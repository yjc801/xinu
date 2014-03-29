/* pipread.c -pipread */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipread
 *------------------------------------------------------------------------
 */
int32	pipread(pipid32 pipid, char *buf, uint32 len)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct pipentry *piptr;

	mask = disable();
	if (isbadpip(pipid)
		|| len < 0){
		restore(mask);
		return SYSERR;
	}
	
	piptr = &piptab[pipid];

	// check if the process is the reader
	if (piptr->pstate != PIPE_CONNECTED){
		restore(mask);
		return SYSERR;
	}

	// check if buffer is full, if yes, put on the semaphor
	int32 count;//, temp;
	count = 0;
	
	while (count < len){
	
		wait(sem_full);
		// wait(mutex);
		//temp = count % PIPE_SIZE;
		buf[count] = readbuff(piptr->pipbuffer);
		count++;
		// signal(mutex);
		signal(sem_empty);
	
	}
	//piptab[pipid].buffcount-=count;
	//buf[count] = '\0';
	restore(mask);
	return count;
}

