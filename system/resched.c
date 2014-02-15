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
	// uint32 T;  // CPU elapsed ticks
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
	//kprintf("----------------preempt is %d -------------------\r\n",preempt);	
	/* Point to process table entry for the firstent (old) process */
	
	ptold = &proctab[currpid];
	
	//kprintf("Process %s\r\n",ptold->prname);

	// T = clktime * CLKTICKS_PER_SEC; // current CPU time in ticks

	// group A is set to the initial priority if the firstent process belongs to group A

	if(ptold->prgroup == PROPORTIONALSHARE && currpid != NULLPROC)
	{
		
		propprio = INITGPPRIO_PROP;
		// update the priority of firstent process
		t = preempt;
		//t = ptold->prtime;
//		 kprintf("the t is %d.\r\n",t);
		Pi = MAXINT - ptold->prprio;
//		  kprintf("the Pi is %d.\r\n",Pi);
		Ri = ptold->prrate;
		 // kprintf("the Ri is %d.\r\n",Ri);
		Pi += t*100/Ri;
		ptold->prprio = MAXINT - Pi;

	}

	kprintf("Priority of %s is %d.\r\n",ptold->prname,ptold->prprio);

	if(ptold->prgroup == TSSCHED && currpid != NULLPROC){
		
		tsprio = INITGPPRIO_TS;
		if (preempt < QUANTUM && ptold->prstate != PR_CURR){
			ptold->prprio += 1;
		}

	}

	// Traverse the queue table and update the priories of each group
	
	if (isempty(readylist)) {
		return;
	}
	
	kprintf("Process %s\r\n",ptold->prname);
	propcounter = 0;
	tscounter = 0;
	first = firstid(readylist);
	ptrfirst = &proctab[first];
//	kprintf("Priority of first in ready queue %d.\r\n",ptrfirst->prprio);
	while (first != NULLPROC && queuetab[first].qkey != MINKEY) {
		prptr = &proctab[first];
//		kprintf("Proc in ready queue %s\r\n",prptr->prname);
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
	
	kprintf("Prop is %d.\r\r\nTs is %d.\r\n",propprio,tsprio);

	if (ptold->prstate == PR_CURR) { /* process remains running */
	// kprintf("clktime is %d.\r\n",clktime*CLKCYCS_PER_TICK + clkticks);
		if (ptold->prgroup == PROPORTIONALSHARE){
			//ptold->prtime = (clktime * CLKCYCS_PER_TICK + clkticks) - ptold->prstart;
			if (propprio > tsprio){
				if(propcounter == 0 || ptold->prprio > ptrfirst->prprio){
				return;
				}
			}
		}
		if (ptold->prgroup == TSSCHED){ // if no other proc in TS
			if (tsprio > propprio){
			if(tscounter == 0 || ptold->prprio > ptrTS->prprio) {
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
		//kprintf("Dequeue first proc in Prop share\r\n\n");
		currpid = dequeue(readylist);
	}else{
		// kprintf("Dequeue first proc in TS: %s\r\n\n",ptrTS->prname);
		currpid = getitem(firstTS);
	}

	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	//ptnew->prstart = clktime * CLKCYCS_PER_TICK + clkticks;
	// if (ptnew->prgroup == PROPORTIONALSHARE && T > (MAXINT - ptnew->prprio)) ptnew->prprio = T; 
	preempt = QUANTUM;	/* reset time slice for process */
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;

}
