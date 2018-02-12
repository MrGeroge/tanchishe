#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static int fd = -1;

unsigned char seg7table[16] = {
    /* 0       1       2       3       4       5       6      7*/
    0xc0,   0xf9,   0xa4,   0xb0,   0x99,   0x92,   0x82,   0xf8,
                                                                                                               
    /* 8       9      A        B       C       D       E      F*/
    0x80,   0x90,   0x88,   0x83,   0xc6,   0xa1,   0x86,   0x8e,
};

int main()
{
	int i=0;
	fd=open("/dev/seg",O_RDWR);
	if(fd<0)
	{
		printf("Can't open\n");
		return -1;
	}
	else
	{
		printf("open OK %x\n", fd);
	}

	//ioctl(fd, 0, 0xf);
	while(1){
        ioctl(fd, 0, 10120);  
	}
   	close(fd);
  	return 0;
}


