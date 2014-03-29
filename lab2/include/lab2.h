#ifndef NPIPE
#define NPIPE 10
#endif

#define PIPE_SIZE 256

#define PIPE_WRITER 0
#define PIPE_READER 1

typedef	int32	pipid32;		/* pipeline ID				*/

/* Pipe state definitions */

#define	INIT_PID			-1		/* Initial Process ID for reader and writer	*/
#define	INIT_PIPID			-1		/* Initial Pipe ID for process	*/

#define	PIPE_FREE		0		/* Pipe table entry is available	*/
#define	PIPE_USED		1		/* Pipe table entry is in use	*/
#define	PIPE_CONNECTED	2		/* Pipe table entry is connected	*/
#define	PIPE_OTHER		3		/* Pipe table entry is in other state	*/

#define	isbadpip(s)	((int32)(s) < 0 || (s) >= NPIPE)

typedef struct buff{
    int16		size;   /* maximum number of elements           */
    int16		start;  /* index of oldest element              */
    int16		count;    /* index at which to write new element  */
    char		elems[PIPE_SIZE];  /* vector of elements                   */
}buff;

/* Pipe table entry */
struct	pipentry	{
	uint16	pstate;
	pipid32 pwriter;
	pipid32 preader;
	bool8	piphasmsg;
	int32	buffcount;
	buff	*pipbuffer;
	// sid32	sem_empty;
	// sid32	sem_full;
};

extern	struct	pipentry piptab[];
extern int32 pipcount;   // number of pipes in use
extern sid32 mutex;
extern sid32 sem_empty;
extern sid32 sem_full;
extern char readbuff(buff *);
extern void writebuff(buff *, char);
