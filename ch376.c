#include <stdio.h>
#include <ch376.h>

int main()
{
	unsigned  char value;
	value=ch376_check_exist(0x55);
	printf("Detecting ch376 ...");
	if (value==0xaa)
		printf("OK\n");
	else
	{
		printf("NOK\n");
		return 1;
	}
	
	printf("Ch376 version : %d\n",ch376_ic_get_version()&(32+16+8+4+2+1));
	printf("Setting USBKEY Mode ...");
	ch376_set_usb_mode(CH376_ARG_SET_USB_MODE_USB_HOST);
	value=ch376_disk_mount();
	if (value==CH376_INT_SUCCESS)
		printf("USBKEY Mounted\n");
	else
		printf("Impossible to mount USBKEY");
	
	
	return 0;
}