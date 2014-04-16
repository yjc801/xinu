#include <xinu.h>

struct	ether	ethertab[Neth];		/* Ethernet control blocks 	*/

/*------------------------------------------------------------------------
 * * ethInit - Initialize Ethernet device structures
 * *------------------------------------------------------------------------
 * */
devcall	ethInit (
	struct dentry *devptr
	)
{
	struct	ether 	*ethptr;
	int32	dinfo;			/* device information*/

	ethptr = &ethertab[devptr->dvminor];

/* Initialize structure pointers */
	memset(ethptr, '\0', sizeof(struct ether));
	ethptr->dev = devptr;
	ethptr->csr = devptr->dvcsr;

/*If find the device on PCI bus, intialize the devtab of ETHER0 with the funtion pointers of e1000
 * If not found, return SYSERR*/

	int32 index = devptr->dvminor;

	if((dinfo = find_pci_device(INTEL_82545EM_DEVICE_ID,INTEL_VENDOR_ID,index)) == SYSERR){
		return dinfo;
	}

	ethptr->pcidev = dinfo;

	pci_bios_read_config_dword(ethptr->pcidev,E1000_PCI_MEMBASE,&ethptr->membase);
	pci_bios_read_config_dword(ethptr->pcidev,E1000_PCI_FLASHBASE,&ethptr->flashbase);
	pci_bios_read_config_dword(ethptr->pcidev,E1000_PCI_IOBASE,&ethptr->iobase);
	ethptr->iobase &= ~1;	
	pci_bios_read_config_dword(ethptr->pcidev,4,&ethptr->flashbase);
	kprintf("io:0x%x, mem:0x%x, flash:0x%x\n", ethptr->iobase,ethptr->membase,ethptr->flashbase);
//	kprintf("%.2x\n",e1000_io_readl(ethptr->iobase,0) & 0xFF);
//	kprintf("%.2x\n",e1000_io_readl(ethptr->iobase,1) & 0xFF);
//	kprintf("%.2x\n",e1000_io_readl(ethptr->iobase,2) & 0xFF);
	//kprintf("io:0x%x, mem:0x%x, flash:0x%x\n", ethptr->iobase,ethptr->membase,ethptr->flashbase);
	//outw(ethptr->iobase + 0xe, 0x800 + 2);
	//*((unsigned short*) &ethptr->devAddress[0]) = inw(ethptr->iobase + 0x00);
	//*((unsigned short*) &ethptr->devAddress[2]) = inw(ethptr->iobase + 0x02);
	//*((unsigned short*) &ethptr->devAddress[4]) = inw(ethptr->iobase + 0x04);
	//int32 status;
	//uint32 addr;
	//addr = 1|(0x0E<<8);
	//kprintf("%x\n",e1000_io_readl(ethptr->iobase,0x14));
	//kprintf("0x%x\n",addr);
	//e1000_io_writel(ethptr->iobase,0x14,addr);
	//kprintf("0x%x\n",mmio_read32(0x14));
	//e1000_io_writel(ethptr->iobase,0x14,addr);
	//while((e1000_io_readl(ethptr->iobase,0x14)&(1<<4)))
	//kprintf("%x\n",e1000_io_readl(ethptr->iobase,0x14));
//	e1000_io_writel(ethptr->iobase,0x04);
	//kprintf("%x\n",e1000_io_readl(ethptr->iobase,0x0E));

/* Set the state of ethptr to be UP */

	return OK;
}


