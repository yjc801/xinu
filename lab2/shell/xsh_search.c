/* xsh_search.c - xsh_search */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

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
	
	while(1){

		mylen = pipread(pip, &buf[0],256);
		if (SYSERR == mylen) {
		 	fprintf(stderr,"Unable to read from pipeline\n");
			return SYSERR;
		}

		for (i = 0; i < 256; i+=5){

			switch(buf[i]){
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
		}

		if (clktime - init > 5){
		 	fprintf(CONSOLE,"A: %d\n",countA);
			fprintf(CONSOLE,"E: %d\n",countE);
			fprintf(CONSOLE,"I: %d\n",countI);
			fprintf(CONSOLE,"O: %d\n",countO);
			fprintf(CONSOLE,"U: %d\n",countU);
		 	init = clktime;
		 	countA = countE = countI = countO = countU = 0;
		}
		
	}
	return 0;
}

