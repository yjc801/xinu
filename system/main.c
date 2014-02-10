#include <xinu.h>

void prch(char a);

int main(void){
	int i;
	kprintf("Hello World!\r\n");
	resume(create(prch("A"),1024,1,10,"proc A",0));
	resume(create(prch("B"),1024,1,5,"proc B",0));
	for(i=0;i<4;i++){
		kprintf("D\r\n");
	}
	return OK;
}

void prch(char a){
	int i;
	for(i=0;i<4;i++){
		kprintf("%s\r\n",a);
	}
}
