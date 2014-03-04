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

//	umsg32 len;
	int32 mylen;
	int32 init_time = clktime;
	char buf[256];
	int32 countA, countE, countI, countO, countU;

	countA = countE = countI = countO = countU = 0;
	
	while(TRUE){
		//length = 0;
		//len = receive();
		//char buf[5];
		//while(length < len){
			mylen = pipread(pip, &buf[0],256);
			if (SYSERR == mylen) {
				fprintf(stderr,"Unable to read from pipeline\n");
				break;
			}
		//	length += mylen;
			
		//}
		
		fprintf(stderr,"====== %d =====\n",mylen);
		int i;
		for (i = 0; i < 256; i++){
			fprintf(stderr,"%c",buf[i]);
		}
	
	//int32 i;
	for (i = 0; i < 256; i+=5){
		if (buf[i-1]== 'A'){
			countA++;
		}
	}

/*
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
	*/
	if ((clktime-init_time) == 10){
		fprintf(stderr,"A: %d\n",countA);
		fprintf(stderr,"E: %d\n",countE);
		fprintf(stderr,"I: %d\n",countI);
		fprintf(stderr,"O: %d\n",countO);
		fprintf(stderr,"U: %d\n",countU);
		init_time = clktime;
		countA = countE = countI = countO = countU = 0;
	}
	}
	return 0;
}

