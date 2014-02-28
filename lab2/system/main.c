/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/

int main(int argc, char **argv)
{
	umsg32 retval;

	pipid32 pipid;
	
	pipid = pipcreate();
	kprintf("Pipe ID is %d\r\n", pipid);
	kprintf("number of pipes %d\r\n", pipcount);
	pipdelete(pipid);
	kprintf("number of pipes %d\r\n", pipcount);
	
	/* Creating a shell process */

	// resume(create(shell, 4096, 1, "shell", 1, CONSOLE));

	// retval = recvclr();
	// while (TRUE) {
		// retval = receive();
		// kprintf("\n\n\rMain process recreating shell\n\n\r");
		// resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
	// }

	return OK;
}
