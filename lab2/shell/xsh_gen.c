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

	//int32 i;
	int32 len;
	int32 mylen;
	//struct pipentry *piptr;
	//pid32 preader;
	uint32 init_time;
	int32 nwords;

	if (pipcount < 1){
		fprintf(stderr, "No pipeline.\n");
		return SYSERR;
	}
	
	//piptr = &piptab[pip];
	//preader = piptr->preader;
	
	nwords = 0;
	len = 0;
	init_time = clktime;
	//char word[5];
	char wordlist[256];
	int32 value;
	//fprintf(stderr,"init_time %d\n",init_time);
	//while (clktime - init_time < 5){
	while(TRUE){
	//	fprintf(stderr,"clk_time %d\n",clktime);
		while (len < 256){		
			value = rand() % 2048;
			//for (i = 0; i < 5; i++){
				wordlist[len] = words[value][0];
			//	wordlist[len] = word[i];
				len++;
			//}
			nwords+=1;
		}
		len = 0;
		mylen = pipwrite(pip, wordlist, 256);
		if (SYSERR == mylen){
			fprintf(stderr, "Unable to write into the pipeline.\n");
	 		return SYSERR;
		}
		if ((clktime - init_time) > 5){
			fprintf(stderr,"Number of generated words: %d\n",nwords);
			init_time = clktime;
			nwords = 0;
		} 
	}
	return 0;
}


