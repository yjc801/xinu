/* readbuffer.c */

#include <xinu.h>

umsg32	readbuff(
	  buff	*buffer
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	umsg32 msg;

	mask = disable();
	
	int16 start = buffer->start;
	msg = buffer->elems[start];
	buffer->start = (start + 1) % buffer->size;
	-- buffer->count;

	restore(mask);
	return msg;
}
