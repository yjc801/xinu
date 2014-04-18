/* 82545EMInit.c - _82545EMInit */

#include <xinu.h>

local 	status 	_82545EM_init_hw(struct ether *);
local 	void 	_82545EM_reset_hw(struct ether *);
local 	void 	_82545EM_configure_rx(struct ether *);
local 	void 	_82545EM_configure_tx(struct ether *);
status 	_82545EM_read_phy_reg(struct ether *, uint32, uint16 *);
status 	_82545EM_write_phy_reg(struct ether *, uint32, uint16);


/*------------------------------------------------------------------------
 * _82545EMInit - initialize Intel 82545EM Ethernet NIC
 *------------------------------------------------------------------------
 */
status 	_82545EMInit(
	struct 	ether *ethptr
	)
{
	int32	i;
	uint16	pci_commd;
	/* Read PCI configuration information */
	/* Read I/O base address */
	pci_bios_read_config_dword(ethptr->pcidev,E1000_PCI_MEMBASE,&ethptr->membase);
	pci_bios_read_config_dword(ethptr->pcidev,E1000_PCI_FLASHBASE,&ethptr->flashbase);
	pci_bios_read_config_dword(ethptr->pcidev,E1000_PCI_IOBASE,&ethptr->iobase);
	ethptr->iobase &= ~1;	

	/* Read interrupt line number */
	pci_bios_read_config_byte(ethptr->pcidev,E1000_PCI_IRQ,&ethptr->dev->dvirq);

	/* Enable PCI bus master, I/O port access */
    pci_bios_read_config_word(ethptr->pcidev,E1000E_PCI_COMMAND,&pci_commd);
    pci_bios_write_config_word(ethptr->pcidev,E1000E_PCI_COMMAND,pci_commd|0x07);

#ifdef DEBUG
    kprintf("Command reg: 0x%x\n",pci_commd);
#endif

	/* Read the MAC address */
	uint32 rar_low = e1000_io_readl(ethptr->iobase, E1000_RAL(0));
	uint32 rar_high = e1000_io_readl(ethptr->iobase, E1000_RAH(0));

	for (i = 0; i < ETH_ADDR_LEN; i++) 
		ethptr->devAddress[i] = (byte)(rar_low >> (i*8));
	for (i = 0; i < ETH_ADDR_LEN; i++)
		ethptr->devAddress[i + 4] = (byte)(rar_high >> (i*8));

#ifdef DEBUG
		kprintf("MAC address is %02x:%02x:%02x:%02x:%02x:%02x\n",
			0xff&ethptr->devAddress[0],
			0xff&ethptr->devAddress[1],
			0xff&ethptr->devAddress[2],
			0xff&ethptr->devAddress[3],
			0xff&ethptr->devAddress[4],
			0xff&ethptr->devAddress[5]);
#endif

	/* Initialize structure pointers */
    ethptr->mtu = ETH_MTU;
    ethptr->errors = 0;
    ethptr->istart = 0;
    ethptr->addrLen = ETH_ADDR_LEN;
    ethptr->rxRingSize = E1000_RX_RING_SIZE;
    ethptr->txRingSize = E1000_TX_RING_SIZE;
    ethptr->isem = semcreate(0);
    ethptr->osem = semcreate(ethptr->txRingSize);

	/* Rings must be aligned on a 16-byte boundary */
	
	
	/* Buffers are highly recommended to be allocated on cache-line */
	/* 	size (64-byte for E8400) 				*/
	

	/* Set buffer pointers and rings to zero */
	


	/* Insert the buffer into descriptor ring */
	

	/* Reset packet buffer allocation to default */



	/* Reset the NIC to bring it into a known state and initialize it */

	_82545EM_reset_hw(ethptr);

	/* Initialize the hardware */

	if (_82545EM_init_hw(ethptr) != OK)
		return SYSERR;

	/* Configure the NIC */

	e1000_io_writel(ethptr->iobase, E1000_AIT, 0);

	/* Configure the RX */

	_82545EM_configure_rx(ethptr);
	
	/* Configure the TX */

	_82545EM_configure_tx(ethptr);

	/* Register the interrupt and enable interrupt */
	
	set_evec(ethptr->dev->dvirq + IRQBASE, (uint32)e1000Dispatch);
	e1000IrqEnable(ethptr);

	return OK;
}

/*------------------------------------------------------------------------
 * _82545EM_reset_hw - Reset the hardware 
 *------------------------------------------------------------------------
 */
local void _82545EM_reset_hw(
	struct 	ether *ethptr
	)
{

	/* Masking off all interrupts */



	/* Disable the Transmit and Receive units. */



	/* Issuing a global reset by setting CTRL register with E1000_CTRL_RST*/

	
    /* Delay slightly to let hardware process */

    /* Masking off all interrupts again*/

}

/*------------------------------------------------------------------------
 * _82545EM_init_hw - Initialize the hardware
 *------------------------------------------------------------------------
 */
