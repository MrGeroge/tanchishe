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
         int fishrow=fish/10;
        int fishcolumn=fish%10;
        int i=0;
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
            if(fishrow>1)fishrow--;
		    else fishrow=8;
		    fish=fishrow*100+fishcolumn*10+labol;
		  if((fishrow!=xiarow || fishcolumn!=xiacolumn) && labol==0)
            {
                   for(i=0;i<10;i++)
                   {
               
                     location2(fishrow,fishcolumn);
                     location2(xiarow,xiacolumn);
                   }
            }
          else
                 {
                 	 location2(fishrow,fishcolumn);
                     labol=1;

                  }
                  
		  break;
		}
	case 3:
		{
		   if(fishrow<8)fishrow++;
		  else fishrow=1;
		   fish=fishrow*100+fishcolumn*10+labol;
	          if((fishrow!=xiarow || fishcolumn!=xiacolumn) && labol==0)
            {
                   for(i=0;i<10;i++)
                   {
               
                     location2(fishrow,fishcolumn);
                     location2(xiarow,xiacolumn);
                   }
            }
          else
                 {
                 	 location2(fishrow,fishcolumn);
                     labol=1;

                  }
		  break;
		}
	case 4:
		{
		  if(fishcolumn>1)
	      fishcolumn--;
		  else fishcolumn=8;
		   fish=fishrow*100+fishcolumn*10+labol;
	          if((fishrow!=xiarow || fishcolumn!=xiacolumn) && labol==0)
            {
                   for(i=0;i<10;i++)
                   {
               
                     location2(fishrow,fishcolumn);
                     location2(xiarow,xiacolumn);
                   }
            }
          else
                 {
                 	 location2(fishrow,fishcolumn);
                     labol=1;

                  }
		  break;
		}
	case 5:
		{
		  if(fishcolumn<8)
	      fishcolumn++;
		  else fishcolumn=1;
		  fish=fishrow*100+fishcolumn*10+labol;
	     if((fishrow!=xiarow || fishcolumn!=xiacolumn) && labol==0)
            {
                   for(i=0;i<10;i++)
                   {
               
                     location2(fishrow,fishcolumn);
                     location2(xiarow,xiacolumn);
                   }
            }
          else
                 {
                 	 location2(fishrow,fishcolumn);
                     labol=1;

                  }
		  break;
		}
		
    case 6:
		{
		  if(fishrow>1)fishrow--;
		  else fishrow=8;
		  fish=fishrow*100+fishcolumn*10+labol2+2;
	     if((fishrow!=xiarow2 || fishcolumn!=xiacolumn2) && labol2==0)
                {
                   for(i=0;i<10;i++)
                   {
                     location2(fishrow,fishcolumn);
                     location2(xiarow2,xiacolumn2);
                
                   }
                 }
               else if(labol2==0)labol2=1;
               if((fishrow!=xiarow3 || fishcolumn!=xiacolumn3)  && labol2==1)
                {
                   for(i=0;i<10;i++)
                   {
                     location2(fishrow,fishcolumn);
                     location2(xiarow3,xiacolumn3);
                
                   }
                 }
                 else if(labol2==1)
                 {
                     location2(fishrow,fishcolumn);
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
                     location2(fishrow,fishcolumn);
                     location2(xiarow2,xiacolumn2);
                
                   }
                 }
               else if(labol2==0)labol2=1;
               if((fishrow!=xiarow3 || fishcolumn!=xiacolumn3)  && labol2==1)
                {
                   for(i=0;i<10;i++)
                   {
                     location2(fishrow,fishcolumn);
                     location2(xiarow3,xiacolumn3);
                
                   }
                 }
                 else if(labol2==1)
                 {
                     location2(fishrow,fishcolumn);
                  }
		  break;
		}
    case 9:
		{
		   if(fishcolumn>1)
	       fishcolumn--;
		  else fishcolumn=8;
		 fish=fishrow*100+fishcolumn*10+labol2+2;
	   if((fishrow!=xiarow2 || fishcolumn!=xiacolumn2) && labol2==0)
                {
                   for(i=0;i<10;i++)
                   {
                     location2(fishrow,fishcolumn);
                     location2(xiarow2,xiacolumn2);
                
                   }
                 }
               else if(labol2==0)labol2=1;
               if((fishrow!=xiarow3 || fishcolumn!=xiacolumn3)  && labol2==1)
                {
                   for(i=0;i<10;i++)
                   {
                     location2(fishrow,fishcolumn);
                     location2(xiarow3,xiacolumn3);
                
                   }
                 }
                 else if(labol2==1)
                 {
                     location2(fishrow,fishcolumn);
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
                     location2(fishrow,fishcolumn);
                     location2(xiarow2,xiacolumn2);
                
                   }
                 }
               else if(labol2==0)labol2=1;
               if((fishrow!=xiarow3 || fishcolumn!=xiacolumn3)  && labol2==1)
                {
                   for(i=0;i<10;i++)
                   {
                     location2(fishrow,fishcolumn);
                     location2(xiarow3,xiacolumn3);
                
                   }
                 }
                 else if(labol2==1)
                 {
                     location2(fishrow,fishcolumn);
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
                    location2(fishrow,fishcolumn);
                     location2(xiarow4,xiacolumn4);
                
                   }
                 }
               else if(labol3==0)labol3=1;
               if((fishrow!=xiarow5 || fishcolumn!=xiacolumn5)  && labol3==1)
                {
                   for(i=0;i<10;i++)
                   {
                    location2(fishrow,fishcolumn);
                     location2(xiarow5,xiacolumn5);
                
                   }
                 }
                 else if(labol3==1)labol3=2;
                 if((fishrow!=xiarow6|| fishcolumn!=xiacolumn6) && labol3==2)
                {
                   for(i=0;i<10;i++)
                   {
                    location2(fishrow,fishcolumn);
                     location2(xiarow6,xiacolumn6);
                   }
                 }
                else if(labol3==2)
                 {
                   location2(fishrow,fishcolumn);
                   labol3=3;
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
                    location2(fishrow,fishcolumn);
                     location2(xiarow4,xiacolumn4);
                
                   }
                 }
               else if(labol3==0)labol3=1;
               if((fishrow!=xiarow5 || fishcolumn!=xiacolumn5)  && labol3==1)
                {
                   for(i=0;i<10;i++)
                   {
                    location2(fishrow,fishcolumn);
                     location2(xiarow5,xiacolumn5);
                
                   }
                 }
                 else if(labol3==1)labol3=2;
                 if((fishrow!=xiarow6|| fishcolumn!=xiacolumn6) && labol3==2)
                {
                   for(i=0;i<10;i++)
                   {
                    location2(fishrow,fishcolumn);
                     location2(xiarow6,xiacolumn6);
                   }
                 }
                else if(labol3==2)
                 {
                   location2(fishrow,fishcolumn);
                   labol3=3;
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
                    location2(fishrow,fishcolumn);
                     location2(xiarow4,xiacolumn4);
                
                   }
                 }
               else if(labol3==0)labol3=1;
               if((fishrow!=xiarow5 || fishcolumn!=xiacolumn5)  && labol3==1)
                {
                   for(i=0;i<10;i++)
                   {
                    location2(fishrow,fishcolumn);
                     location2(xiarow5,xiacolumn5);
                
                   }
                 }
                 else if(labol3==1)labol3=2;
                 if((fishrow!=xiarow6|| fishcolumn!=xiacolumn6) && labol3==2)
                {
                   for(i=0;i<10;i++)
                   {
                    location2(fishrow,fishcolumn);
                     location2(xiarow6,xiacolumn6);
                   }
                 }
                else if(labol3==2)
                 {
                   location2(fishrow,fishcolumn);
                   labol3=3;
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
                    location2(fishrow,fishcolumn);
                     location2(xiarow4,xiacolumn4);
                
                   }
                 }
           else if(labol3==0)labol3=1;
          if((fishrow!=xiarow5 || fishcolumn!=xiacolumn5)  && labol3==1)
                {
                   for(i=0;i<10;i++)
                   {
                    location2(fishrow,fishcolumn);
                     location2(xiarow5,xiacolumn5);
                
                   }
                 }
                 else if(labol3==1)labol3=2;
                 if((fishrow!=xiarow6|| fishcolumn!=xiacolumn6) && labol3==2)
                {
                   for(i=0;i<10;i++)
                   {
                    location2(fishrow,fishcolumn);
                     location2(xiarow6,xiacolumn6);
                   }
                 }
                else if(labol3==2)
                 {
                   location2(fishrow,fishcolumn);
                   labol3=3;
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
