#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <asm/irq.h>
#include <mach/hardware.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>

#include <mach/map.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>

#include <plat/gpio-cfg.h>

#define DEVICE_NAME "matrixled"
static int labol=0;
static int labol2=0;
static int labol3=0;
static int xiarow=5;
static int xiacolumn=6;
static int xiarow2=6;
static int xiacolumn2=2;
static int xiarow3=7;
static int xiacolumn3=7;
static int xiarow4=2;
static int xiacolumn4=6;
static int xiarow5=8;
static int xiacolumn5=2;
static int xiarow6=4;
static int xiacolumn6=7;
//static int step1=0;
//static int step2=0;
//static int step3=0;

static void __iomem *io_base1, *io_base2;

void location(int fishrow,int fishcolumn)
{
  int tmp1,tmp2;
  int i;
    tmp1 = ~(0x01<<(fishrow-1));
    tmp2 = (0x01<<(fishcolumn-1));
    writeb(tmp1, io_base1);
    writeb(tmp2, io_base2);
    msleep(0.00005);
 
}

void location2(int fishrow,int fishcolumn)
{
  int tmp1,tmp2;
    tmp1 = ~(0x01<<(fishrow-1));
    tmp2 = (0x01<<(fishcolumn-1));
    writeb(tmp1, io_base1);
    writeb(tmp2, io_base2);
    msleep(0.025);
 
}

static int finish[15]={25,32,34,35,36,43,44,45,46,47,52,54,55,56,65};

