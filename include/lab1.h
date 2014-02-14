#define PROPORTIONALSHARE 0
#define TSSCHED 1
#define	isbadgroup(x) (((int)x != PROPORTIONALSHARE) && ((int)x != TSSCHED))

#define INITGPPRIO_PROP 10
#define INITGPPRIO_TS 10

#define MAXINT 32767     /**< maximum value of int16 */
#define	isbadgid(x)	((pid32)(x) != 0) && (pid32)(x) != 1))

extern pri16 propprio; // priority for proprotional group
extern pri16 tsprio; // priority for ts group
