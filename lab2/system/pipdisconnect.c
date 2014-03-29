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

	// check whether curr is reader or writer
	
	if (piptr->pstate != PIPE_CONNECTED
		) {
		restore(mask); 
		return SYSERR;
	}

	// if both sides are connected

	if (piptr->pwriter != INIT_PID
		&& piptr->preader != INIT_PID) {
		prptr->prpipside = -1;   // disconnect pipe with curr process, reset writer/reader
		if (piptr->preader == currpid){
			piptr->preader = INIT_PID;
		}
		else{
			piptr->pwriter = INIT_PID;
		}
		restore(mask);
		return OK;
	}

	// one side is connected, if reader, let it finish
	
	if (piptr->preader == currpid){
		piptr->preader = INIT_PID;
		// finish buffer
	}

	if (piptr->pwriter == currpid){
		piptr->pwriter = INIT_PID;
	}

	// reset
	piptr->pstate = PIPE_USED;
	prptr->prpipside = -1;

	// clean up buffer
	piptr->buffcount = 0;
	// for (i = 0; i < PIPE_SIZE; i++){
	// 	piptr->buffer[i] = '\0';
	// }

	restore(mask);
	return OK;
}
