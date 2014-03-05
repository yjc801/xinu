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

	int32 i;
	int32 mylen;
	char buf[256];
	int32 countA, countE, countI, countO, countU;
	int32 init;
	countA = countE = countI = countO = countU = 0;
	
	init = clktime;

	fprintf(stdout,"Start searching..\n");
	
	while(TRUE){
		if (clktime - init > 5){
		 	fprintf(stdout,"A: %d\n",countA);
			fprintf(stdout,"E: %d\n",countE);
			fprintf(stdout,"I: %d\n",countI);
			fprintf(stdout,"O: %d\n",countO);
			fprintf(stdout,"U: %d\n",countU);
		 	init = clktime;
		 	countA = countE = countI = countO = countU = 0;
		}
		
		mylen = pipread(pip, &buf[0],256);
		printf("%d\n", mylen);
		if (SYSERR == mylen) {
		 	fprintf(stderr,"Unable to read from pipeline\n");
			return SYSERR;
		}

		
		for (i = 0; i < 256; i+=5){

			switch(buf[i]){
			case 'A': 
				countA++;
				continue;
			case 'E': 
				countE++;
				continue;
			case 'I': 
				countI++;
				continue;
			case 'O': 
				countO++;
				continue;
			case 'U': 
				countU++;
				continue;
			default:
				continue;
			}
		}
	}
	return 0;
}

