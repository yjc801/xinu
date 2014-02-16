#define PROPORTIONALSHARE 0
#define TSSCHED 1
#define	isbadgroup(x) (((int)x != PROPORTIONALSHARE) && ((int)x != TSSCHED))
#define	isbadrate(x) ((pri16)x < 1 || (pri16)x > 100)

#define MAXINT 32767     /**< maximum value of int16 */

extern pri16 rate_sum; // sum of the rates of all proportional processess, should <= 100
extern pri16 INITGPPRIO_PROP; // initial prio of proportional group
extern pri16  INITGPPRIO_TS; // initial prio of TS group
extern pri16  propprio; // current prio of prop group
extern pri16  tsprio; // current prio of TS group
