/* 82545EMInit.c - _82545EMInit */

#include <xinu.h>
#define DEBUG

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
	int32  i;
	struct e1000_rx_desc *rx_ringptr;
	struct e1000_tx_desc *tx_ringptr;
	uint32 bufptr;
	uint16 pci_commd;

	/* Read PCI configuration information */
	/* Read I/O base address */
	pci_bios_read_config_dword(ethptr->pcidev,E1000_PCI_MEMBASE,&ethptr->membase);
	pci_bios_read_config_dword(ethptr->pcidev,E1000_PCI_FLASHBASE,&ethptr->flashbase);
	pci_bios_read_config_dword(ethptr->pcidev,E1000_PCI_IOBASE,&ethptr->iobase);
	ethptr->iobase &= ~1;	

	/* Read interrupt line number */
	pci_bios_read_config_byte(ethptr->pcidev,E1000_PCI_IRQ,&ethptr->dev->dvirq);

	/* Enable PCI bus master, I/O port access */
    pci_bios_read_config_word(ethptr->pcidev,E1000_PCI_COMMAND,&pci_commd);
    pci_bios_write_config_word(ethptr->pcidev,E1000_PCI_COMMAND,pci_commd|0x07);

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
	ethptr->rxRing = (struct e1000_rx_desc *) getmem(E1000_RDSIZE*(E1000_RX_RING_SIZE+1));
	ethptr->rxRing = ((uint32)ethptr->rxRing + 0xf) & ~0xf;
	ethptr->txRing = (struct e1000_tx_desc *) getmem(E1000_TDSIZE*(E1000_TX_RING_SIZE+1)); 
	ethptr->txRing = ((uint32)ethptr->txRing + 0xf) & ~0xf;

	/* Buffers are highly recommended to be allocated on cache-line */
	/* 	size (64-byte for E8400) 				*/
	ethptr->rxBufs = (struct etherPkt *) getmem(ETH_BUF_SIZE*E1000_RX_RING_SIZE);
	ethptr->rxBufs = ((uint32)ethptr->rxBufs + 0x3f) & ~0x3f;
	ethptr->txBufs = (struct etherPkt *) getmem(ETH_BUF_SIZE*E1000_TX_RING_SIZE);
	ethptr->txBufs = ((uint32)ethptr->txBufs + 0x3f) & ~0x3f;
	
	if ( (SYSERR == (uint32)ethptr->rxBufs)
		|| (SYSERR == (uint32)ethptr->txBufs)){
		return SYSERR;
	}
	
	/* Set buffer pointers and rings to zero */
	memset(ethptr->rxRing, '\0', E1000_RDSIZE * E1000_RX_RING_SIZE);
	memset(ethptr->txRing, '\0', E1000_TDSIZE * E1000_TX_RING_SIZE);	
	memset(ethptr->rxBufs, '\0', E1000_RX_RING_SIZE * ETH_BUF_SIZE);
	memset(ethptr->txBufs, '\0', E1000_TX_RING_SIZE * ETH_BUF_SIZE);

	/* Insert the buffer into descriptor ring */

	rx_ringptr = (struct e1000_rx_desc*)ethptr->rxRing;
	bufptr = (uint32)ethptr->rxBufs;
	for (i = 0; i < E1000_RX_RING_SIZE; i++) {
		rx_ringptr->buffer_addr = (uint64)bufptr;
		rx_ringptr++;
		bufptr += ETH_BUF_SIZE;
	}	

	tx_ringptr = (struct e1000_tx_desc*)ethptr->txRing;
	bufptr = (uint32)ethptr->txBufs;
	for (i = 0; i < E1000_TX_RING_SIZE; i++) {
		tx_ringptr->buffer_addr = (uint64)bufptr;
		tx_ringptr++;
		bufptr += ETH_BUF_SIZE;
	}

	/* Reset packet buffer allocation to default */

	// manual p. 292 PBA
	e1000_io_writel(ethptr->iobase, E1000_PBA, E1000_PBA_10K << 16 | E1000_PBA_48K);

#ifdef DEBUG
    kprintf("PBA reset: 0x%x\n",E1000_PBA_10K << 16 | E1000_PBA_48K);
