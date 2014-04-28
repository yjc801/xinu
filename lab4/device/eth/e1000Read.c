/* e1000Read.c - e1000Read */

#include <xinu.h>

/*------------------------------------------------------------------------
 * e1000Read - read a packet from an E1000E device
 *------------------------------------------------------------------------
 */
devcall	e1000Read(
	struct	dentry	*devptr,	/* entry in device switch table	*/
	void	*buf,			/* buffer to hold packet	*/
	uint32	len			/* length of buffer		*/
	)
{
	struct	ether 	*ethptr;
	struct 	e1000_tx_desc *descptr;
	char 	*pktptr; 		
	uint32	tail;
	uint32 	tdt;

	if (len < 17){
		return SYSERR;
	}
	
	ethptr = &ethertab[devptr->dvminor];
	
	wait(ethptr->osem);

	tail = ethptr->txTail;
	descptr = (struct e1000_tx_desc *)ethptr->txRing + tail;
	pktptr = (char *)((uint32)descptr->buffer_addr & ADDR_BIT_MASK);
	memcpy(pktptr, buf, len);
	descptr->lower.data &= E1000_TXD_CMD_DEXT; 
	descptr->lower.data = E1000_TXD_CMD_IDE|E1000_TXD_CMD_RS|E1000_TXD_CMD_IFCS|E1000_TXD_CMD_EOP|len;
	descptr->upper.data = 0;
	tdt = e1000_io_readl(ethptr->iobase, E1000_TDT(0));
	tdt = (tdt + 1) % ethptr->txRingSize;
	e1000_io_writel(ethptr->iobase, E1000_TDT(0), tdt);

	ethptr->txTail = (ethptr->txTail + 1) % ethptr->txRingSize;

	return len;
}
