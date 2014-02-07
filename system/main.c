/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/

int32 propcounter; //counter for propotional group
int32 tscounter; //counter for ts group

int main(int argc, char **argv)
{
	kprintf("Hello World!\n");
	kprintf("The priority of Prop gourp is %d.\n",propcounter);
	kprintf("The priority of TS gourp is %d.\n",tscounter);
	return OK;
}
