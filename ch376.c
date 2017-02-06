#include <stdio.h>
#include "../oric-common/include/ch376.h"
#include <string.h>

void version()
{
	printf("ch376 0.0.1\n");
}


void write_file()
{
	char *str="Hello world!";
	char *filename="/jer4";
	unsigned char ret;
	printf("Trying to write %s\n",filename);
	ch376_set_file_name(filename);
	ret=ch376_file_create();
	printf("ch376 file create return : %x\n",ret);
	ch376_set_file_name(filename);
	ret=ch376_file_open();
	printf("ret de ch376 file open %x\n",ret);
	ret=ch376_fwrite(str,4);
	printf("ret de ch376 fwrite %x\n",ret);
	
}

int main(int argc,char *argv[])
{
	unsigned  char value;
	
	if (argc==2 && strcmp(argv[1],"--version")==0)
	{
		version();
		return 1;
	}
		
	value=ch376_check_exist(0x55);
	printf("This tool is for ch376 chip test ...\n");
	printf("Detecting ch376 ...");
	if (value==0xaa)
		printf("OK\n");
	else
	{
		printf("NOK\n");
		return 1;
	}
	
	printf("Ch376 version : %d\n",ch376_ic_get_version()&(32+16+8+4+2+1));
	printf("Setting USBKEY Mode ...\n");
	ch376_set_usb_mode(CH376_ARG_SET_USB_MODE_USB_HOST);
	value=ch376_disk_mount();
	if (value==CH376_INT_SUCCESS)
		printf("USBKEY Mounted\n");
	else
	{	
		printf("Impossible to mount USBKEY\n");
		return 1;
	}
	write_file();
	return 0;
}