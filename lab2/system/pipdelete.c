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
	int i;		
	struct	pipentry *piptr;		/* ptr to semaphore table entry	*/

	mask = disable();

	if (isbadpip(pipid)) {
		restore(mask);
		return SYSERR;
	}
	
	piptr = &piptab[pipid];

	if (currpid->prpipid != pipid        // must be the owner of the pipe
		||piptr->pstate == PIPE_FREE) {
		restore(mask);
		return SYSERR;
	}

	pipcount--;

	currpid->prpipid = INIT_PIPID;
	piptr->pstate = PIPE_FREE;
	piptr->pwriter = INIT_PID;
	piptr->preader = INIT_PID;

	// clear the buffer
	for (i = 0; i < PIPE_SIZ; i++){
		piptr->buffer[i] = '\0';
	}
	
	restore(mask);
	return OK;
}
