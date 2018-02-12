#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define DEVICE_GPIODRV "/dev/matrixled" 
#define DEVICE_GPIODRV_SEG "/dev/seg"  //¹ØÁªÊýÂë¹Ü
#define DEVICE_GPIODRV_PWM "/dev/pwm"  //¹ØÁª·äÃùÆ÷

long int melody[21]={3424,3401,3030,2865,2551,2272,2024,
                    1912,1703,1517,1432,1275,1136,1012,
                    956,851,758,715,637,568,508,0};   //µÍ£¬ÖÐ£¬žßÒô
long int love[29]={19,18,16,15,16,15,14,13,14,13,12,11,12,8,9,11,12,21,12,16,0,15,16,17,18,21,21,21,21};  //ÒôÀÖÐýÂÉ
long int wangling[24]={21,12,13,21,12,13,14,21,13,12,13,21,9,14,13,12,21,12,13,12,17,21,16,15};//ÍöÁéÐòÇú
long int butterfly[34]={9,11,11,11,11,9,9,12,12,11,9,9,9,11,11,11,11,9,9,12,12,13,21,21,9,8,9,8,7,21,21,7,7,9};//ÊýÂë±Š±Žbutt

long int butterfly1[34]={200,200,200,200,200,200,200,200,200,1000,200,200,200,200,200,200,200,200,200,200,200,400,200,100,200,200,200,200,200,400,200,200,200,200};

long int wangling1[24]={200,100,100,200,100,100,400,200,100,100,400,100,100,100,100,400,100,100,100,100,400,200,100,100};

int fd_pwm;
int buzzer(int arg) //·äÃùÆ÷×ŽÌ¬º¯Êý
{

    int k,n;
	fd_pwm=open("/dev/pwm",O_RDWR);
	if(fd_pwm<0)
	{
		printf("Can't open\n");
		return -1;
	}
	else
	{
		printf("open OK 11%x\n", fd_pwm);
	}

        if(arg==0)
          {
          for(n=0;n<100;n++)
           {
           ioctl(fd_pwm,0);
           usleep(1000);
           ioctl(fd_pwm,1);
           usleep(1000);
           }
           //sleep(1);
   	   close(fd_pwm);
          }
      if(arg==1)
         {
      	   
             for(k=0;k<29;k++)
              {
              for(n=0;n<100;n++)
                {
                 long int m=love[k];
                 ioctl(fd_pwm,0);
                 usleep(melody[m]/2);
                 ioctl(fd_pwm,1);
                 usleep(melody[m]/2);
                }
               sleep(0.75);
              }	
   	     close(fd_pwm);
         }
      //return 0;
        if(arg==2)
         {
      	   
             for(k=0;k<48;k++)
              {
              for(n=0;n<wangling1[k];n++)
                {
                 long int m=wangling[k];
                 ioctl(fd_pwm,0);
                 usleep(melody[m]/2);
                 ioctl(fd_pwm,1);
                 usleep(melody[m]/2);
                }
               sleep(0.75);
              }	
   	     close(fd_pwm);
         }
     // return 0;

//}
 if(arg==3)
         {
      	   
             for(k=0;k<30;k++)
              {
              for(n=0;n<butterfly1[k];n++)
                {
                 long int m=butterfly[k];
                 ioctl(fd_pwm,0);
                 usleep(melody[m]/2);
                 ioctl(fd_pwm,1);
                 usleep(melody[m]/2);
                }
               sleep(0.75);
              }	
   	     close(fd_pwm);
         }
      return 0;

}

//}  


