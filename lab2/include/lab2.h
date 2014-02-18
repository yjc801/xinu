#ifndef NPIPE
#define NPIPE 10
#endif

typedef	int32	pipid32;		/* semaphore ID				*/

/* Pipe state definitions */

#define	PIPE_FREE		0		/* Pipe table entry is available	*/
#define	PIPE_USED		1		/* Pipe table entry is in use	*/
#define	PIPE_CONNECTED	2		/* Pipe table entry is connected	*/
#define	PIPE_OTHER		3		/* Pipe table entry is in other state	*/


/* Pipe table entry */
struct	pipentry	{
	uint16	pipstate;
	qid16	pipqueue;	
};

extern	struct	pipentry piptab[];

#define	isbadpip(s)	((int32)(s) < 0 || (s) >= NPIPE)


extern int32 pipcount;