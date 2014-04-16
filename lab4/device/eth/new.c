nclude <xinu.h>

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

pci_bios_read_config_dword(devptr,E1000_PCI_MEMBASE,ethptr->membase);
pci_bios_read_config_dword(devptr,E1000_PCI_FLASHBASE,ethptr->flashbase);
pci_bios_read_config_dword(devptr,E1000_PCI_IOBASE,ethptr->iobase);

kprintf("io:0x%x, mem:0x%x, flash:0x%x\n", ethptr->iobase,ethptr->membase,ethptr->flashbase);

/*If find the device on PCI bus, intialize the devtab of ETHER0 with the funtion pointers of e1000
 * If not found, return SYSERR*/

int32 index = devptr->dvminor;

if((dinfo = find_pci_device(INTEL_82545EM_DEVICE_ID,INTEL_VENDOR_ID,index)) == SYSERR){
return dinfo;
}

ethptr->pcidev = dinfo;

/* Set the state of ethptr to be UP */

return OK;
}


