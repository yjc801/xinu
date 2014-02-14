/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid,		/* ID of process to make ready	*/
	  bool8		resch		/* reschedule afterward?	*/
	)
{
	register struct procent *prptr;
	uint32 T;

	T = clktime * CLKTICKS_PER_SEC; // current CPU time in ticks

	if (isbadpid(pid)) {
		return(SYSERR);
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	if (prptr->prgroup == PROPORTIONALSHARE && T > (MAXINT - ptnew->prprio)) prptr->prprio = T; 
	
	insert(pid, readylist, prptr->prprio);

	if (resch == RESCHED_YES) {
		resched();
	}
	return OK;
}
