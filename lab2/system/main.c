/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/
void writer(pipid32, int);
void reader(pipid32, int);
char words[10] = "Hello world!";

int main(int argc, char **argv)
{
//	umsg32 retval;
	pipid32 pipid;
	pid32 wrpid;
	pid32 repid;

	pip = pipcreate();
	
	if (SYSERR == pip)
		return 1;
	
	wrpid = create(writer, 2048, 20, "writer", 2, pip, 5);
	repid = create(reader, 2048, 20, "reader", 2, pip, 5);
	
	if (SYSERR == pipconnect(pip, wrpid, repid)) {
		return 1;
	}
	
	kprintf("[main]: Pipe connected!\r\n");
	resume(wrpid);
	resume(repid);
	sleepms(1000);
	// kprintf("the string: %s\r\n", words);
	while(1) {
		sleep(100);
	}
	return OK;
}

void writer(pipid32 pip, int len){
	// kprintf("[wr]: wr %d chars\r\n", len);
	if (SYSERR == pipwrite(pip, words, 7500)) {
		kprintf("[wr]: Sucks!\r\n");
	}

	if (SYSERR == pipdisconnect(pip)) {
		kprintf("[wr]: disc suck\r\n");
	}
	return;
}

void reader(pipid32 pip, int len) {
	// kprintf("[Rd]: rd %d chars\r\n", len);
	int length = 0;
	char mybuf[7500];
	int mylen;
	
	while (length < 7500) {
		mylen = pipread(pip, &mybuf[length], 7500-length);
		if (SYSERR == mylen) {
			kprintf("[rd]: Sucks!\r\n");
		break;
		}
		length += mylen;
	}
	
	kprintf("[reader]: string-- %s\r\n", mybuf);
	return;
}