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

	char word[5];
	int32 i;
	int32 mylen;
	int j = 0;

	if (pipcount < 1){
		fprintf(stderr, "No pipeline.\n");
		return SYSERR;
	}
while (j < 5){
	j++;
	for (i = 0; i < 5; i++){
		word[i] = words[rand() % 2048][i];
	}
	
	fprintf(stderr,"writer: %s\n",word);

	mylen = pipwrite(pip, word, 7500);

	if (SYSERR == len){
		fprintf(stderr, "Unable to write into the pipeline.\n");
	 	return SYSERR;
	}

}
	return 0;
}
