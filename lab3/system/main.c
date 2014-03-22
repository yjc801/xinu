#include <xinu.h>
#include <stdio.h>
#include <string.h>
/************************************************************************/
/* */
/* main - main program for testing Xinu */
/* */
/************************************************************************/
void sender(pid32 receiver) {
	uint32 i;
	for(i=0; i<15; i++) {
		kprintf("sender %d\r\n",i);
		if( sendb(receiver, i) == SYSERR ) {
			kprintf("Fail to send msg %d!\r\n", i);
		} else {
			kprintf("Send msg %d to receiver!\r\n", i);
		}
	}
	return;
}

void receiver(void) {
	int i;
	uint32 msg;
	for(i=0; i<15; i++) {
		msg = receiveb();
		if( msg == SYSERR ) {
			kprintf("Fail to recieve msg!\r\n");
		} else {
			kprintf("Recieve msg %d from sender!\r\n", msg);
		}
	sleep(1);
	}
	return;
}
 
int main(int argc, char **argv) {
	pid32 spid, rpid;
	rpid = create(receiver, 2014, 20, "receiver", NULL);
	spid = create(sender, 2048, 20, "sender", 1, rpid);
	resume(rpid);
	resume(spid);

	while(1) {
		sleep(100);
	}
	return OK;
}
