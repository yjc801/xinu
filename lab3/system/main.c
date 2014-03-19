/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/
void sender(pid32);
void reader(void);

int main(int argc, char **argv)
{
	pid32 wrpid;
	pid32 repid;
	
	resume(repid = create(reader, 2048, 20, "reader", 0));
	resume(wrpid = create(sender, 2048, 20, "sender", 1, repid));
	sleep(100);	
	return OK;
}

void sender(pid32 pid){
	umsg32 i;
	while (1){
		for (i=0; i<100; i++) 
			sendb(pid, i);
	}
}

void reader(void) {
	umsg32 msg;
	while (1) {
		msg = receiveb();
		kprintf("%d",msg);
	}
}
