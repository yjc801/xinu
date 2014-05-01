/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	uint32 retval;

	kprintf("main: calling getlocalip\n");
    NetData.ipvalid = FALSE;
	retval = getlocalip();

	if (retval == SYSERR) {
		kprintf("I'm here to stop!\n");
	} else {
		kprintf("I'm here to continue!\n");
		kprintf("\n\n###########################################################\n\n");
		kprintf("IP address is %d.%d.%d.%d   %08x\n\r",
			(retval>>24)&0xff, (retval>>16)&0xff, (retval>>8)&0xff,
		 	retval&0xff,retval);

	    	kprintf("Subnet mask is %d.%d.%d.%d and router is %d.%d.%d.%d\n\r",
			(NetData.addrmask>>24)&0xff, (NetData.addrmask>>16)&0xff,
			(NetData.addrmask>> 8)&0xff,  NetData.addrmask&0xff,
			(NetData.routeraddr>>24)&0xff, (NetData.routeraddr>>16)&0xff,
			(NetData.routeraddr>> 8)&0xff, NetData.routeraddr&0xff);
	}
	
	netin();

	//while (1);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */
	recvclr();
	while (TRUE) {
		retval = receive();
		kprintf("\n\n\rMain process recreating shell\n\n\r");
		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
	}

	return OK;
}
