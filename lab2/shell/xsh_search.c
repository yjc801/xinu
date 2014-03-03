/* xsh_search.c - xsh_search */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------------
 * xsh_gen - generate words
 *------------------------------------------------------------------------
 */
shellcmd xsh_search(int nargs, char *args[]) {

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
	pipid32 pip;
	char buf[5];
	int32 len;

	pip = (pipid32) args[1];
	
	len = pipread(pip, &buf[0], 5);

	if (SYSERR == len) {
		fprintf(stderr,"Unable to read from pipeline\n");
		return SYSERR;
	}else{
		fprintf(stderr,"%s",buf);
	}
	// if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
	// 	printf("Usage: %s PID\n\n", args[0]);
	// 	printf("Description:\n");
	// 	printf("\tterminates a process\n");
	// 	printf("Options:\n");
	// 	printf("\tPID \tthe ID of a process to terminate\n");
	// 	printf("\t--help\tdisplay this help and exit\n");
	// 	return OK;
	// }

	// /* Check argument count */

	// if (nargs != 2) {
	// 	fprintf(stderr, "%s: incorrect argument\n", args[0]);
	// 	fprintf(stderr, "Try '%s --help' for more information\n",
	// 		args[0]);
	// 	return SYSERR;
	// }

	// // compute process ID from argument string 

	// chptr = args[1];
	// ch = *chptr++;
	// pid = 0;
	// while(ch != NULLCH) {
	// 	if ( (ch < '0') || (ch > '9') ) {
	// 		fprintf(stderr, "%s: non-digit in process ID\n",
	// 			args[0]);
	// 		return 1;
	// 	}
	// 	pid = 10*pid + (ch - '0');
	// 	ch = *chptr++;
	// }
	// if (pid == 0) {
	// 	fprintf(stderr, "%s: cannot kill the null process\n",
	// 		args[0]);
	// 	return 1;
	// }

	// retval = kill(pid);
	// if (retval == SYSERR) {
	// 	fprintf(stderr, "%s: cannot kill process %d\n",
	// 		args[0], pid);
	// 	return 1;
	// }
	return 0;
}
