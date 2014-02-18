/* pipdelete.c - pipdelete */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipdelete
 *------------------------------------------------------------------------
 */
int	pipdelete(pipid32)
{
	intmask	mask;			/* saved interrupt mask		*/
	pipid32	pipid;		

	mask = disable();
	if (pipcount < 1) {
		restore(mask);
		return SYSERR;
	}

	pipcount--;

	restore(mask);
	return OK;
}
