#include <xinu.h>
#include <stdio.h>
#include <string.h>
/************************************************************************/
/* */
/* main - main program for testing Xinu */
/* */
/************************************************************************/

void allocater(void){
	char *p1;
	char *p2;
	char *p3;

	p1 = getmemb(10);
	kprintf("1. %d\r\n",numbytes);
	sleepms(10);
	p2 = getmemb(8);
	kprintf("2. %d\r\n",numbytes);
	sleepms(10);
	p3 = getmemb(13);
	kprintf("3. %d\r\n",numbytes);
	freememb(p1,10);
	// freememb(p2,8);
	// freememb(p3,13);
	sleepms(10);
	kprintf("4. %d\r\n",numbytes);
}

int main(int argc, char **argv) {
	pid32 pid;
	kprintf("Start: %d\r\n",numbytes);
	pid = resume(create(allocater, 2014, 20, "allocater", NULL));
	sleep(1);
	kill(pid);
	sleep(1);
	kprintf("End: %d\r\n",numbytes);
	return OK;
}
