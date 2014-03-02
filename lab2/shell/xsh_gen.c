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
shellcmd xsh_gen(int nargs, char *args[]) {

	// int32	retval;			/* return value			*/
	// pid32	pid;			/* ID of process to kill	*/
	// char	ch;			/* next character of argument	*/
	// char	*chptr;			/* walks along argument string	*/

	/* Output info for '--help' argument */
	//if (nargs != 1){
	//	fprintf(stderr, "%s: incorrect argument\n", args[0]);
		// fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
	//	return SYSERR;
	//}
	char word[5];
	int i;
	// pipid32 pip;

	// pip = args[1];

	for (i = 0; i < 5; i++){
		word[i] = words[rand() % 2048][i];
	}

	fprintf(stderr, "%s\n", word);

	// if (SYSERR == pipwrite(pip, word, 5){
	// 	fprintf(stderr, "Unable to write into the pipeline\n");
	// 	return SYSERR;
	// }

	return 0;
}