int main()
{
	int fd_matrixled,fd_seg;
        //int fd;
	unsigned int id;
	int status;
	char *data;
	if((fd_matrixled=open(DEVICE_GPIODRV,O_RDWR))<0)
	 {
	  printf("open device: %s\n",DEVICE_GPIODRV);
	  perror("can not open device");
	  exit(1);
	 }

       if((fd_seg=open(DEVICE_GPIODRV_SEG,O_RDWR))<0)
	 {
	  printf("open device: %s\n",DEVICE_GPIODRV_SEG);
	  perror("can not open device");
	  exit(1);
	}  

       if((fd_pwm=open(DEVICE_GPIODRV_PWM,O_RDWR))<0)
	 {
	  printf("open device: %s\n",DEVICE_GPIODRV_PWM);
	  perror("can not open device");
	  exit(1);
	}  
        

        //printf("2;5;50");
        //printf("Content-type: text/html;charset=gb2312");
        //printf("<script>window.location.href='/index.html';</script>");
        //printf("charset=gb2312\n\n");
        //printf("2;5;50");
        //printf("Content-type: text/html\n\n");
	//printf("<html>\n");
        //printf("2;5;50");
        
	//printf("<head><title>CGI LED DEMO</title></head>\n");
	//printf("<body>\n");
	//printf("<center>\n");
	//printf("<hr size=5 color=blue width=20%/>\n");
	//printf("<h1>CGI LED DEMO 11111111111111</h1>\n");
	//printf("<h1><a href=/cgi_led.html>go back</a></h1>\n");
	//printf("<hr size=5 color=blue width=20%/>\n");
	//printf("<center>\n");
	//printf("</body>\n");
	
	data=getenv("QUERY_STRING");
	
	sscanf(data,"status=%ld",&status);
	
        int i=0;
	char local[3]={'\0'};
	char temp[3]={'\0'};
	int fish;
        int situation;
        int labol=0;
        //int step;
       
 
	fd_matrixled=open("/dev/matrixled",O_RDWR);
	FILE *fd2;
	fd2 = fopen("//mnt//local.dat", "r+");
        if(flock(fileno(fd2), LOCK_EX)==0)
	{
	
		fscanf(fd2, "%s", local);
		strcpy(temp,local);
	
		buzzer(0);
		for(i=12;i>0;i--)
		{
                
			strcpy(local,temp);
			fish=(local[0]-'0')*10+(local[1]-'0');
                       //printf("%d\n",fish);
			situation=ioctl(fd_matrixled, status,fish);
                      // printf("%d\n",situation);
                        fish=situation/10;
                        //step=(situation%100)/10;
                        labol=situation%10;

		}    
              
                if(labol==1){
                
                 buzzer(1);
                for(i=35;i>0;i--)
                 ioctl(fd_seg,0,1);
                   for(i=4;i>0;i--)
                 {
                     ioctl(fd_matrixled, 16,0);
                  }
                 ioctl(fd_seg,0,0);
                  
                 printf("Content-type: text/html;charset=utf-8\n\n");
                 printf("2;0;20");
                 }
                if(labol==3){
                 
                 ioctl(fd_seg,0,1);
                 
                 printf("Content-type: text/html;charset=utf-8\n\n");
                 printf("2;10;20");
                 }
                if(labol==4){
                 //labol=0;
                  buzzer(2);
                for(i=35;i>0;i--)
                 ioctl(fd_seg,0,2);
                 for(i=4;i>0;i--)
                 {
                     ioctl(fd_matrixled, 16,0);
                  }
                //for(i=40;i>0;i--)
                 ioctl(fd_seg,0,0);
                 printf("Content-type: text/html;charset=utf-8\n\n");
                 printf("3;0;30");
                 }
                if(labol==6){
                 //labol=0;
                  //buzzer(0);
                
                //for(i=40;i>0;i--)
                 ioctl(fd_seg,0,1);
                 
                 printf("Content-type: text/html;charset=utf-8\n\n");
                 printf("3;10;30");
                 }
                if(labol==7){
                 //labol=0;
                  //buzzer(0);
                
                //for(i=40;i>0;i--)
                 ioctl(fd_seg,0,2);
               
                 printf("Content-type: text/html;charset=utf-8\n\n");
                 printf("3;20;30");
                 }
               if(labol==8){
                // labol=0;
                 buzzer(3);
                
                //for(i=40;i>0;i--)
                 ioctl(fd_seg,0,3);
                 for(i=4;i>0;i--)
                 {
                     ioctl(fd_matrixled, 16,0);
                  }
                 ioctl(fd_seg,0,0);
                 printf("Content-type: text/html;charset=utf-8\n\n");
                 printf("3;30;30");
                 }


		fclose(fd2);
		fd2 = fopen("//mnt//local.dat", "w+");
		//printf("%s ",local);
                if(status==0)
                 {fish=11;
                   for(i=40;i>0;i--)
                  ioctl(fd_seg,0,0);
                 }
                 local[0]=fish/10+'0';
		 local[1]=fish%10+'0';
                 //local[2]='0';
                 // printf("%s ",local);
		 fprintf(fd2, "%s", local);
		
		fclose(fd2);
	        flock(fileno(fd2), LOCK_UN);
                close(fd_seg);
		close(fd_matrixled);

             }
         //printf("<script>window.location.href='/index.html';</script>");
	//while(1)
	//{ 
               
	    
         //    ioctl(fd, status, id);
		
	//}
	//close(fd);
	//printf("</html>\n");
	exit(0);
}

