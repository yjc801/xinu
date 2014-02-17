/* chgprio.c - chgprio */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  chgprio  -  Change the scheduling priority of a group
 *------------------------------------------------------------------------
 */
pri16	chgprio(
	
	int group, 		// group
	pri16 newprio	// new group priority

	)
{
	intmask	mask;			/* saved interrupt mask		*/
	pri16	oldprio;		/* priority to return		*/

	mask = disable();
	if (isbadgroup(group)) {
		restore(mask);
		return (pri16) SYSERR;
	}
	if (group == PROPORTIONALSHARE){
		oldprio = INITGPPRIO_PROP;
		INITGPPRIO_PROP = newprio;
	}
	if (group == TSSCHED){
		oldprio = INITGPPRIO_TS;
		INITGPPRIO_TS = newprio;
	}
	restore(mask);
	return oldprio;
}
