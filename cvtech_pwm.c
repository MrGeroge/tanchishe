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
#include <mach/gpio-bank.h>

#include <plat/gpio-cfg.h>

#define DEVICE_NAME "pwm"

static long pwm_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

       unsigned int tmp;
	int i;
	switch(cmd) {
	case 0:{
		  tmp = __raw_readl(S5PV210_GPD0DAT);
		  tmp |= 0x8;
		  __raw_writel(tmp, S5PV210_GPD0DAT);
                }         	 
		break;
	case 1:
		{
		  tmp = __raw_readl(S5PV210_GPD0DAT);
		  tmp &= 0x7;
		  __raw_writel(tmp, S5PV210_GPD0DAT);		 
		}
		break;
        
	default:
		return -EINVAL;
	}
}

static struct file_operations dev_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= pwm_ioctl,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};

static int __init dev_init(void)
{
	int ret;
	unsigned int tmp;

	ret = misc_register(&misc);

	tmp = __raw_readl(S5PV210_GPD0CON);
	tmp &= ~(0xf << 12);
	tmp |= 0x1 << 12;
	__raw_writel(tmp, S5PV210_GPD0CON);

	printk ("[***" DEVICE_NAME "***]:initialized\n");

	return ret;
}

static void __exit dev_exit(void)
{
	misc_deregister(&misc);
}



module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPD");
MODULE_AUTHOR("CVTECH Inc.");
