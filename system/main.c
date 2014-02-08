#include <xinu.h>
/* test1.c
 * This test program creates three processes, prA, prB, and prC, at
 * priority 20.  The main process also has priority 20.
 */

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
<<<<<<< HEAD

	kprintf("The priority of Prop gourp is %d.\n",propcounter);
	kprintf("The priority of TS gourp is %d.\n",tscounter);
=======
>>>>>>> d392c272ba523ee1f1a8cb16c262ad8717efb6b5
}

prch(c)
{      char c;

	int i;

	while(1) {
		kprintf("%c", c);
		for (i=0; i< 10000; i++);
	}
}
