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
	umsg32 len;
	int32 mylen;
	struct pipentry *piptr;
	pid32 preader;
	uint32 init_time;
	int32 nwords;

	if (pipcount < 1){
		fprintf(stderr, "No pipeline.\n");
		return SYSERR;
	}
	
	piptr = &piptab[pip];
	preader = piptr->preader;
	
	nwords = 0;
	len = 0;
	init_time = clktime;
	char word[5];
	char wordlist[5000];
//	while (clktime < init_time + 5){
	while (nwords < 20){		
		for (i = 0; i < 5; i++){
			word[i] = words[rand() % 2048][i];
			wordlist[len] = word[i];
			len++;
		}
		nwords+=1;
		if (len >= 5){
			send(preader,len);
			fprintf(stderr,"%s\n",word);
			mylen = pipwrite(pip, word, len);
			len = 0;
			if (SYSERR == mylen){
				fprintf(stderr, "Unable to write into the pipeline.\n");
	 			return SYSERR;
			}
		}
	}
	fprintf(stderr,"Number of generated words: %d\n",nwords);
	return 0;
}
