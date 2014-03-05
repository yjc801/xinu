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
	
	while(TRUE){
		
		if (clktime - init > 1){
		 	printf("A: %d\n",countA);
		// 	fprintf(stderr,"E: %d\n",countE);
		// 	fprintf(stderr,"I: %d\n",countI);
		// 	fprintf(stderr,"O: %d\n",countO);
		// 	fprintf(stderr,"U: %d\n",countU);
		 	countA = countE = countI = countO = countU = 0;
		}
		
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
	}
	return 0;
}

