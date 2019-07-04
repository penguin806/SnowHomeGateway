/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <asm/mach-types.h>
#include <linux/gpio.h>
#include <asm/gpio.h>
#include <asm/delay.h>
#include <linux/clk.h>
#include <mach/gpio.h>
#include <mach/soc.h>
#include <mach/platform.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include <asm/io.h>

#define DEVICE_NAME				"cled_ctl"

#define DRIVER_NAME "cled_ctl"


#define GPIOA_NAME		"cled_ctl"

#define GPIOA0			(PAD_GPIO_A + 0)
#define GPIOA1			(PAD_GPIO_A + 1)
#define GPIOA2			(PAD_GPIO_A + 2)
#define GPIOA3			(PAD_GPIO_A + 3)
#define GPIOA4			(PAD_GPIO_A + 4)
#define GPIOA5			(PAD_GPIO_A + 5)
#define GPIOA6			(PAD_GPIO_A + 6)
#define GPIOA7			(PAD_GPIO_A + 7)

#define GPIOA23			(PAD_GPIO_A + 23)

#define GPIO_INT_BASE		(void __iomem *)IO_ADDRESS(PHY_BASEADDR_GPIOA)

static int cled_gpio_init(void){
	int ret;

	ret = gpio_request(GPIOA0, GPIOA_NAME);
	if (ret) {
		printk("request GPIO %d for cled_ctl failed\n", GPIOA0);
		return ret;
	}

	ret = gpio_request(GPIOA1, GPIOA_NAME);
	if (ret) {
		printk("request GPIO %d for cled_ctl failed\n", GPIOA1);
		return ret;
	}

	ret = gpio_request(GPIOA2, GPIOA_NAME);
	if (ret) {
		printk("request GPIO %d for cled_ctl failed\n", GPIOA2);
		return ret;
	}

	ret = gpio_request(GPIOA3, GPIOA_NAME);
	if (ret) {
		printk("request GPIO %d for cled_ctl failed\n", GPIOA3);
		return ret;
	}

	ret = gpio_request(GPIOA4, GPIOA_NAME);
	if (ret) {
		printk("request GPIO %d for cled_ctl failed\n", GPIOA4);
		return ret;
	}

	ret = gpio_request(GPIOA5, GPIOA_NAME);
	if (ret) {
		printk("request GPIO %d for cled_ctl failed\n", GPIOA5);
		return ret;
	}

	ret = gpio_request(GPIOA6, GPIOA_NAME);
	if (ret) {
		printk("request GPIO %d for cled_ctl failed\n", GPIOA6);
		return ret;
	}

	ret = gpio_request(GPIOA7, GPIOA_NAME);
	if (ret) {
		printk("request GPIO %d for cled_ctl failed\n", GPIOA7);
		return ret;
	}

	ret = gpio_request(GPIOA23, GPIOA_NAME);
	if (ret) {
		printk("request GPIO %d for cled_ctl failed\n", GPIOA23);
		return ret;
	}

	gpio_direction_output(GPIOA0, 0);
	gpio_direction_output(GPIOA1, 0);
	gpio_direction_output(GPIOA2, 0);
	gpio_direction_output(GPIOA3, 0);
	gpio_direction_output(GPIOA4, 0);
	gpio_direction_output(GPIOA5, 0);
	gpio_direction_output(GPIOA6, 0);
	gpio_direction_output(GPIOA7, 0);

	gpio_direction_output(GPIOA23, 0);
}

static void cled_gpio_free(){
	gpio_free(GPIOA0);
	gpio_free(GPIOA1);
	gpio_free(GPIOA2);
	gpio_free(GPIOA3);
	gpio_free(GPIOA4);
	gpio_free(GPIOA5);
	gpio_free(GPIOA6);
	gpio_free(GPIOA7);

	gpio_free(GPIOA23);
}

static void cled_gpio_ctl(int bit){
	int tmp=0;
	gpio_set_value(GPIOA23, 0);

	tmp = readl(GPIO_INT_BASE);
	tmp &= ~(0xFF);
	tmp |= (1<<bit);
	writel(tmp, GPIO_INT_BASE);

	gpio_set_value(GPIOA23, 1);
}

static void cled_gpio_ctl_for_snow_home_gateway(int controlBits){
	int tmp=0;
	gpio_set_value(GPIOA23, 0);

	tmp = readl(GPIO_INT_BASE);
	tmp &= ~(0xFF);
	tmp |= controlBits;
	writel(tmp, GPIO_INT_BASE);

	gpio_set_value(GPIOA23, 1);
}

static int cvt_cled_open(struct inode *inode, struct file *file) {
		return 0;
}

static int cvt_cled_close(struct inode *inode, struct file *file) {
	return 0;
}

struct ioctl_arguments
{
    unsigned long cmd_type;
    unsigned long bit;
};
typedef struct ioctl_arguments IOCTL_ARG;

static long cvt_cled_ioctl(struct file *filep, unsigned int cmd,
                           unsigned long arg)
{
    printk("%s: arg = %d\n", __FUNCTION__, arg);
	
    cled_gpio_ctl_for_snow_home_gateway(arg);

    return 0;
}

static struct file_operations cvt_cled_ops = {
	.owner			= THIS_MODULE,
	.open			= cvt_cled_open,
	.release		= cvt_cled_close, 
	.unlocked_ioctl	= cvt_cled_ioctl,
};

static struct miscdevice cvt4418_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &cvt_cled_ops,
};

static int cvt_cled_probe(struct platform_device *pdev)
{
	int ret,i;

	/*cled_gpio_free();
	cled_gpio_init();

	for(i = 0;i<8;i++){
		cled_gpio_ctl(i);		
		msleep(150);
	}

	cled_gpio_free();*/


	ret = misc_register(&cvt4418_misc_dev);

	printk(DEVICE_NAME "\tinitialized\n");

	return ret;
}

static int cvt_cled_remove (struct platform_device *pdev)
{
	misc_deregister(&cvt4418_misc_dev);
	cled_gpio_free();

	return 0;
}

static int cvt_cled_suspend (struct platform_device *pdev, pm_message_t state)
{
	printk("cled_ctl suspend:power off!\n");
	return 0;
}

static int cvt_cled_resume (struct platform_device *pdev)
{
	printk("cled_ctl resume:power on!\n");
	return 0;
}

static struct platform_driver cvt_cled_driver = {
	.probe = cvt_cled_probe,
	.remove = cvt_cled_remove,
	.suspend = cvt_cled_suspend,
	.resume = cvt_cled_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	},
};

static int __init cvt_cled_dev_init(void) {
	return platform_driver_register(&cvt_cled_driver);
}

static void __exit cvt_cled_dev_exit(void) {
	platform_driver_unregister(&cvt_cled_driver);
}

module_init(cvt_cled_dev_init);
module_exit(cvt_cled_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YL Inc.");
MODULE_DESCRIPTION("S5PXX18 cled Driver");
