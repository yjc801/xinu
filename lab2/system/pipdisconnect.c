/* pipdisconnect.c - pipdisconnect */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipdisconnect
 *------------------------------------------------------------------------
 */
int	pipdisconnect(pipid32 pipid)
{
	intmask	mask;			/* saved interrupt mask		*/
	static pipid32 nextpip = 0;
	int32	i;

	mask = disable();

	if (isbadpip(pipid)
		|| isbadpid(writer) 
		|| isbadpid(reader)){

		restore(mask);
		return SYSERR;
	}

	piptr = &piptab[pipid];
	
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
		currpid->prpipside = -1;   // disconnect pipe with curr process, reset writer/reader
		restore(mask);
		return OK;
	}

	// one side is connected, if reader, let it finish
	
	if (currpid->prpipside = PIPE_READER){
		// finish buffer
	}

	// clean up buffer

	piptr->pstate = PIPE_FREE
	currpid->prpipside = -1;
	// reset writer/reader

	restore(mask);
	return OK;
}
