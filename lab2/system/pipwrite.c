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

	kprintf("I'm the writer\r\n");

	// check if buffer is full, if yes, put on the semaphor
	// if (piptr->buffcount >= PIPE_SIZE){
	// }

	int32 count;
	count = 0;
	// start = piptr->buffcount + 1;

	while (count != len && buf[count] != '\0'){
	
		wait(sem_empty);
		if (piptr->pstate != PIPE_CONNECTED) {
			restore(mask);
			return SYSERR;
		}
		piptr->buffer[count] = buf[count];
		count++;
		signal(sem_full);
	
	}

	// if reader is in other state? (killed, other state)
	// signal read if it is waiting

	// ready
	kprintf("Finish writing! I have written %d letters.\r\n",count);
	restore(mask);
	return count;
}
