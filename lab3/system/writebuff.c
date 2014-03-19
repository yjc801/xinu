/* writebuff.c */

#include <xinu.h>

void	writebuff(
	  buff	*buffer,
	  umsg32 msg
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	// int16 end;
	
	mask = disable();

    // end = (buffer.start + buffer.count) % buffer.size;
    buffer->elems[0] = msg;

 //    if (buffer.count == buffer.size){
 //        buffer.start = (buffer.start + 1) % buffer.size;
 //    }else{
 //        ++ buffer.count;
	// }

	restore(mask);
	// return msg;
}
