/* xsh_search.c - xsh_search */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------------
 * xsh_search - search words
 *------------------------------------------------------------------------
 */
shellcmd xsh_search(int32 pip) {

	// int32 i;
	int32 mylen;
	char buf[5];
	int32 countA, countE, countI, countO, countU;
	int32 init;
	struct pipentry *piptr;
	
	piptr = &piptab[pip];

	if (piptr->pstate != PIPE_CONNECTED){
		fprintf(stderr, "No pipeline\n");
		return 0;
	}

	countA = countE = countI = countO = countU = 0;
	init = clktime;

	// fprintf(stderr, "Start searching\n");
	
	while(1){

		mylen = pipread(pip, &buf[0],5);
		if (SYSERR == mylen) {
		 	fprintf(stderr,"Unable to read from pipeline\n");
			return SYSERR;
		}

			switch(buf[0]){
			case 'A': 
				countA++;
				break;
			case 'E': 
				countE++;
				break;
			case 'I': 
				countI++;
				break;
			case 'O': 
				countO++;
				break;
			case 'U': 
				countU++;
				break;
			default:
				break;
			}

		if (clktime - init > 10){
		 	fprintf(stderr,"A: %d\n",countA);
			fprintf(stderr,"E: %d\n",countE);
			fprintf(stderr,"I: %d\n",countI);
			fprintf(stderr,"O: %d\n",countO);
			fprintf(stderr,"U: %d\n",countU);
		 	init = clktime;
		 	countA = countE = countI = countO = countU = 0;
		}
		
	}
	return 0;
}

