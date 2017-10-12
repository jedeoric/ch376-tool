#include <stdio.h>
#include "../../telemon/src/include/c/ch376.h"
#include <string.h>

#include "version.h"

unsigned char version_opt=0;
unsigned char help_opt=0;

unsigned char getopts(char *arg)
{
  // 2: arg is not an option
  if (arg[0]!='-') return 2;
  if (strcmp(arg,"--version")==0 || strcmp(arg,"-v")==0) 
  {
    version_opt=1;
    return 0;
  }
  
  if (strcmp(arg,"--help")==0 || strcmp(arg,"-h")==0) 
  {
    help_opt=1;
    return 0;
  }  

  return 1;
}

void version()
{
	printf("ch376 %s\n",VERSION);
}

void usage()
{
  printf("usage:\n");
  printf(" ch376 sub-command\n");
  printf("sub-command :\n");
  printf(" detect : detect ch376\n");
  printf(" version : display ch376 version\n");
  printf(" mountsd : mount sdcard\n");
  printf(" mountusb : mount usbkey\n");
  printf(" mkdir : Create a /ch376d folder\n");
  printf(" write : write data in a file\n");
  printf(" rm : Delete a /ch376d folder\n");
//  printf(" menu : display menu\n");
  printf(" all : do all test\n");
  printf("\n* Orix version : Jede (jede@oric.org)\n");
  return;
}

void create_directory()
{
  unsigned char ret;
  char *filename="/ch376d";
  printf("Trying to create %s\n",filename);
  ch376_set_file_name(filename);
  ret=ch376_dir_create();
  if (ret==CH376_INT_SUCCESS)
    printf("OK return code is equal to %d\n",CH376_INT_SUCCESS);
  else
    printf("NOK error code %d received instead of %d\n",ret,CH376_INT_SUCCESS);
}

void fseek_test()
{  
  unsigned int ret;
  char *filename="toto.wav";
  
  ch376_set_file_name("/");
  ch376_file_open();
  ch376_set_file_name(filename);
  ch376_file_open();
  ret=ch376_seek_file(10000);
  printf("Seek : First bytes ptr : %d\n",ret);
}


void delete_directory()
{
  unsigned char ret;
  char *filename="/toto";
  ch376_set_file_name(filename);
  ret=ch376_dir_create();
  
  printf("Suppression de %s\n",filename);
  ch376_set_file_name(filename);
  ret=ch376_file_open(); // Marche aussi avec cette ligne commentée.
  ret=ch376_file_erase();
}


void write_file()
{
	char *str="Hello world!";
	char *filename="/writeme";
	unsigned char ret;
	printf("Trying to createfile %s\n",filename);
	ch376_set_file_name(filename);
	ret=ch376_file_create();
  if (ret==CH376_INT_SUCCESS)
     printf("OK return code is equal to %x\n",CH376_INT_SUCCESS);
  else
    printf("NOK error code %d received instead of %d\n",ret,CH376_INT_SUCCESS);
	
  printf("Trying to write '%s' string to %s\n",str,filename);
	ch376_set_file_name(filename);
	ret=ch376_file_open();
	if (ret==CH376_INT_SUCCESS)
     printf("OK return code is equal to %x\n",CH376_INT_SUCCESS);
  else
    printf("NOK error code %d received instead of %d\n",ret,CH376_INT_SUCCESS);
  
  ch376_set_bytes_write(strlen(str));
	ret=ch376_write(str);
	printf("ret de ch376 fwrite %x\n",ret);
  printf("Closing file with length update ...\n");
  ret=ch376_file_close(1);
  printf("Close return %x\n",ret);
	
}

unsigned char detect()
{
  unsigned  char value;
	value=ch376_check_exist(0x55);
	
	printf("Detecting ch376 ... (sending 0x55)\n");
	if (value==0xaa)
		printf("OK : received 0xaa\n");
	else
	{
		printf("NOK : 0xaa not received\n");
		return 1;
	}
	  
}

void mount_sdcard()
{
  unsigned  char value;
 	printf("Setting SDCARD Mode ...\n");
	ch376_set_usb_mode(CH376_ARG_SET_USB_MODE_SD_HOST);
	value=ch376_disk_mount();
  
	if (value==CH376_INT_SUCCESS)
		printf("SDCARD Mounted\n");
	else
	{	
		printf("Impossible to mount SDCARD, received code %d instead of %d\n",value,CH376_INT_SUCCESS);
	}
  
}

unsigned char mount_usbkey()
{
  unsigned  char value;
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
}


void display_version()
{
	printf("Ch376 version : %d\n",ch376_ic_get_version()&(32+16+8+4+2+1));
}

int main(int argc,char *argv[])
{
	unsigned  char value;

  unsigned char i,ret,found_a_folder_in_arg_found=0;

  if (argc==2 || argc==3)
  {
    for (i=1;i<argc;i++)
    {
      ret=getopts(argv[i]);
      if (ret==1) 
      {
        //this is a parameter but not recognized
        usage();
        return 1;
      }
      if (ret==2) 
      {
        //theses are to stop if we have 2 folders on commands line, in the future it will bepossible
        if (found_a_folder_in_arg_found==0) 
            found_a_folder_in_arg_found=1;
        else
          {
          // here we found 2 folders on the command line
          usage();
          return 1;
          }
      }
    }
  }
    else
    {
      usage();
      return 1;
    }

  if (version_opt==1)
  {
    version();
    return 0;
  }
  
  if (help_opt==1)
  {
    usage();
    return 0;
  } 

  printf("This tool is for ch376 chip test ...\n");
  
  if (strcmp(argv[1],"detect")==0)
  {
    detect();
    return 0;
  }
  
  if (strcmp(argv[1],"version")==0)
  {
    display_version();
    return 0;
  }  
  
  if (strcmp(argv[1],"mountsd")==0)
  {
    mount_sdcard();
    return 0;
  }    

  if (strcmp(argv[1],"mountusb")==0)
  {
    mount_usbkey();
    return 0;
  }      
  
  if (strcmp(argv[1],"mkdir")==0)
  {
    create_directory();
    return 0;
  }      


  if (strcmp(argv[1],"write")==0)
  {
    write_file();
    return 0;
  }        

  
  
  if (strcmp(argv[1],"all")==0)
  {
    detect();
    display_version();
    mount_sdcard();
    mount_usbkey();
    create_directory();
    return 0;
  }
  
  

  



  
  delete_directory();
  fseek_test();
  /*
	write_file();
  printf("Creating directory /tmp");
  create_directory();
  */
	return 0;
}