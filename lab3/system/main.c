/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/
void sender(pid32, char);
void reader(void);

int main(int argc, char **argv)
{
	pid32 repid;
	
	resume(repid = create(reader, 2048, 20, "reader", 0));
	resume(create(sender, 2048, 20, "sender1", 2, repid, 'a'));
	//resume(create(sender, 2048, 20, "sender2", 2, repid, 'b'));
	//resume(create(sender, 2048, 20, "sender3", 2, repid, 'c'));
	sleep(100);	
	return OK;
}

void sender(pid32 pid, char id){
	umsg32 i;
	//kprintf("%c",id);
	for (i=0; i<100; i++) {
		kprintf("%c",id);
		sendb(pid, i);
	}
}

void reader(void) {
	umsg32 msg;
	while (1) {
		msg = receiveb();
		kprintf("%d ",msg);
	}
}
