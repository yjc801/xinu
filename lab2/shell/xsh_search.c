/* xsh_search.c - xsh_search */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------------
 * xsh_gen - generate words
 *------------------------------------------------------------------------
 */
shellcmd xsh_search(int32 pip) {
/*
	char buf[5];
	int32 len;
	int32 countA, countE, countI, countO, countU;
	
	len = pipread(pip, &buf[0], 5);

	if (SYSERR == len) {
		fprintf(stderr,"Unable to read from pipeline\n");
		return SYSERR;
	}
	fprintf(stderr,"reader: %s\n",buf);
	
	switch(buf[0]){
	case 'A': countA++;
	case 'E': countE++;
	case 'I': countI++;
	case 'O': countO++;
	case 'U': countU++;
	default:
		break;
	}
	fprintf(stderr,"A: %d\n",countA);
	fprintf(stderr,"E: %d\n",countE);
	fprintf(stderr,"I: %d\n",countI);
	fprintf(stderr,"O: %d\n",countO);
	fprintf(stderr,"U: %d\n",countU);
*/	
	fprintf(stderr,"reader: Hello!\n");
	return 0;
}
