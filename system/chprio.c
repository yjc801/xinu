/* chprio.c - chprio */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  chprio  -  Change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
pri16	chprio(
	  pid32		pid,		/* ID of process to change	*/
	  pri16		newprio		/* new priority			*/
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	pri16	oldprio;		/* priority to return		*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return (pri16) SYSERR;
	}
	prptr = &proctab[pid];
	
	if (prptr->prgroup == PROPORTIONALSHARE){
		oldprio = prptr->prrate;
		prptr->prrate = newprio;
	}

	if (prptr->prgroup == TSSCHED){
		oldprio = prptr->prprio;
		prptr->prprio = newprio;
		// if changing the current process
		if (prptr->prstate == PR_CURR){
			resched();
		}
		// if changing the process in ready queue
		if (prptr->prstate == PR_READY){
			insert(getitem(pid), readylist, prptr->prprio);
		}
	}

	restore(mask);
	return oldprio;
}
