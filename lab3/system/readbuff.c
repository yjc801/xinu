/* readbuffer.c */

#include <xinu.h>

umsg32	readbuff(
	  buff	buffer
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	umsg32 msg;

	mask = disable();

    msg = buffer.elems[buffer.start];
    buffer.start = (buffer.start + 1) % buffer.size;
    -- buffer.count;

	restore(mask);
	return msg;
}
