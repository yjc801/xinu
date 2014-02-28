/* pipconnect.c - pipconnect */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipconnect
 *------------------------------------------------------------------------
 */
int	pipconnect(pipid32 pipid, pid32 writer, pid32 reader)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	pipentry *piptr;
	struct	procent *prptr_reader;
	struct	procent *prptr_writer;

	mask = disable();

	if (isbadpip(pipid)
		|| isbadpid(writer) 
		|| isbadpid(reader)){
		restore(mask);
		return SYSERR;
	}

	piptr = &piptab[pipid];
	prptr_writer = &proctab[writer];
	prptr_reader = &proctab[reader];

	if (piptr->pstate != PIPE_USED 
		&& piptr->pwriter != INIT_PID
		&& piptr->preader != INIT_PID) {
		restore(mask);
		return SYSERR;
	}

	// update processes
	prptr_writer->prpipside = PIPE_WRITER;
	prptr_reader->prpipside = PIPE_READER;

	// update pipe
	piptr->pstate = PIPE_CONNECTED;
	piptr->pwriter = writer;
	piptr->preader = reader;
	
	restore(mask);
	return OK;
}
