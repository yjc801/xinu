/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/
void prchP(char, char);
void prchT(char, char);
int prA, prB;
int round;

int main(int argc, char **argv)
{
//	umsg32 retval;
	round = 10;
	pipid32 pipid;
	
	pipid = pipcreate();
	kprintf("Pipe ID is %d\r\n", pipid);
	kprintf("number of pipes %d\r\n", pipcount);
	pipdelete(pipid);
	kprintf("number of pipes %d\r\n", pipcount);
	prA = create(prchP, 2000, 1, "proc A", 2, 'A', 'A');
	prB = create(prchT, 2000, 1, "proc B", 2, 'B', 'B');
	printf("Connected? %d\r\n",pipconnect(pipid,prA,prB));
	// resume(prA);
	// resume(prB);

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

void prchP(char c, char d){
	kprintf("Proc %c starts!\r\n", c);
	int i;
	//chprio(getpid(),10);
	for(i=0; i<round; i++){
		kprintf("%c", d);
	}
	kprintf("Proc %c ends! \r\n", c);
}

void prchP(char c, char d){
	kprintf("Proc %c starts!\r\n", c);
	int i;
	//chprio(getpid(),10);
	for(i=0; i<round; i++){
		kprintf("%c", d);
	}
	kprintf("Proc %c ends! \r\n", c);
}