static long mled_ioctl(struct file *filp, unsigned int cmd,unsigned int fish)
{
	int tmp1,tmp2,tmp3,tmp4;
        //int xia=56;
	//int xiarow=xia/10;
	//int xiacolumn=xia%10;
	//int fishrow=fish/100;
        //int fishcolumn=(fish%100)/10;
         int fishrow=fish/10;
        int fishcolumn=fish%10;
        //int step=fish%100;
        int i=0;
	//tmp1 = ~(0x01<<xiarow+0x01<<fishrow);
	//tmp2 = (0x01<<xiacolumn+0x01<<fishcolumn);
	//writeb(tmp1, io_base1);
        //writeb(tmp2, io_base2);
	switch(cmd) {
	case 0:
		{
                 labol=0;
                 labol2=0;
                 labol3=0;
                 fish=fishrow*100+fishcolumn*10;
		 break;
		}
	case 1:
		{
		  //step++;
                  if(fishrow>1)fishrow--;
		  else fishrow=8;
		  fish=fishrow*100+fishcolumn*10+labol;
		  if((fishrow!=xiarow || fishcolumn!=xiacolumn) && labol==0)
                {
                   for(i=0;i<10;i++)
                   {
                  //tmp3 = ~(0x01<<(fishrow-1));
	              //tmp4 = (0x01<<(fishcolumn-1));
		         //writeb(tmp3, io_base1);
		         //writeb(tmp4, io_base2);
                  //printk("u");
                  //msleep(0.025);
                  location2(fishrow,fishcolumn);
                   location2(xiarow,xiacolumn);
	          //tmp1 = ~(0x01<<(xiarow-1));
	         // tmp2 = (0x01<<(xiacolumn-1));
		 // writeb(tmp1, io_base1);
		  //writeb(tmp2, io_base2);
                  //printk("h");
                 // msleep(0.025);
                
                   }
                 }
                  else
                 {
                 	 location2(fishrow,fishcolumn);
                   //tmp3 = ~(0x01<<(fishrow-1));
	         // tmp4 = (0x01<<(fishcolumn-1));
		 // writeb(tmp3, io_base1);
		//  writeb(tmp4, io_base2);
                   labol=1;
                //  msleep(0.025);
                  
                  }
                  
		  break;
		}
	case 3:
		{
                   //step++;
		   if(fishrow<8)fishrow++;
		  else fishrow=1;
		   fish=fishrow*100+fishcolumn*10+labol;
	          if((fishrow!=xiarow || fishcolumn!=xiacolumn) && labol==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow-1));
	          tmp2 = (0x01<<(xiacolumn-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else
                 {
                   tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol=1;
                  msleep(0.025);
                  }
		  break;
		}
	case 4:
		{
                  //step++;
		  if(fishcolumn>1)
	      fishcolumn--;
		  else fishcolumn=8;
		   fish=fishrow*100+fishcolumn*10+labol;
	          if((fishrow!=xiarow || fishcolumn!=xiacolumn) && labol==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow-1));
	          tmp2 = (0x01<<(xiacolumn-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else
                 {
                   tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol=1;
                  msleep(0.025);
                  }
		  break;
		}
	case 5:
		{
                  //step++;
		  if(fishcolumn<8)
	      fishcolumn++;
		  else fishcolumn=1;
		  fish=fishrow*100+fishcolumn*10+labol;
	     if((fishrow!=xiarow || fishcolumn!=xiacolumn) && labol==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow-1));
	          tmp2 = (0x01<<(xiacolumn-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else
                 {
                   tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol=1;
                  msleep(0.025);
                  }
		  break;
		}
         case 6:
		{
                  //step++;
		  if(fishrow>1)fishrow--;
		  else fishrow=8;
		  fish=fishrow*100+fishcolumn*10+labol2+2;
	     if((fishrow!=xiarow2 || fishcolumn!=xiacolumn2) && labol2==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow2-1));
	          tmp2 = (0x01<<(xiacolumn2-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
               else if(labol2==0)labol2=1;
               if((fishrow!=xiarow3 || fishcolumn!=xiacolumn3)  && labol2==1)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow3-1));
	          tmp2 = (0x01<<(xiacolumn3-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else if(labol2==1)
                 {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol2=2;
                  msleep(0.025);
                  }
		  break;
		}
case 8:
		{
                   //step++;
		  if(fishrow<8)fishrow++;
		  else fishrow=1;
		 fish=fishrow*100+fishcolumn*10+labol2+2;
	     if((fishrow!=xiarow2 || fishcolumn!=xiacolumn2) && labol2==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow2-1));
	          tmp2 = (0x01<<(xiacolumn2-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
               else if(labol2==0)labol2=1;
               if((fishrow!=xiarow3 || fishcolumn!=xiacolumn3)  && labol2==1)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow3-1));
	          tmp2 = (0x01<<(xiacolumn3-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else if(labol2==1)
                 {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol2=2;
                  msleep(0.025);
                  }
		  break;
		}
case 9:
		{
                  // step++;
		   if(fishcolumn>1)
	      fishcolumn--;
		  else fishcolumn=8;
		 fish=fishrow*100+fishcolumn*10+labol2+2;
	    if((fishrow!=xiarow2 || fishcolumn!=xiacolumn2) && labol2==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow2-1));
	          tmp2 = (0x01<<(xiacolumn2-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
               else if(labol2==0)labol2=1;
               if((fishrow!=xiarow3 || fishcolumn!=xiacolumn3)  && labol2==1)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow3-1));
	          tmp2 = (0x01<<(xiacolumn3-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else if(labol2==1)
                 {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol2=2;
                  msleep(0.025);
                  }
		  break;
		}
case 10:
		{
                 //step++;
		 if(fishcolumn<8)
	      fishcolumn++;
		  else fishcolumn=1;
		 fish=fishrow*100+fishcolumn*10+labol2+2;
	    if((fishrow!=xiarow2 || fishcolumn!=xiacolumn2) && labol2==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow2-1));
	          tmp2 = (0x01<<(xiacolumn2-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
               else if(labol2==0)labol2=1;
               if((fishrow!=xiarow3 || fishcolumn!=xiacolumn3)  && labol2==1)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow3-1));
	          tmp2 = (0x01<<(xiacolumn3-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else if(labol2==1)
                 {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol2=2;
                  msleep(0.025);
                  }
		  break;
		}
case 11:
		{
                  //step++;
		  if(fishrow>1)fishrow--;
		  else fishrow=8;
		  fish=fishrow*100+fishcolumn*10+labol3+5;
	     if((fishrow!=xiarow4|| fishcolumn!=xiacolumn4) && labol3==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow4-1));
	          tmp2 = (0x01<<(xiacolumn4-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
               else if(labol3==0)labol3=1;
               if((fishrow!=xiarow5 || fishcolumn!=xiacolumn5)  && labol3==1)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow5-1));
	          tmp2 = (0x01<<(xiacolumn5-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else if(labol3==1)labol3=2;
                 if((fishrow!=xiarow6|| fishcolumn!=xiacolumn6) && labol3==2)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow6-1));
	          tmp2 = (0x01<<(xiacolumn6-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                   }
                 }
                else if(labol3==2)
                 {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol3=3;
                  msleep(0.025);
                  }
		  break;
		}
   case 13:
		{
                  //step++;
		  if(fishrow<8)fishrow++;
		  else fishrow=1;
		 fish=fishrow*100+fishcolumn*10+labol3+5;
	     if((fishrow!=xiarow4|| fishcolumn!=xiacolumn4) && labol3==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow4-1));
	          tmp2 = (0x01<<(xiacolumn4-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
               else if(labol3==0)labol3=1;
               if((fishrow!=xiarow5 || fishcolumn!=xiacolumn5)  && labol3==1)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow5-1));
	          tmp2 = (0x01<<(xiacolumn5-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else if(labol3==1)labol3=2;
                 if((fishrow!=xiarow6|| fishcolumn!=xiacolumn6) && labol3==2)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow6-1));
	          tmp2 = (0x01<<(xiacolumn6-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                   }
                 }
                else if(labol3==2)
                 {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol3=3;
                  msleep(0.025);
                  }
		  break;
		}
case 14:
		{
                   //step++;
		  if(fishcolumn>1)
	           fishcolumn--;
		  else fishcolumn=8;
		  fish=fishrow*100+fishcolumn*10+labol3+5;
	     if((fishrow!=xiarow4|| fishcolumn!=xiacolumn4) && labol3==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow4-1));
	          tmp2 = (0x01<<(xiacolumn4-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
               else if(labol3==0)labol3=1;
               if((fishrow!=xiarow5 || fishcolumn!=xiacolumn5)  && labol3==1)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow5-1));
	          tmp2 = (0x01<<(xiacolumn5-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else if(labol3==1)labol3=2;
                 if((fishrow!=xiarow6|| fishcolumn!=xiacolumn6) && labol3==2)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow6-1));
	          tmp2 = (0x01<<(xiacolumn6-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                   }
                 }
                else if(labol3==2)
                 {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol3=3;
                  msleep(0.025);
                  }
		  break;
		}
case 15:
		{
                  // step++;
		  if(fishcolumn<8)
	      fishcolumn++;
		  else fishcolumn=1;
		fish=fishrow*100+fishcolumn*10+labol3+5;
	     if((fishrow!=xiarow4|| fishcolumn!=xiacolumn4) && labol3==0)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow4-1));
	          tmp2 = (0x01<<(xiacolumn4-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
               else if(labol3==0)labol3=1;
               if((fishrow!=xiarow5 || fishcolumn!=xiacolumn5)  && labol3==1)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow5-1));
	          tmp2 = (0x01<<(xiacolumn5-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                
                   }
                 }
                 else if(labol3==1)labol3=2;
                 if((fishrow!=xiarow6|| fishcolumn!=xiacolumn6) && labol3==2)
                {
                   for(i=0;i<10;i++)
                   {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                  //printk("u");
                  msleep(0.025);

	          tmp1 = ~(0x01<<(xiarow6-1));
	          tmp2 = (0x01<<(xiacolumn6-1));
		  writeb(tmp1, io_base1);
		  writeb(tmp2, io_base2);
                  //printk("h");
                  msleep(0.025);
                   }
                 }
                else if(labol3==2)
                 {
                  tmp3 = ~(0x01<<(fishrow-1));
	          tmp4 = (0x01<<(fishcolumn-1));
		  writeb(tmp3, io_base1);
		  writeb(tmp4, io_base2);
                   labol3=3;
                  msleep(0.025);
                  }
		  break;
		}
     case 16:{
              for(i=0;i<10;i++)
              {
               int j;
               for(j=0;j<16;j++)
               location(finish[j]/10,finish[j]%10);
              } 
              break;
              }
	default:
                 return fish;
		//return -EINVAL;
	}
           return fish;
}

static struct file_operations dev_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= mled_ioctl,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};

static int __init dev_init(void)
{
	int ret;
        
	ret = misc_register(&misc);

	io_base1 = ioremap(0x88003000, 1);
	if (io_base1 == 0)
	{
		printk("failed to ioremap() region\n");
	}
	else
	{
		printk("io_base = %p\n",io_base1);
		writeb(0x00, io_base1);
	}
	io_base2 = ioremap(0x88005000, 1);
	if (io_base2 == 0)
	{
		printk("failed to ioremap() region\n");
	}
	else
	{
		printk("io_base = %p\n",io_base2);
		writeb(0xFF, io_base2);
	}

	printk ("[***" DEVICE_NAME "***]:initialized\n");

	return ret;
}

static void __exit dev_exit(void)
{
	misc_deregister(&misc);
	iounmap(io_base1);
	iounmap(io_base2);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cvtech Inc.");
