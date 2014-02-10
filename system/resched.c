/* resched.c - resched */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */

void	resched(void)		/* assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* ptr to table entry for old process	*/
	struct procent *ptnew;	/* ptr to table entry for new process	*/
	int32 propcounter; //counter for propotional group
	int32 tscounter; //counter for ts group
	//uint16 Ri; //process rate
	//uint16 Pi; 
	struct	procent *prptr; //pointer 
	struct	procent *ptrTS; //pointer to first proc in TS
	int16 firstTS; //id of first proc in TS
	int16 first; //id of first process in ready queue

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}
	
	/* Point to process table entry for the firstent (old) process */
	ptold = &proctab[currpid];

	// update the priority of firstent process
	// Pi' = Pi' + (t*100/Ri); Pi = Maxint - Pi'
	//Pi = MAXINT - ptold->prprio;
	//Ri = ptold->prrate;
	//Pi += t*100.0/Ri;
	//ptold->prprio = MAXINT - Pi;

	// group A is set to the initial priority if the firstent process belongs to group A
	
	if(ptold->prgroup == PROPORTIONALSHARE){
		propprio = INITGPPRIO;
	}
	else{
		tsprio = INITGPPRIO;
	}

	// Traverse the queue table and update the priories of each group
	if (isempty(readylist)) {
		return;
	}
	
	propcounter = 0;
	tscounter = 0;
	first = firstid(readylist);	
	while (queuetab[first].qkey != MINKEY) {
		prptr = &proctab[first];
		kprintf("Proc in ready queue %s\r\n",prptr->prname);
		if(prptr->prgroup == PROPORTIONALSHARE){
			propcounter++;
		}
		else{
			tscounter++;
			if (tscounter == 1){
				firstTS = first;
				ptrTS = prptr;
			}
		}
		first = queuetab[first].qnext;
	}

	propprio += propcounter;
	tsprio += tscounter;
	
	kprintf("\nProp is %d.\r\r\nTs is %d.\r\n",propprio,tsprio);

	if (ptold->prstate == PR_CURR) { /* process remains running */
		if (ptold->prgroup == PROPORTIONALSHARE){
			if (propprio > tsprio && ptold->prprio > firstkey(readylist)) {
				return;
			}
		}
		if (ptold->prgroup == TSSCHED){ // if no other proc in TS
			if (tscounter == 0) return;
			if (tsprio > propprio && ptold->prprio > ptrTS->prprio) {
				return;
			}
		}
		/* Old process will no longer remain current */
			ptold->prstate = PR_READY;
			insert(currpid, readylist, ptold->prprio);
		}

		/* Force context switch to highest priority ready process */
	
	if (propprio > tsprio || tscounter == 0){
		kprintf("Dequeue first proc in Prop share");
		currpid = dequeue(readylist);
	}else{
		kprintf("First proc in TS is \r\n",ptrTS->prname);
		currpid = getitem(firstTS);
	}

	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;	/* reset time slice for process */
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;

}
