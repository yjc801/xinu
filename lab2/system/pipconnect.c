/* pipconnect.c - pipconnect */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipconnect
 *------------------------------------------------------------------------
 */
pipid32	pipconnect(pipid32 pipid, pid32 writer, pid32 reader)
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

	if (piptr->pstate != PIPE_FREE) {
		restore(mask);
		return SYSERR;
	}

	piptr->pwriter = writer;
	piptr->preader = reader;
	
	restore(mask);
	return OK;
}
