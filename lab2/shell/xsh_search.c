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

	char buf[];
	int32 mylen, length;
	length = 0;
//	int32 countA, countE, countI, countO, countU;

while(TRUE){
	
	mylen = pipread(pip, &buf[length],5);
	
	if (SYSERR == len) {
		fprintf(stderr,"Unable to read from pipeline\n");
		return SYSERR;
	}

	length += mylen;

	fprintf(stderr,"reader: %s\n",buf);
}
/*	
	if (SYSERR == pipdisconnect(pip)){
		fprintf(stderr,"Uable to disconnect the pipeline\n");
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

	fprintf(stderr,"A: %d\n",countA);
	fprintf(stderr,"E: %d\n",countE);
	fprintf(stderr,"I: %d\n",countI);
	fprintf(stderr,"O: %d\n",countO);
	fprintf(stderr,"U: %d\n",countU);
*/	
	return 0;
}
