/* pipdisconnect.c - pipdisconnect */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipdisconnect
 *------------------------------------------------------------------------
 */
int	pipdisconnect(pipid32 pipid)
{
	intmask	mask;			/* saved interrupt mask		*/
	int i;
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
		||(piptr->pwriter != currpid 
		&& piptr->preader != currpid)) {
		restore(mask); 
		return SYSERR;
	}

	// if both sides are connected

	if (piptr->pwriter != INIT_PID
		&& piptr->preader != INIT_PID) {
		prptr->prpipside = -1;   // disconnect pipe with curr process, reset writer/reader
		if (piptr->preader == currpid){
			piptr->preader = INIT_PID;
		}else{
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

	// clean up buffer
	for (i = 0; i < PIPE_SIZ; i++){
		piptr->buffer[i] = '\0';
	}

	piptr->pstate = PIPE_USED;
	prptr->prpipside = -1;

	restore(mask);
	return OK;
}
