#include <xinu.h>

void prch(void);

int main(void){
	int i;
	kprintf("Hello World!\r\n");
	resume(create(prch,1024,1,10,"proc A",0));
	resume(create(prch,1024,0,5,"proc B",0));
	for(i=0;i<4;i++){
		kprintf("D\r\n");
	}
	return OK;
}

void prch(void){
	int i;
	for(i=0;i<4;i++){
		kprintf("A\r\n");
	}
}
