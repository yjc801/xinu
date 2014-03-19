#include <xinu.h>

int prch(char c, char d, int s);
int prA, prB, prC, prD;

int round;


int main(void){
round = 10000;

kprintf("\n\nPS TEST:\n");
resume( prA = create(prch, 2000, PROPORTIONALSHARE, 40, "proc A", 3, 'A', 'a', 100) );
resume( prB = create(prch, 2000, PROPORTIONALSHARE, 30, "proc B", 3, 'B', 'b', 100) );
resume( prC = create(prch, 2000, PROPORTIONALSHARE, 20, "proc C", 3, 'C', 'c', 100) );
resume( prD = create(prch, 2000, PROPORTIONALSHARE, 10, "proc D", 3, 'D', 'd', 0) );


while (1) {
sleep(1);
}

return 1;
}

int prch(char c, char d, int s){
sleepms(s);
kprintf("%c", d);
int i;
for(i=0; i<round; i++){
kprintf("%c", c);
}
kprintf("%c", d);
return 0;
}

 
