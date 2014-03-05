/* pipwrite.c -pipwrite */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipwrite
 *------------------------------------------------------------------------
 */
int32	pipwrite(pipid32 pipid, char *buf, uint32 len)
{
	intmask	mask;			/* saved interrupt mask		*/
	//int i;
	struct pipentry *piptr;

	if (isbadpip(pipid)
		|| len < 0){
		restore(mask);
		return SYSERR;
	}
	
	piptr = &piptab[pipid];

	// check if the process is the writer
	if (piptr->pwriter != currpid
		|| piptr->pstate != PIPE_CONNECTED){
		restore(mask);
		return SYSERR;
	}

	// check if buffer is full, if yes, put on the semaphor
	// if (piptr->buffcount >= PIPE_SIZE){
	// }

	int32 count;
	int32 temp;
	//int32 start;
	count = 0;
//	count = piptr->buffcount;

	while (count < len){
		wait(sem_empty);
		temp = count % PIPE_SIZE;
		wait(mutex);
		piptr->buffer[temp] = buf[count];
		signal(mutex);
		count++;
		signal(sem_full);
	}
	//piptr->buffcount+=count;
	
	// if reader is in other state? (killed, other state)
	// signal read if it is waiting

	restore(mask);
	return count;
}
