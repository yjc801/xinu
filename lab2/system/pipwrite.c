/* pipwrite.c -pipwrite */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipwrite
 *------------------------------------------------------------------------
 */
int32	pipwrite(pipid32 pipid, char *buf, uint32 len)
{
	intmask	mask;			/* saved interrupt mask		*/
	int32 count;
	int32 temp;
	struct pipentry *piptr;

	if (isbadpip(pipid)
		|| len < 0){
		restore(mask);
		return SYSERR;
	}
	
	piptr = &piptab[pipid];

	// if (piptr->pwriter != currpid
	// 	|| piptr->pstate != PIPE_CONNECTED){
	// 	restore(mask);
	// 	return SYSERR;
	// }

	count = 0;
	// int32 start;
	// wait(mutex);
	// start = piptr->buffcount;
	// signal(mutex);
	while (count < len){	
		wait(piptr->sem_empty);
		temp = count % PIPE_SIZE;
		piptr->buffer[temp] = buf[count];
		count++;
		signal(piptr->sem_full);
	}
	// piptr->buffcount = temp + 1;

	restore(mask);
	return count;
}
