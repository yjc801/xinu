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
	static pipid32 nextpip = 0;
	int32	i;

	mask = disable();
	// check if this process is a producer or consumer

	if (currpid->prpipid != -1
		|| pipcount > NPIPE) {
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
			currpid->prpipid = pipid;  // owner of the pipe
			restore(mask);
			return pipid;
		}
	}
	
	restore(mask);
	return SYSERR;
}
