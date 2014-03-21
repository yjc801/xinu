#include <xinu.h>

syscall registerrecv(umsg32 *abuf, int (* func)(void)){

	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	pid32 pid;

	mask = disable();
	pid = create(*func, 2048, 20, "func", 0);
	if (pid == SYSERR){
		restore(mask);		/* restore interrupts */
		return SYSERR;
	}
	abuf = &recvbuf;

	prptr = &proctab[pid];
	prptr->prreg = TRUE;
	prptr->prregpid = pid;

	restore(mask);		/* restore interrupts */
	return OK;
}
