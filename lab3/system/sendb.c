/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	sendb(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* contents of message		*/
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	struct  procent *curr;

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];

	if (prptr->prstate == PR_FREE)
	{
		restore(mask);
		return SYSERR;
	}
	
	while(prptr->prbuffull){
		curr->prstate = PRSND;
		enqueue(currpid,prptr->prwait);
		resched();
	}

	writebuff(&prptr->prbuffer, msg);
	if (prptr->prbuffer.size >= MSGSIZE){
		prptr->prbuffull = TRUE;
	}

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECVB) {
		ready(pid, RESCHED_YES);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid, RESCHED_YES);
	}
	restore(mask);		/* restore interrupts */
	return OK;
}
