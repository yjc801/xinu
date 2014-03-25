#include <xinu.h>
#include <stdio.h>
#include <string.h>
/************************************************************************/
/* */
/* main - main program for testing Xinu */
/* */
/************************************************************************/

void allocater(void){
	getmemb(10);
	kprintf("1. # of bytes %d\r\n",numbytes);
	getmemb(8);
	kprintf("2. # of bytes %d\r\n",numbytes);
	getmemb(13);
	kprintf("3. # of bytes %d\r\n",numbytes);
}

int main(int argc, char **argv) {
	pid32 pid;
	kprintf("Start: # of bytes %d\r\n",numbytes);
	pid = resume(create(allocater, 2014, 20, "allocater", NULL));
	kill(pid);
	kprintf("End: # of bytes %d\r\n",numbytes);
	return OK;
}
