/* freememb.c - freememb */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  freemem  -  Free a memory block, returning the block to the free list
 *------------------------------------------------------------------------
 */
syscall	freememb(
	  char		*blkaddr,	/* pointer to memory block	*/
	  uint32	nbytes		/* size of block in bytes	*/
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	memblk	*next, *prev, *block;
	uint32	top;
	struct 	procent	*prptr;
	struct 	tracklist *curr, *temp;

	mask = disable();
	if ((nbytes == 0) || ((uint32) blkaddr < (uint32) minheap)
			  || ((uint32) blkaddr > (uint32) maxheap)) {
		restore(mask);
		return SYSERR;
	}

	blkaddr -=  sizeof(tracklist);
	nbytes = (uint32) roundmb(nbytes) + sizeof(tracklist);	/* use memblk multiples	*/
	block = (struct memblk *)blkaddr;

	prev = &memlist;			/* walk along free list	*/
	next = memlist.mnext;
	while ((next != NULL) && (next < block)) {
		prev = next;
		next = next->mnext;
	}

	if (prev == &memlist) {		/* compute top of previous block*/
		top = (uint32) NULL;
	} else {
		top = (uint32) prev + prev->mlength;
	}

	/* Insure new block does not overlap previous or next blocks	*/

	if (((prev != &memlist) && (uint32) block < top)
	    || ((next != NULL)	&& (uint32) block+nbytes>(uint32)next)) {
		kprintf("Check\r\n");
		restore(mask);
		return SYSERR;
	}

	memlist.mlength += nbytes;

	/* Either coalesce with previous block or add to free list */

	if (top == (uint32) block) { 	/* coalesce with previous block	*/
		prev->mlength += nbytes;
		block = prev;
	} else {			/* link into list as new node	*/
		block->mnext = next;
		block->mlength = nbytes;
		prev->mnext = block;
	}

	/* Coalesce with next block if adjacent */

	if (((uint32) block + block->mlength) == (uint32) next) {
		block->mlength += next->mlength;
		block->mnext = next->mnext;
	}

	//update tracklist
	prptr = &proctab[currpid];
	curr = prptr->prblock;
	while (curr != NULL){
    		//kprintf("%d,%d\r\n",blkaddr,curr);
		curr = curr->next;
	}

	curr = prptr->prblock;
	if ((char *)curr == blkaddr){
		prptr->prblock = curr->next;
    		numbytes-=nbytes;
	}else{
  		while(curr!= NULL){
			temp = curr->next;
    			if ((char *)temp == blkaddr){
    				curr->next = temp->next;
    				temp->next = NULL;
				numbytes-=nbytes;
    			}
			curr = curr->next;
		 }
	}
	restore(mask);
	return OK;
}
