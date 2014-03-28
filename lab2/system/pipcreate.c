/* pipcreate.c - pipcreate */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipcreate
 *------------------------------------------------------------------------
 */
pipid32	pipcreate(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	pipid32	pipid;
	struct procent *prptr;
	static pipid32 nextpip = 0;
	int32	i;
	int32 j;

	mask = disable();
	// check if this process is a producer or consumer
	
	prptr = &proctab[currpid];

	if (pipcount > NPIPE) {
		restore(mask);
		return SYSERR;
	}

	pipcount++;
	
	for (i = 0; i < NPIPE; i++)
	{
		pipid = nextpip++;
		if (nextpip >= NPIPE)
			nextpip = 0;
		if (piptab[pipid].pstate == PIPE_FREE) {
			piptab[pipid].pstate = PIPE_USED;
			piptab[pipid].preader = INIT_PID;
			piptab[pipid].pwriter = INIT_PID;
			piptab[pipid].buffcount = 0;
			piptab[pipid].sem_empty = semcreate(PIPE_SIZE);
			piptab[pipid].sem_full = semcreate(0);
			for (j = 0; j < PIPE_SIZE; j++){
				piptab[pipid].buffer[j] = '\0';
			}
			prptr->prpipid = pipid;  // owner of the pipe
			restore(mask);
			return pipid;
		}
	}
	
	restore(mask);
	return SYSERR;
}
