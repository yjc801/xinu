#include <xinu.h>
#include <stdio.h>

uint32 recvbuf;

int myrecvhandler1(void) {
	kprintf("Handler1: msg received = %d\r\n", recvbuf);
	sleep(2);
	return(OK);
}
 
int myrecvhandler2(void) {
	kprintf("Handler2: msg received = %d\r\n", recvbuf);
	return(OK);
}

void sender(pid32 receiver) {
	sleep(3);
	int i;
	for (i=0;i<5;i++){
	if( send(receiver, i) == SYSERR ) {
		kprintf("Fail to send msg %d!\r\n",i);
	} else {
		kprintf("Send msg %d\r\n",i);
	}
	sleepms(10);
	}
	return;
}

void receiver(void) {
//	kprintf("receive() %d\r\n",receive());
	if (registerrecv(&recvbuf, &myrecvhandler1) != OK) {
		kprintf("recv handler registration failed\n");
		return;
	}
	sleep(5);
	if (registerrecv(&recvbuf, &myrecvhandler2) != OK) {
		kprintf("recv handler registration failed\n");
	//	return;
	}

	while(1) {
		sleep(1);
	}
	return;
}
 
int main(int argc, char **argv) {
	pid32 spid1, rpid;
	rpid = create(receiver, 2014, 20, "receiver", NULL);
	spid1 = create(sender, 2048, 20, "sender1", 1, rpid);
	//spid2 = create(sender, 2048, 20, "sender2", 1, rpid);
	resume(rpid);
	resume(spid1);
	//resume(spid2);

	while(1) {
		sleep(100);
	}
	return OK;
}
