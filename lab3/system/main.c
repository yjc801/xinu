#include <xinu.h>


void PrintList(void);
void RequestMem(int base, int round, bool8 sflag, int pflag);
int main (int argc, char **argv) {

	kprintf("Heap: %x, size %d\r\n", memlist.mnext, memlist.mnext->mlength);
//	char *addr = getmem(560);
//	kprintf("return addr: %x\r\n", addr);
	resume(create(RequestMem, 2048, 20, "Test1", 4, 300, 10, 0, 1));
	sleep(5);
	resume(create(RequestMem, 2048, 20, "Test2", 4, 300, 10, 0, 2));
	sleep(5);

	resume(create(RequestMem, 2048, 20, "Test3-1", 4, 400, 20, 1, 10));
	resume(create(RequestMem, 2048, 20, "Test3-2", 4, 400, 20, 1, 5));
	sleep(10);
	kprintf("Final\r\n");
	PrintList();
	return 1;

}


void PrintList(void) {

	struct memblk *root;

	root = memlist.mnext;
	kprintf("Block List:\r\n");
	while (NULL != root) {
		kprintf("addr %x, size %d\r\n", root, root->mlength);
		root = root->mnext;
	}

	return;
}

void RequestMem(int base, int round, bool8 sflag, int pflag) {

	int i, len, prevlen;
	if (pflag)
		sleep(2);
	char *prev, *curr;
	prev = getmemgb(7);
	kprintf("new %d, %x, siz %d\r\n", 0, prev, 7);
	for (i=1; i<round; ++i) {
		len = 7 + base * i;
		curr = getmemgb(len);
		if (sflag)
			sleepms(100);
		
		prevlen = 7 + base * (i-1);
		if (0 == i % pflag)
			freememgb(prev, prevlen);
		prev = curr;
	}	
	if (pflag > 5)
		sleepms(1500);
	kprintf("\r\n");
	PrintList();
	return;
}

