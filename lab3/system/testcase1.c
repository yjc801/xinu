/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/
void sender(pid32, umsg32);
void reader(void);

int main(int argc, char **argv)
{
	pid32 wrpid;
	pid32 repid;
	umsg32 msg = 1;
	
	resume(wrpid = create(sender, 2048, 20, "sender", 1, msg));
	resume(repid = create(reader, 2048, 20, "reader", 0));
	
	return OK;
}

void sender(pid32 pid, umsg32 msg){
	return send(pid, msg);
}

void reader(void) {
	umsg32 msg;
	msg = receive();
	kprintf("%d",msg);
	return;
}
