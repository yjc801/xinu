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
	
	ethptr->state = ETH_STATE_DOWN;
	ethptr->pcidev = dinfo;

	_82545EMInit(ethptr);

/* Set the state of ethptr to be UP */
	ethptr->state = ETH_STATE_UP;

	return OK;
}


