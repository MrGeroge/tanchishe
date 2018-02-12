#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h>
#include<sys/file.h>

static int fd = -1;

int main()
{
	int i=0;
	char local[3]={'\0'};
	char temp[3]={'\0'};
	int fish;
        int situation;
        int labol=0;
	fd=open("/dev/matrixled",O_RDWR);
	FILE *fd2;
	fd2 = fopen("//mnt//local.dat", "r+");
       // fprintf(fd2, "%s", local);
       //   printf("open OK 11%x\n", fd2);
	if(fd<0)
	{
		printf("Can't open\n");
		return -1;
	}
	else
	{
		printf("open OK 11%x\n", fd);
	}
        // printf("hu");
	if(flock(fileno(fd2), LOCK_EX)==0)
	{
	//while (!feof(fd2))
	//{
            // printf("hu1 ");
		fscanf(fd2, "%s", local);
               // printf("%s",local);
		strcpy(temp,local);
	//}
	//while(1)
	//{
		
		for(i=15;i>0;i--)
		{
		//ioctl(fd, 0, 1<<i);
			strcpy(local,temp);
			fish=(local[0]-'0')*10+(local[1]-'0');
                       printf("%d\n",fish);
			situation=ioctl(fd, 1,fish);
                        printf("%d\n",situation);
                        fish=situation/10;
                        labol=situation%10;
			//sleep(1);
                       // printf("%ld\n",fish);
		}
	//}       
                if(labol){labol=0;printf("2;3;30");}
		fclose(fd2);
		fd2 = fopen("//mnt//local.dat", "w+");
		//printf("%s ",local);
                 local[0]=fish/10+'0';
		 local[1]=fish%10+'0';
                 // printf("%s ",local);
		 fprintf(fd2, "%s", local);
		
		fclose(fd2);
	    flock(fileno(fd2), LOCK_UN);
		close(fd);
	}
  	return 0;
}


