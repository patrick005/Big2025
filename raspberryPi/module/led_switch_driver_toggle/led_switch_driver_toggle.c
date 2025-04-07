/*
sudo insmod led_switch_driver.ko
dmesg
sudo mknod /dev/led_switch_driver c 222 0
sudo chmod 666 /dev/led_switch_driver
*/
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>

#define DEV_MAJOR_NUMBER 222
#define DEV_NAME "led_switch_driver"

static int led_switch_driver_open(struct inode *inode, struct file *file);
static int led_switch_driver_release(struct inode *inode, struct file *file);
static ssize_t led_switch_driver_write(struct file *file, const char __user *buf, size_t length, loff_t *ofs);
static ssize_t led_switch_driver_read(struct file *file, char __user *buf, size_t length, loff_t *ofs);

int led[4] = {23 + 512, 24 + 512, 25 + 512, 1 + 512};
int sw[4] = {4 + 512, 17 + 512, 27 + 512, 22 + 512};
static int irq_num[4] = {58, 59, 60, 61};
char read_buf[4];
char led_status[4] = {0};

static struct file_operations led_switch_driver_fops = {
    .owner = THIS_MODULE,
    .open = led_switch_driver_open,
    .release = led_switch_driver_release,
    .write = led_switch_driver_write,
    .read = led_switch_driver_read,
};

static irqreturn_t switch_irq_handler(int irq, void *dev_id) {
    int i;
    for (i = 0; i < 4; i++) {
        if (irq == irq_num[i]) {
            read_buf[i] = gpio_get_value(sw[i]);
            break;
        }
    }
    return IRQ_HANDLED;
}

static int led_switch_driver_init(void) {
    int ret, i;
    printk(KERN_INFO "led switch driver init!\n");
    register_chrdev(DEV_MAJOR_NUMBER, DEV_NAME, &led_switch_driver_fops);

    for (i = 0; i < 4; i++) {
        ret = request_irq(irq_num[i], switch_irq_handler, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "switch_irq", NULL);
        if (ret < 0) {
            printk(KERN_ERR "Failed to request IRQ %d\n", irq_num[i]);
            // 에러 처리
        }
    }
    return 0;
}

static void led_switch_driver_exit(void) {
    int i;
    printk(KERN_INFO "led switch driver exit!\n");
    unregister_chrdev(DEV_MAJOR_NUMBER, DEV_NAME);

    for (i = 0; i < 4; i++) {
        free_irq(irq_num[i], NULL);
    }
}

static int led_switch_driver_open(struct inode *inode, struct file *file) {
    int ret, ret1, i;
    printk(KERN_INFO "led switch driver open!\n");
    for (i = 0; i < 4; ++i) {
        ret = gpio_request(sw[i], "switch");
        if (ret < 0) {
            printk(KERN_INFO "switch driver %d request fail!\n", i);
        }
        ret1 = gpio_request(led[i], "LED");
        if (ret1 < 0) {
            printk(KERN_INFO "led driver %d request fail!\n", i);
        }
        ret = gpio_direction_input(sw[i]);
        if (ret < 0) {
            printk(KERN_INFO "switch driver %d direction input fail!\n", i);
        }
        ret1 = gpio_direction_output(led[i], 0);
        if (ret1 < 0) {
            printk(KERN_INFO "led driver %d direction output fail!\n", i);
        }
    }
    return 0;
}

static int led_switch_driver_release(struct inode *inode, struct file *file) {
    int i;
    printk(KERN_INFO "led switch driver release!\n");
    for (i = 0; i < 4; ++i) {
        gpio_free(sw[i]);
        gpio_free(led[i]);
    }
    return 0;
}

static ssize_t led_switch_driver_read(struct file *file, char __user *buf, size_t length, loff_t *ofs) {
    int ret, i;
    printk(KERN_INFO "led_switch_driver_read!\n");
    for (i = 0; i < 4; ++i) {
        read_buf[i] = gpio_get_value(sw[i]);
    }
    ret = copy_to_user(buf, read_buf, sizeof(read_buf));
    if (ret < 0) {
        printk(KERN_INFO "switch driver copy to user fail!\n");
    }
    return sizeof(read_buf);
}

static ssize_t led_switch_driver_write(struct file *file, const char __user *buf, size_t length, loff_t *ofs) {
    int ret, i;
    char write_buf[4];
    printk(KERN_INFO "led driver write!\n");
    ret = copy_from_user(write_buf, buf, length);
    if (ret < 0) {
        printk(KERN_INFO "copy from user error!\n");
    }
    for (i = 0; i < 4; i++) {
        if (write_buf[i] == 1) {
            led_status[i] = !led_status[i];
            gpio_set_value(led[i], led_status[i]);
        }
    }
    return length;
}

module_init(led_switch_driver_init);
module_exit(led_switch_driver_exit);
MODULE_LICENSE("GPL");