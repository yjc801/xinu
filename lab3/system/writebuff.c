/* writebuff.c */

#include <xinu.h>

void	writebuff(
	  buff	buffer,
	  umsg32 msg
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	
	mask = disable();

    int16 end = (buffer.start + buffer.count) % buffer.size;
    buffer.elems[end] = msg;
    if (buffer.count == buffer.size)
        buffer.start = (buffer.start + 1) % buffer.size; /* full, overwrite */
    else
        ++ buffer.count;

	restore(mask);
	// return msg;
}