#endif

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
	uint32 ctrl;

	/* Masking off all interrupts */

	/* manual p. 297  if software desires to disable a particular 
	interrupt condition that had been previously enabled, it must
	write to the Interrupt Mask Clear Register */

	e1000_io_writel(ethptr->iobase, E1000_IMC, ~0);

	/* Disable the Transmit and Receive units. */

	// manual p.300
	e1000_io_writel(ethptr->iobase, E1000_RCTL, 0);
	e1000_io_writel(ethptr->iobase, E1000_TCTL, 0);

	/* Issuing a global reset by setting CTRL register with E1000_CTRL_RST*/
	ctrl = e1000_io_readl(ethptr->iobase, E1000_CTRL);
	e1000_io_writel(ethptr->iobase, E1000_CTRL, ctrl|E1000_CTRL_RST);

    /* Delay slightly to let hardware process */
	MDELAY(50);

    /* Masking off all interrupts again*/
	e1000_io_writel(ethptr->iobase, E1000_IMC, ~0);
}

/*------------------------------------------------------------------------
 * _82545EM_init_hw - Initialize the hardware
 *------------------------------------------------------------------------
 */
local status _82545EM_init_hw(
	struct 	ether *ethptr
	)
{
	uint32 i;
	uint32 ctrl;
	uint16 phy_ctrl, phy_1000t_ctrl, autoneg_adv, phy_status;

	/* Setup the receive address */
	/* Zero out the other receive addresses */
	for(i = 1; i < E1000_82567LM_RAR_ENTRIES; i++){
		e1000_io_writel(ethptr->iobase, E1000_RAL(i), 0);
		e1000_io_writel(ethptr->iobase, E1000_RAH(i), 0);
	}


	/* Zero out the Multicast HASH table */
	for (i = 0; i < E1000_82567LM_MTA_ENTRIES; i++){
		e1000_io_writel(ethptr->iobase, E1000_MTA + i*4, 0);
	}


	/* Configure copper link settings */
	ctrl = e1000_io_readl(ethptr->iobase, E1000_CTRL);
	ctrl |= E1000_CTRL_SLU;
	// ctrl &= ~(E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);


	/* Commit the changes.*/
	e1000_io_writel(ethptr->iobase, E1000_CTRL, ctrl);


    /* Do a slightly delay for the hardware to proceed the commit */
	MDELAY(50);

	/* Setup autoneg and flow control advertisement and perform 	*/
	/* 	autonegotiation. 					*/

	// manual p.165; PHY registers p.245
	_82545EM_read_phy_reg(ethptr, E1000_PHY_AUTONEG_ADV, &autoneg_adv);
	_82545EM_read_phy_reg(ethptr, E1000_PHY_1000T_CTRL, &phy_1000t_ctrl);

	autoneg_adv |= (E1000_NWAY_AR_10T_HD_CAPS  |
					E1000_NWAY_AR_10T_FD_CAPS  |
					E1000_NWAY_AR_100TX_HD_CAPS|
					E1000_NWAY_AR_100TX_FD_CAPS);
	
	autoneg_adv &= ~(E1000_NWAY_AR_PAUSE | E1000_NWAY_AR_ASM_DIR);

	phy_1000t_ctrl &= ~E1000_CR_1000T_HD_CAPS;
	phy_1000t_ctrl |= E1000_CR_1000T_FD_CAPS;

	_82545EM_write_phy_reg(ethptr, E1000_PHY_AUTONEG_ADV, autoneg_adv);
	_82545EM_write_phy_reg(ethptr, E1000_PHY_1000T_CTRL, phy_1000t_ctrl);

	/* Restart auto-negotiation. */

	// manual p.247
	_82545EM_read_phy_reg(ethptr, E1000_PHY_CONTROL, &phy_ctrl);
	phy_ctrl |= E1000_MII_CR_AUTO_NEG_EN|E1000_MII_CR_RESTART_AUTO_NEG;
	_82545EM_write_phy_reg(ethptr, E1000_PHY_CONTROL, phy_ctrl);

	/* Wait for auto-negotiation to complete 
       Implement a loop here to check the E1000_MII_SR_LINK_STATUS and E1000_MII_SR_AUTONEG_COMPLETE, break if they are both ture
       You should also delay for a while in each loop so it won't take too much CPU time */
    
    while (1){
    	_82545EM_read_phy_reg(ethptr, E1000_PHY_STATUS, &phy_status);
    	
    	if ((phy_status & E1000_MII_SR_LINK_STATUS) && 
			(phy_status & E1000_MII_SR_AUTONEG_COMPLETE))
			break;

		MDELAY(200);
    }

#ifdef DEBUG
    kprintf("PHY status: 0x%x\n", phy_status);
#endif

    /* Update device control according receive flow control and transmit flow control*/
	ctrl = e1000_io_readl(ethptr->iobase, E1000_CTRL);
	ctrl &= (~(E1000_CTRL_TFCE | E1000_CTRL_RFCE));
	e1000_io_writel(ethptr->iobase, E1000_CTRL, ctrl);

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
	uint32 rctl, recv_sum;

	/* Disable receiver while configuring. */

	//manual p.300
	rctl = e1000_io_readl(ethptr->iobase, E1000_RCTL);
	rctl &= ~E1000_RCTL_EN;
	e1000_io_writel(ethptr->iobase, E1000_RCTL, rctl);

#ifdef DEBUG
	kprintf("Receive Control: 0x%x\n", rctl);
#endif

	/* Enable receiver, accept broadcast packets, no loopback, and 	*/
	/* 	free buffer threshold is set to 1/2 RDLEN. 		*/
	
	rctl |= E1000_RCTL_EN|E1000_RCTL_BAM|E1000_RCTL_LBM_NO|E1000_RCTL_RDMTS_HALF;

	/* Do not store bad packets, do not pass MAC control frame, 	*/
	/* 	disable long packet receive and CRC strip 		*/
	
	rctl &= ~(E1000_RCTL_SBP|E1000_RCTL_LPE|E1000_RCTL_SECRC|E1000_RCTL_PMCF);
	
	/* Setup buffer sizes */
	rctl &= ~(E1000_RCTL_BSEX|E1000_RCTL_SZ_4096|E1000_RCTL_FLXBUF_MASK);
	rctl |= E1000_RCTL_SZ_2048;

	/* Set the Receive Delay Timer Register, let driver be notified */
	/* 	immediately each time a new packet has been stored in 	*/
	/* 	memory 							*/
	
	e1000_io_writel(ethptr->iobase, E1000_RDTR, E1000_RDTR_DEFAULT);
	e1000_io_writel(ethptr->iobase, E1000_RADV, E1000_RADV_DEFAULT);

	/* Set up interrupt rate to be default. Notice that it is a the rate is not just E1000_ITR_DEFAULT which is the frequency, 
       it is 1000000000 / (E1000_ITR_DEFAULT * 256) */

	e1000_io_writel(ethptr->iobase, E1000_ITR, 1000000000/(E1000_ITR_DEFAULT*256));


	/* Setup the HW Rx Head and Tail Descriptor Pointers, the Base 	*/
	/* 	and Length of the Rx Descriptor Ring 			*/
	e1000_io_writel(ethptr->iobase, E1000_RDBAL(0), (uint32)ethptr->rxRing);
	e1000_io_writel(ethptr->iobase, E1000_RDBAH(0), 0);
	e1000_io_writel(ethptr->iobase, E1000_RDLEN(0), E1000_RDSIZE*ethptr->rxRingSize);
	e1000_io_writel(ethptr->iobase, E1000_RDH(0), 0);
	e1000_io_writel(ethptr->iobase, E1000_RDT(0), ethptr->rxRingSize-E1000_RING_BOUNDARY);


	/* Disable Receive Checksum Offload for IPv4, TCP and UDP. */
	recv_sum = e1000_io_readl(ethptr->iobase, E1000_RXCSUM);
	recv_sum &= ~E1000_RXCSUM_TUOFL;
	e1000_io_writel(ethptr->iobase, E1000_RXCSUM, recv_sum);

	/* Enable receiver. */
	e1000_io_writel(ethptr->iobase, E1000_RCTL, rctl);
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
