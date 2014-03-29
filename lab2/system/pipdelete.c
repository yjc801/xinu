/* pipdelete.c - pipdelete */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipdelete
 *------------------------------------------------------------------------
 */
int	pipdelete(
	pipid32 pipid
	)
{
	intmask	mask;			/* saved interrupt mask		*/

	struct	pipentry *piptr;		/* ptr to semaphore table entry	*/
	struct procent *prptr;
	mask = disable();

	if (isbadpip(pipid)) {
		restore(mask);
		return SYSERR;
	}
	
	piptr = &piptab[pipid];
	prptr = &proctab[currpid];

	if (prptr->prpipid != pipid        // must be the owner of the pipe
		||piptr->pstate == PIPE_FREE) {
		restore(mask);
		return SYSERR;
	}

	pipcount--;

	prptr->prpipid = INIT_PIPID;
	piptr->pstate = PIPE_FREE;
	piptr->pwriter = INIT_PID;
	piptr->preader = INIT_PID;
	piptr->buffcount = 0;
	freemem(piptr->pipbuffer,sizeof(buff));

	// semdelete(piptr->sem_empty);
	// semdelete(piptr->sem_full);

	// clear the buffer
	// for (i = 0; i < PIPE_SIZE; i++){
	// 	piptr->buffer[i] = '\0';
	// }
	
	restore(mask);
	return OK;
}
