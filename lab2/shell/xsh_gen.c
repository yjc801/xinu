/* xsh_gen.c - xsh_gen */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wordlist.h>

/*------------------------------------------------------------------------
 * xsh_gen - generate words
 *------------------------------------------------------------------------
 */
shellcmd xsh_gen(int32 pip) {

	int32 i;
	int32 len;
	int32 mylen;
	int32 nwords;

	if (pipcount < 1){
		fprintf(stderr, "No pipeline.\n");
		return SYSERR;
	}
	
	
	nwords = 0;
	len = 0;
	char wordlist[1000];
	int32 value;

	while(TRUE){

		if ((clktime+1) % 5 == 0){
			fprintf(stderr,"Number of generated words: %d\n",nwords);
			nwords = 0;
		}

		while (len < 1000){		
			value = rand() % 2048;
			for (i = 0; i < 5; i++){
				wordlist[len] = words[value][i];
				len++;
			}
			nwords+=1;
		}

		len = 0;
		mylen = pipwrite(pip, wordlist, 1000);

		if (SYSERR == mylen){
			fprintf(stderr, "Unable to write into the pipeline.\n");
	 		return SYSERR;
		}
	}
	return 0;
}


