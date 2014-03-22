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
	struct  sentry	*semptr;
	umsg32	msg;			/* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECVB;
		resched();		/* block until message arrives	*/
	}
	
	msg = readbuff(&prptr->prbuffer);
	
	semptr = &semtab[prptr->prbuffsem];
	
	//kprintf("scount %d\r\n",semptr->scount);
	
	if (semptr->scount <= 0) {
		signal(prptr->prbuffsem);
		prptr->prhasmsg = FALSE;	/* reset message flag		*/
	}
	
	restore(mask);
	return msg;
}
