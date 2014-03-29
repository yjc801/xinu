/* readbuffer.c */

#include <xinu.h>

char	readbuff(
	  buff	*buffer
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	char msg;

	mask = disable();
	
	int16 start = buffer->start;
	msg = buffer->elems[start];
	buffer->start = (start + 1) % buffer->size;
	-- buffer->count;

	restore(mask);
	return msg;
}
