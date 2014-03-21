#include <xinu.h>

syscall registerrecv(umsg32 *abuf, int (* func)(void)){

	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/

	mask = disable();

	prptr = &proctab[currpid];
	prptr->prreg = TRUE;
	abuf = &prptr->prmsg;
	prptr->prregptr = func;

	restore(mask);		/* restore interrupts */
	return OK;
}
