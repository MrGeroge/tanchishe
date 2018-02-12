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

#define DEVICE_NAME "seg"   

static void __iomem *io_base1, *io_base2;  

unsigned char seg7table[17] = {   
    /* 0       1       2       3       4       5       6      7*/
    0xc0,   0xf9,   0xa4,   0xb0,   0x99,   0x92,   0x82,   0xf8,

    /* 8       9      A        B       C       D       E      F     */ 
    0x80,   0x90,   0x88,   0x83,   0xc6,   0xa1,   0x86,   0x8e,0xff,
};


static long seg_ioctl(struct file *filp, unsigned int cmd, unsigned long arg1)
{
	unsigned int guan_shi=arg1/10000;
	unsigned int guan_ge=(arg1%10000)/1000;
	unsigned int score_bai=((arg1%10000)%1000)/100;
	unsigned int score_shi=(((arg1%10000)%1000)%100)/10;
	unsigned int score_ge=(((arg1%10000)%1000)%100)%10;
	unsigned int a[6];
        //a[0]=guan_shi;
        //a[1]=guan_ge;
        //a[2]=16;
        //a[3]=score_bai;
        //a[4]=score_shi;
        //a[5]=score_ge;
        a[0]=16;
        a[1]=16;
        a[2]=16;
        a[3]=16;
        a[4]=16;
        a[5]=score_ge;
	switch(cmd) {
	case 0:{
		int j;
		for(j=0;j<6;j++){
			writeb(~(0x01<<(j)),io_base1);
			writeb(seg7table[a[j]], io_base2);
                        msleep(0.0025);
                      
		}
             }
		break;
                
	default:
		return -EINVAL;
	}
}

static struct file_operations dev_fops = {   
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= seg_ioctl,
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
	io_base1 = ioremap(0x88007000, 1);  
	if (io_base1 == 0)
	{
		printk("failed to ioremap() region\n");
	}
	else
	{
		printk("io_base = %p\n",io_base1);
		writeb(0x00, io_base1);
	}
	io_base2 = ioremap(0x88009000, 1); 
	if (io_base2 == 0)
	{
		printk("failed to ioremap() region\n");
	}
	else
	{
		printk("io_base = %p\n",io_base2);
		writeb(seg7table[15], io_base2);
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
MODULE_AUTHOR("CVTECH Inc.");
