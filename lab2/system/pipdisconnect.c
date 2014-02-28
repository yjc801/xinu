/* pipdisconnect.c - pipdisconnect */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipdisconnect
 *------------------------------------------------------------------------
 */
int	pipdisconnect(pipid32 pipid)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct pipentry *piptr;
	struct procent *prptr;

	mask = disable();

	if (isbadpip(pipid)){
		restore(mask);
		return SYSERR;
	}

	piptr = &piptab[pipid];
	prptr = &proctab[currpid];
	
	if (piptr->pstate != PIPE_CONNECTED
		
		||(piptr->pwriter != currpid 
		&& piptr->preader != currpid) // check whether curr is reader or writer
		
		) {
		restore(mask); 
		return SYSERR;
	}

	// if both sides are connected

	if (piptr->pwriter != INIT_PID
		&& piptr->preader != INIT_PID) {
		prptr->prpipside = -1;   // disconnect pipe with curr process, reset writer/reader
		restore(mask);
		return OK;
	}

	// one side is connected, if reader, let it finish
	
	if (prptr->prpipside == PIPE_READER){
		// finish buffer
	}

	// clean up buffer

	piptr->pstate = PIPE_FREE;
	prptr->prpipside = -1;
	// reset writer/reader

	restore(mask);
	return OK;
}
