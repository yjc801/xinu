#include <xinu.h>

int prchcpu(char c, char d, int s);
int prchio(char c, char d, int s);

int prA,  prB,  prC, prD;

int round;


int main(int argc, char **argv){
		round = 3000;
		
		kprintf("\n\nPS TEST:\n");
		resume( create(prchcpu, 2000, TSSCHED, 20, "proc A", 3, 'A', 'a', 100) );
		resume( create(prchcpu, 2000, TSSCHED, 20, "proc B", 3, 'B', 'b', 100) );
		resume( create(prchio, 2000, TSSCHED, 20, "proc C", 3, 'C', 'c', 50) );
		resume( create(prchio, 2000, TSSCHED, 20,  "proc D", 3, 'D', 'd', 100) );
		
		while (1) {
			sleep(1);					
		}
		return OK;
}

int prchcpu(char c, char d, int s){
//		sleepms(s);
		kprintf("%c", d);
		int i;
		for(i=0; i<round; i++){
			kprintf("%d",  proctab[currpid].prprio);
			kprintf("%c",  c);
		}
		kprintf("%c", d);
		return 0;
}

int prchio(char c, char d, int s){
//		sleepms(s);
		kprintf("%c", d);
		int i, j;
		int innerr = 3;
		int outerr = round/innerr;
		for(i=0; i<outerr; i++){
			kprintf("%d", proctab[currpid].prprio);
			for(j=0; j<innerr; j++)
				kprintf("%c",  c);
			sleepms(s);
		}
		kprintf("%c", d);
		return 0;
}

