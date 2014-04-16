/* e1000Control.c - e1000Control, e1000IrqEnable, e1000IrqDisable */

#include <xinu.h>

/*------------------------------------------------------------------------
 * e1000Control - implement control function for an E1000 device
 *------------------------------------------------------------------------
 */
devcall	e1000Control(
	struct	dentry	*devptr,	/* entry in device switch table	*/
	int32	func,			/* control function		*/
	int32	arg1,			/* argument 1, if needed 	*/
	int32	arg2			/* argument 2, if needed	*/
	)
{
	struct	ether	*ethptr; 	/* pointer to control block	*/
	uint32 rar_low, rar_high;
	uint8 *addr;


	ethptr = &ethertab[devptr->dvminor];

	switch (func) {

		/* Get MAC address */

		case ETH_CTRL_GET_MAC:
			memcpy((byte *)arg1, ethptr->devAddress, 
					ETH_ADDR_LEN);
			break;

		case ETH_CTRL_SET_MAC:
			addr = (uint8 *)arg1;
			rar_low = ((uint32) addr[0] |
				  ((uint32) addr[1] << 8) |
				  ((uint32) addr[2] << 16) | 
				  ((uint32) addr[3] << 24));

			rar_high = ((uint32) addr[4] | 
				   ((uint32) addr[5] << 8));

			if (rar_low || rar_high)
				rar_high |= E1000_RAH_AV;

			e1000_io_writel(ethptr->iobase, E1000_RAL(arg2), 
					rar_low);
			e1000_io_flush(ethptr->iobase);
			e1000_io_writel(ethptr->iobase, E1000_RAH(arg2), 
					rar_high);
			e1000_io_flush(ethptr->iobase);
			
			break;

		default:
			return SYSERR;
	}

	return OK;
}

/*------------------------------------------------------------------------
 * e1000IrqDisable - Mask off interrupt generation on the NIC
 *------------------------------------------------------------------------
 */
void e1000IrqDisable(
	struct 	ether *ethptr
	)
{
	e1000_io_writel(ethptr->iobase, E1000_IMC, ~0);

	e1000_io_flush(ethptr->iobase);
}

/*------------------------------------------------------------------------
 * e1000_irq_enable - Enable default interrupt generation settings
 *------------------------------------------------------------------------
 */
void e1000IrqEnable(
	struct 	ether *ethptr
	)
{
	e1000_io_writel(ethptr->iobase, E1000_IMS, E1000_IMS_ENABLE_MASK);

	e1000_io_flush(ethptr->iobase);
}
