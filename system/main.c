#include <xinu.h>
 
void prchP(char c, char d);
void prchT(char c, char d);
int prA, prB, prC;
int round;
unsigned long ctr100;

main(){
	round = 1000;
	resume( prA = create(prchP, 2000, PROPORTIONALSHARE, 30, "proc A", 2, 'A', 'A') );
	resume( prB = create(prchP, 2000, PROPORTIONALSHARE, 50, "proc B", 2, 'B', 'B') );
// resume( prC = create(prch, 2000, 15, TSSCHED, "proc C", 2, 'C', 'C’') );

while (1) {
	sleepms(10000); 
	}
}

void prchP(char c, char d){
	sleepms(500);
	kprintf("Proc %c starts!\r\n", c);
	int i;
	for(i=0; i<round; i++){
		kprintf("%c", d);
	}
	kprintf("Proc %c ends! \r\n", c);
}

void prchT(char c, char d){
	sleepms(500);
	kprintf("Proc %c starts!\r\n", c);
	int i;
	for(i=0; i<round; i++){
		kprintf("%c", d);
		if(i%50 == 0) sleep(1);
	}
}