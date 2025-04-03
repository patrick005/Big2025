/*
sudo insmod led_driver.ko
dmesg | tail -5
ls /dev -l
sudo mknod /dev/led_driver c 221 0
sudo chmod 666 /dev/led_driver

*/
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>

#define DEV_MAJOR_NUMBER 221
#define DEV_NAME "led_driver"

int led[4] = {23 +512, 24+512, 25+512, 1+512};

static int led_driver_open(struct inode *inode, struct file *file);
static int led_driver_release(struct inode *inode, struct file *file);
static ssize_t led_driver_write(struct file *file, const char __user *buf, size_t length, loff_t *ofs);
// static ssize_t led_driver_read(struct file *file, char __user *buf, size_t length, loff_t *ofs);

static struct file_operations led_driver_fops = {
    .owner = THIS_MODULE,
    .open = led_driver_open,
    .release = led_driver_release,
    .write = led_driver_write,
    // .read = led_driver_read
};

static int led_driver_init(void){
    printk(KERN_INFO "led_driver_init!\n");
    register_chrdev(DEV_MAJOR_NUMBER, DEV_NAME, &led_driver_fops);
    return 0;
}

static void led_driver_exit(void){
    printk(KERN_INFO "led_driver_exit!\n");
    unregister_chrdev(DEV_MAJOR_NUMBER, DEV_NAME);
}

static int led_driver_open(struct inode *inode, struct file *file){
    int ret, i;
    printk(KERN_INFO "led driver open!\n");
    for(i = 0; i<4; i++){
        ret = gpio_request(led[i], "LED");
        if(ret<0){
            printk(KERN_INFO "led driver %d request fail!\n", i);
        }
    }
    return 0;
}

static int led_driver_release(struct inode *inode, struct file *file){
    int i;
    printk(KERN_INFO "led driver release!\n");
    for(i = 0; i<4; i++){
        gpio_free(led[i]);
    }
    return 0;
}
static ssize_t led_driver_write(struct file *file, const char __user *buf, size_t length, loff_t *ofs){
    int ret, i;
    unsigned char cbuf[4];
    printk(KERN_INFO "led driver write!\n");
    ret = copy_from_user(cbuf, buf, length);
    if(ret<0){
        printk(KERN_INFO "lcopy from user error!\n");
    }
    for(i = 0; i<4; i++){
        gpio_direction_output(led[i], cbuf);
        if(ret<0){
            printk(KERN_INFO "led driver %d direction fail!\n", i);
        }
    }
    return 0;
}
// static ssize_t led_driver_read(struct file *file, char __user *buf, size_t length, loff_t *ofs){
//     printk(KERN_INFO "led driver read!\n");
//     return 0;
// }

module_init(led_driver_init);
module_exit(led_driver_exit);
MODULE_LICENSE("GPL");