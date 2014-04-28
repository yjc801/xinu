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
	struct	e1000_rx_desc *descptr;
	char	*pktptr;
	uint32	head;			
	uint32	status;			
	uint32	length;		
	int32 	retval;
	uint32 	rdt;

	ethptr = &ethertab[devptr->dvminor];

	/* Wait for a packet to arrive */

	wait(ethptr->isem);

	/* Find out where to pick up the packet */

	head = ethptr->rxHead;
	descptr = (struct e1000_rx_desc *)ethptr->rxRing + head;
	status = descptr->status;

	if (!(status & E1000_RXD_STAT_DD)) { 	/* check for error */
		kprintf("e1000_read: packet error!\n");
		retval = SYSERR;
	} else { 	/* pick up the packet */			
		pktptr = (char *)((uint32)(descptr->buffer_addr &
					   ADDR_BIT_MASK));
		length = descptr->length;
		memcpy(buf, pktptr, length);
		retval = length;
	}
	/* Clear up the descriptor and the buffer */

	descptr->length = 0;
	descptr->csum = 0;
	descptr->status = 0;
	descptr->errors = 0;
	descptr->special = 0;
	memset((char *)((uint32)(descptr->buffer_addr & ADDR_BIT_MASK)), 
			'\0', ETH_BUF_SIZE); 

	/* Add newly reclaimed descriptor to the ring */

	if (ethptr->rxHead % E1000_RING_BOUNDARY == 0) {
		rdt = e1000_io_readl(ethptr->iobase, E1000_RDT(0));
		rdt = (rdt + E1000_RING_BOUNDARY) % ethptr->rxRingSize;
		e1000_io_writel(ethptr->iobase, E1000_RDT(0), rdt);
	}

	/* Advance the head pointing to the next ring descriptor which 	*/
	/*  	will be ready to be picked up 				*/
	ethptr->rxHead = (ethptr->rxHead + 1) % ethptr->rxRingSize;

	return retval;
}
