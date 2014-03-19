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
	int32 nwords;
	int32 init;
	char wordlist[5];
	int32 value;
	struct pipentry *piptr;
	
	piptr = &piptab[pip];

	if (piptr->pstate != PIPE_CONNECTED){
		fprintf(stderr, "No pipeline\n");
		return 0;
	}
	
	fprintf(CONSOLE,"Start generating\n");

	nwords = 0;
	init = clktime;


	while(1){
		len = 0;
		value = rand() % 2048;
		for (i = 0; i < 5; i++){
			wordlist[len] = words[value][i];
			len++;
		}
		nwords+=1;
		
		if (SYSERR == pipwrite(pip, wordlist, 5)){
			fprintf(stderr, "Unable to write into the pipeline.\n");
	 		return SYSERR;
		}

		if (clktime - init > 5){
			fprintf(CONSOLE,"Number of generated words: %d\n",nwords);
			nwords = 0;
			init = clktime;
		}
	}
	return 0;
}


