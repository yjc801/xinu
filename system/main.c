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

int prch(), prA, prB, prC;

main()
{
	int i;

	kprintf("\n\nTEST1:\n");
	resume(prA = create(prch,2000,0,20,"proc A",1,'A'));
	resume(prB = create(prch,2000,0,20,"proc B",1,'B'));
	resume(prC = create(prch,2000,0,20,"proc C",1,'C'));

	while (1) {
		kprintf("%c", 'D');
		for (i=0; i< 10000; i++);
	}

	kprintf("The priority of Prop gourp is %d.\n",propcounter);
	kprintf("The priority of TS gourp is %d.\n",tscounter);
}

prch(c)
{      char c;

	int i;

	while(1) {
		kprintf("%c", c);
		for (i=0; i< 10000; i++);
	}
}