local status _82545EM_init_hw(
	struct 	ether *ethptr
	)
{

	/* Setup the receive address */
	/* Zero out the other receive addresses */



	/* Zero out the Multicast HASH table */



	/* Configure copper link settings */



	/* Commit the changes.*/



    /* Do a slightly delay for the hardware to proceed the commit */
	

	/* Setup autoneg and flow control advertisement and perform 	*/
	/* 	autonegotiation. 					*/




	/* Restart auto-negotiation. */



	/* Wait for auto-negotiation to complete 
       Implement a loop here to check the E1000_MII_SR_LINK_STATUS and E1000_MII_SR_AUTONEG_COMPLETE, break if they are both ture
       You should also delay for a while in each loop so it won't take too much CPU time */



    /* Update device control according receive flow control and transmit flow control*/

	return OK;
}

/*------------------------------------------------------------------------
 * _82545EM_configure_rx - Configure Receive Unit after Reset
 *------------------------------------------------------------------------
 */
local void _82545EM_configure_rx(
	struct 	ether *ethptr
	)
{


	/* Disable receiver while configuring. */


	/* Enable receiver, accept broadcast packets, no loopback, and 	*/
	/* 	free buffer threshold is set to 1/2 RDLEN. 		*/


	/* Do not store bad packets, do not pass MAC control frame, 	*/
	/* 	disable long packet receive and CRC strip 		*/
	
	
	/* Setup buffer sizes */


	/* Set the Receive Delay Timer Register, let driver be notified */
	/* 	immediately each time a new packet has been stored in 	*/
	/* 	memory 							*/


	/* Set up interrupt rate to be default. Notice that it is a the rate is not just E1000_ITR_DEFAULT which is the frequency, 
       it is 1000000000 / (E1000_ITR_DEFAULT * 256) */



	/* Setup the HW Rx Head and Tail Descriptor Pointers, the Base 	*/
	/* 	and Length of the Rx Descriptor Ring 			*/



	/* Disable Receive Checksum Offload for IPv4, TCP and UDP. */


	/* Enable receiver. */

}

/*------------------------------------------------------------------------
 * _82545EM_configure_tx - Configure Transmit Unit after Reset
 *------------------------------------------------------------------------
 */
local void _82545EM_configure_tx(
	struct 	ether *ethptr
	)
{

	/* Set the transmit descriptor write-back policy for both queues */



	/* Program the Transmit Control Register */
	


	/* Set the default values for the Tx Inter Packet Gap timer */
	


	/* Set the Tx Interrupt Delay register */
	


	/* Setup the HW Tx Head and Tail descriptor pointers */
	


    /* Enable transmit but setting TCTL*/
}

/*------------------------------------------------------------------------
 * _82545EM_read_phy_reg - Read MDI control register
 *------------------------------------------------------------------------
 */
status _82545EM_read_phy_reg(
	struct 	ether *ethptr,
	uint32 	offset,
	uint16 	*data
	)
{
	uint32 i, mdic = 0;

	if (offset > E1000_MAX_PHY_REG_ADDRESS) {
		return SYSERR;
	}

	mdic = ((offset << E1000_MDIC_REG_SHIFT) |
		(E1000_82545EM_MDIC_PHY_ADDR << E1000_MDIC_PHY_SHIFT) |
		(E1000_MDIC_OP_READ));

	e1000_io_writel(ethptr->iobase, E1000_MDIC, mdic);

	for (i = 0; i < (E1000_GEN_POLL_TIMEOUT * 3); i++) {
		DELAY(50);
		mdic = e1000_io_readl(ethptr->iobase, E1000_MDIC);
		if (mdic & E1000_MDIC_READY)
			break;
	}
	if (!(mdic & E1000_MDIC_READY)) {
		return SYSERR;
	}
	if (mdic & E1000_MDIC_ERROR) {
		return SYSERR;
	}
	*data = (uint16) mdic;

	return OK;
}

/*------------------------------------------------------------------------
 *  _82545EM_write_phy_reg - Write MDI control register
 *------------------------------------------------------------------------
 */
status _82545EM_write_phy_reg(
	struct 	ether *ethptr,
	uint32 	offset,
	uint16 	data
	)
{
	uint32 i, mdic = 0;

	if (offset > E1000_MAX_PHY_REG_ADDRESS) {
		return SYSERR;
	}

	mdic = ( ((uint32)data) |
		 (offset << E1000_MDIC_REG_SHIFT) |
		 (E1000_82545EM_MDIC_PHY_ADDR << E1000_MDIC_PHY_SHIFT) |
		 (E1000_MDIC_OP_WRITE) );

	e1000_io_writel(ethptr->iobase, E1000_MDIC, mdic);

	for (i = 0; i < (E1000_GEN_POLL_TIMEOUT * 3); i++) {
		DELAY(50);
		mdic = e1000_io_readl(ethptr->iobase, E1000_MDIC);
		if (mdic & E1000_MDIC_READY)
			break;
	}
	if (!(mdic & E1000_MDIC_READY)) {
		return SYSERR;
	}
	if (mdic & E1000_MDIC_ERROR) {
		return SYSERR;
	}

	return OK;
}
