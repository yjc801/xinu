/* e1000Read.c - e1000Read */

#include <xinu.h>

/*------------------------------------------------------------------------
 * e1000Read - read a packet from an E1000 device
 *------------------------------------------------------------------------
 */
devcall	e1000Read(
	struct	dentry	*devptr,	/* entry in device switch table	*/
	void	*buf,			/* buffer to hold packet	*/
	uint32	len			/* length of buffer		*/
	)
{
	struct	ether 	*ethptr;
	struct	e1000_rx_desc *descptr;
	void	*pktptr;
	uint32	status,length,rdt;		
	int32 	retval;

	ethptr = &ethertab[devptr->dvminor];

	wait(ethptr->isem);

	descptr = (struct e1000_rx_desc *)ethptr->rxRing + ethptr->rxHead;
	status = descptr->status;

	if (!(status & E1000_RXD_STAT_DD)){ 
		retval = SYSERR;
	}else{
		pktptr = (void *)((uint64)(descptr->buffer_addr & ADDR_BIT_MASK));
		length = descptr->length;
		memcpy(buf, pktptr, length);
		retval = length;
	}

	descptr->status = 0;
	descptr->errors = 0;
	descptr->length = 0;
	descptr->special = 0;
	descptr->csum = 0;
	
	memset((void *)((uint64)(descptr->buffer_addr & ADDR_BIT_MASK)),'\0',ETH_BUF_SIZE); 

	if (ethptr->rxHead % E1000_RING_BOUNDARY == 0) {
		rdt = e1000_io_readl(ethptr->iobase, E1000_RDT(0));
		rdt = (rdt + E1000_RING_BOUNDARY) % ethptr->rxRingSize;
		e1000_io_writel(ethptr->iobase, E1000_RDT(0), rdt);
	}

	ethptr->rxHead = (ethptr->rxHead + 1)%ethptr->rxRingSize;

	return retval;
}
