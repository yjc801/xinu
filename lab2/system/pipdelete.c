/* pipdelete.c - pipdelete */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipdelete
 *------------------------------------------------------------------------
 */
int	pipdelete(
	pipid32 pipid32
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	pipid32	pipid;		
	struct	pipentry *piptr;		/* ptr to semaphore table entry	*/

	mask = disable();

	if (isbadpip(pipid32)) {
		restore(mask);
		return SYSERR;
	}
	
	piptr = &piptab[pipid];

	if (piptr->pstate == PIPE_FREE) {
		restore(mask);
		return SYSERR;
	}

	piptr->pstate = PIPE_FREE;

	// clear the buffer
	
	restore(mask);
	return OK;
}
