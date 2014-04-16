/* e1000Interrupt.c - e1000Interrupt */

#include <xinu.h>

/*------------------------------------------------------------------------
 * e1000_rxPackets - handler for receiver interrupts
 *------------------------------------------------------------------------
 */
local 	void 	e1000_rxPackets(
	struct 	ether 	*ethptr 	/* ptr to control block		*/
	)
{
	struct	e1000_rx_desc *descptr;/* ptr to ring descriptor 	*/
	uint32	tail;			/* pos to insert next packet	*/
	uint32	status;			/* status of ring descriptor 	*/
	int numdesc; 			/* num. of descriptor reclaimed	*/

	for (numdesc = 0; numdesc < ethptr->rxRingSize; numdesc++) {

		/* Insert new arrived packet to the tail */

		tail = ethptr->rxTail;
		descptr = (struct e1000_rx_desc *)ethptr->rxRing + tail;
		status = descptr->status;

		if (status == 0) {
			break;
		}

		ethptr->rxTail 
			= (ethptr->rxTail + 1) % ethptr->rxRingSize;
	}

	signaln(ethptr->isem, numdesc);

	return;
}

/*------------------------------------------------------------------------
 * e1000_txPackets - handler for transmitter interrupts
 *------------------------------------------------------------------------
 */
local 	void 	e1000_txPackets(
	struct	ether *ethptr		/* ptr to control block		*/
	)
{
	struct	e1000_tx_desc *descptr;/* ptr to ring descriptor 	*/
	uint32 	head; 			/* pos to reclaim descriptor	*/
	char 	*pktptr; 		/* ptr used during packet copy  */
	int 	numdesc; 		/* num. of descriptor reclaimed	*/

	for (numdesc = 0; numdesc < ethptr->txRingSize; numdesc++) {
		head = ethptr->txHead;
		descptr = (struct e1000_tx_desc *)ethptr->txRing + head;

		if (!(descptr->upper.data & E1000_TXD_STAT_DD))
			break;

		/* Clear the write-back descriptor and buffer */

		descptr->lower.data = 0;
		descptr->upper.data = 0;
		pktptr = (char *)((uint32)(descptr->buffer_addr &
					   ADDR_BIT_MASK));
		memset(pktptr, '\0', ETH_BUF_SIZE);

		ethptr->txHead 
			= (ethptr->txHead + 1) % ethptr->txRingSize;
	}

	signaln(ethptr->osem, numdesc);

	return;
}


/*------------------------------------------------------------------------
 * e1000Interrupt - decode and handle interrupt from an E1000 device
 *------------------------------------------------------------------------
 */
interrupt e1000Interrupt(void)
{
	uint32	status;
	struct  dentry  *devptr;        /* address of device control blk*/
	struct 	ether 	*ethptr;	/* ptr to control block		*/

	/* Initialize structure pointers */

	devptr = (struct dentry *) &devtab[ETHER0];
	
	/* Obtain a pointer to the tty control block */

	ethptr = &ethertab[devptr->dvminor];

	/* Invoke the device-specific interrupt handler */

	/* Disable device interrupt */

	e1000IrqDisable(ethptr);

	/* Obtain status bits from device */

	status = e1000_io_readl(ethptr->iobase, E1000_ICR);

	/* Not our interrupt */

	if (status == 0) {
		e1000IrqEnable(ethptr);
		return;
	}

	sched_cntl(DEFER_START);

	if (status & E1000_ICR_LSC) {
	}

	if (status & E1000_ICR_RXT0) {
		ethptr->rxIrq++;
		e1000_rxPackets(ethptr);
	}

	if (status & E1000_ICR_TXDW) {
		ethptr->txIrq++;
		e1000_txPackets(ethptr);
	}

	/* Enable device interrupt */

	e1000IrqEnable(ethptr);
	
	sched_cntl(DEFER_STOP);

	return;
}
