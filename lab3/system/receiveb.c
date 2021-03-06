/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receiveb(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	umsg32	msg;			/* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	
	if (prptr->prbuffer.count <= 0){
		prptr->prstate = PR_RECVB;
		resched();		 
	}
	
	msg = readbuff(&prptr->prbuffer);
	prptr->prbuffull = FALSE;
	if(nonempty(prptr->prwait)){
		ready(dequeue(prptr->prwait), RESCHED_YES);
	}
	
	restore(mask);
	return msg;
}
