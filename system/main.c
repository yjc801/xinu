#include <xinu.h>
 
void prchP(char, char);
void prchT(char, char);
int prA, prB, prC, prD;
int round;
unsigned long ctr100;

int main(void){
	round = 500;
	resume( prA = create(prchP, 2000, PROPORTIONALSHARE, 20, "proc A", 2, 'A', 'A') );
	resume( prB = create(prchP, 2000, PROPORTIONALSHARE, 50, "proc B", 2, 'B', 'B') );
	 resume( prD = create(prchP, 2000, TSSCHED, 25, "proc D", 2, 'D', 'D') );
	 chgprio(TSSCHED,20);
	// resume( prC = create(prchP, 2000, TSSCHED, 20, "proc C", 2, 'C', 'C'));

//while (1) {
//	sleepms(100); 
//	}
	return OK;
}

void prchP(char c, char d){
	//sleepms(50);
	//kprintf("Proc %c starts!\r\n", c);
	int i;
	for(i=0; i<round; i++){
		kprintf("%c", d);
	}
	//kprintf("Proc %c ends! \r\n", c);
}

void prchT(char c, char d){
	sleepms(50);
	//kprintf("Proc %c starts!\r\n", c);
	int i;
	for(i=0; i<round; i++){
		kprintf("%c", d);
		if(i%50 == 0) sleep(1);
	}
}


