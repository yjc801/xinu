/* kill.c - kill */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  kill  -  Kill a process and remove it from the system
 *------------------------------------------------------------------------
 */
syscall	kill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	int32	i;			/* index into descriptors	*/
	struct	memblk	*curr;

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	freestk(prptr->prstkbase, prptr->prstklen);

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* suicide */
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* fall through */

	case PR_READY:
		getitem(pid);		/* remove from queue */
		/* fall through */

	default:
		
		while(nonempty(prptr->prwait)){
			ready(dequeue(prptr->prwait),RESCHED_NO);	
		}

		if (prptr->prgcflag){
			curr = &memlist;
			while (curr != NULL){
				if (curr->gcflag == TRUE && curr->gcpid == currpid)
					freememb((char *)curr, curr->mlength);
				curr = curr->mnext;
			}
		}
		prptr->prstate = PR_FREE;
	}

	restore(mask);
	return OK;
}
