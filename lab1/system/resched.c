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
	uint16 Ri; //process rate
	uint16 Pi; // Pi for proportional share
	uint32 t;  // CPU consumed ticks
	struct	procent *prptr; //pointer 
	struct	procent *ptrTS; //pointer to first proc in TS
	struct	procent *ptrfirst; //pointer to first proc in readylist
	int16 firstTS; //id of first proc in TS
	int16 first; //id of first process in ready queue

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the firstent (old) process */
	
	ptold = &proctab[currpid];

	// group A is set to the initial priority if the current process belongs to group A
	
	if(ptold->prgroup == PROPORTIONALSHARE && currpid != NULLPROC)
	{
		propprio = INITGPPRIO_PROP;
		// update the priority of current process
		t = ptold->prtime;
		Pi = MAXINT - ptold->prprio;
		Ri = ptold->prrate;
		Pi += t*100/Ri;
		ptold->prprio = MAXINT - Pi;
	}

	if(ptold->prgroup == TSSCHED && currpid != NULLPROC){   
		
		tsprio = INITGPPRIO_TS;
		if (preempt == QUANTUM && ptold->prstate != PR_CURR){  // Junchao Yan modified, where it was preempt < QUANTUM
			ptold->prprio += 1;
		}

	}

	// Traverse the queue table and update the priories of each group
	
	if (isempty(readylist)) {
		return;
	}
	
	// kprintf("Process %s\r\n",ptold->prname);
	propcounter = 0;
	tscounter = 0;
	first = firstid(readylist);
	ptrfirst = &proctab[first];

	while (first != NULLPROC && queuetab[first].qkey != MINKEY) {
		prptr = &proctab[first];
		if(prptr->prgroup == PROPORTIONALSHARE){
			propcounter++;
		}else{
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
	
	// kprintf("Prop is %d.\r\r\nTs is %d.\r\n",propprio,tsprio);

	if (ptold->prstate == PR_CURR) { /* process remains running */

		if (ptold->prgroup == PROPORTIONALSHARE){
			ptold->prtime = preempt;
			if (propcounter != 0 && propprio > tsprio){
				if(ptold->prprio > ptrfirst->prprio){
					return;
				}
			}
		}

		if (ptold->prgroup == TSSCHED){ // if no other proc in TS
			if (tscounter != 0 && tsprio > propprio){
				if(ptold->prprio > ptrTS->prprio) {
					return;
				}
			}
		}

		/* Old process will no longer remain current */
		
			ptold->prstate = PR_READY;
			insert(currpid, readylist, ptold->prprio);
		}

		/* Force context switch to highest priority ready process */
	
	if (propprio > tsprio || tscounter == 0){
		currpid = dequeue(readylist);
	}else{
		currpid = getitem(firstTS);
	}

	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;	/* reset time slice for process */
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;

}
