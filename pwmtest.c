#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static int fd = -1;
long int melody[21]={3424,3401,3030,2865,2551,2272,2024,
                    1912,1703,1517,1432,1275,1136,1012,
                    956,851,758,715,637,568,508,0};
long int love[29]={19,18,16,15,16,15,14,13,14,13,12,11,12,8,9,11,12,21,12,16,0,15,16,17,18,21,21,21,21};

int buzzer(int arg)
{

        int i,j;
	fd=open("/dev/pwm",O_RDWR);
	if(fd<0)
	{
		printf("Can't open\n");
		return -1;
	}
	else
	{
		printf("open OK 11%x\n", fd);
	}

        if(arg==0)
          {
          for(j=0;j<100;j++)
           {
           ioctl(fd,0);
           usleep(1000);
           ioctl(fd,1);
           usleep(1000);
           }
           //sleep(1);
   	   close(fd);
          }
      if(arg==1)
         {
      	   //while(1)
	    //{
             for(i=0;i<29;i++)
              {
              for(j=0;j<100;j++)
                {
                 long int m=love[i];
                 ioctl(fd,0);
                 usleep(melody[m]/2);
                 ioctl(fd,1);
                 usleep(melody[m]/2);
                }
               sleep(0.75);
              }	
	    //}
   	     close(fd);
         }
      return 0;

}

int main()
{
	/*int i,j;
	fd=open("/dev/pwm",O_RDWR);
	if(fd<0)
	{
		printf("Can't open\n");
		return -1;
	}
	else
	{
		printf("open OK 11%x\n", fd);
	}

	while(1)
	{
           for(i=0;i<7;i++)
            {
              for(j=0;j<100;j++)
                {
                 ioctl(fd,0);
                 usleep(melody[i]/2);
                 ioctl(fd,1);
                 usleep(melody[i]/2);
                }
               sleep(1);
             }	
	}
   	close(fd);*/
        int n=1;
        buzzer(n);
}


