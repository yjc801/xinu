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
	int32 start;
	struct pipentry *piptr;

	if (isbadpip(pipid)
		|| len < 0){
		restore(mask);
		return SYSERR;
	}
	
	piptr = &piptab[pipid];

	if (piptr->pwriter != currpid
		|| piptr->pstate != PIPE_CONNECTED){
		restore(mask);
		return SYSERR;
	}

	count = 0;

	while (count < len){
		wait(sem_empty);
		start = piptr->buffcount;
		temp = (count) % PIPE_SIZE;
		piptr->buffer[temp] = buf[count];
		count++;
		signal(sem_full);
	}
	piptr->buffcount = temp + 1;

	restore(mask);
	return count;
}
