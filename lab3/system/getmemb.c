/* getmemb.c - getmemb */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getmem  -  Allocate heap storage, returning lowest word address
 *------------------------------------------------------------------------
 */
char  	*getmemb(
	  uint32	nbytes		/* size of memory requested	*/
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	memblk	*prev, *curr, *leftover;
	struct  procent	*prptr;
	struct 	tracklist	*temp;

	mask = disable();
	if (nbytes == 0) {
		restore(mask);
		return (char *)SYSERR;
	}

	nbytes = (uint32) roundmb(nbytes);	/* use memblk multiples	*/
	
	prptr = &proctab[currpid];

	prev = &memlist;
	curr = memlist.mnext;
	while (curr != NULL) {			/* search free list	*/

		if (curr->mlength == nbytes) {	/* block is exact match	*/
			prev->mnext = curr->mnext;
			memlist.mlength -= nbytes;

			temp = (tracklist *) curr;
			curr++;
			temp->length = nbytes;
			temp->blkaddr = (char *)curr;
			temp->next = prptr->prblock;
			prptr->prblock = temp;
			restore(mask);
			return (char *)(curr);

		} else if (curr->mlength > nbytes) { /* split big block	*/
			leftover = (struct memblk *)((uint32) curr +
					nbytes);
			prev->mnext = leftover;
			leftover->mnext = curr->mnext;
			leftover->mlength = curr->mlength - nbytes;
			memlist.mlength -= nbytes;

			temp = (tracklist *) curr;
			curr++;
			temp->length = nbytes;
			temp->blkaddr = (char *)curr;
			temp->next = prptr->prblock;
			prptr->prblock = temp;
			restore(mask);
			return (char *)(curr);
		} else {			/* move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;
}
