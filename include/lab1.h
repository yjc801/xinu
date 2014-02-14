#define PROPORTIONALSHARE 0
#define TSSCHED 1
#define	isbadgroup(x) (((int)x != PROPORTIONALSHARE) && ((int)x != TSSCHED))

#define MAXINT 32767     /**< maximum value of int16 */

extern pri16 INITGPPRIO_PROP;
extern pri16  INITGPPRIO_TS;
extern pri16  propprio;
extern pri16  tsprio;
