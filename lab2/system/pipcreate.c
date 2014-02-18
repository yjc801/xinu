/* pipcreate.c - pipcreate */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  chprio  -  Change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
pipid32	pipcreate(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	pipid32	pipid;		

	mask = disable();
	if (pipcount > NPIPE) {
		restore(mask);
		return (pipid32) SYSERR;
	}

	pipcount++;
	
	pipid = (pipid32) semcreate(1);

	restore(mask);
	return pipid;
}
