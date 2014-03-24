#include <xinu.h>

syscall registerrecv(umsg32 *abuf, int (* func)(void)){

	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhandling){
		restore(mask);
		return SYSERR;
	}
	prptr->prreg = TRUE;
	prptr->prmsgaddr = abuf;
	prptr->prregptr = func;

	restore(mask);		/* restore interrupts */
	return OK;
}
