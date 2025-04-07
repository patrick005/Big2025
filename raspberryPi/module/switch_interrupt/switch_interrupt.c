#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/gpio.h>

int sw[4] = {4 +512, 17+512, 27+512, 22+512};

irq_handler_t irq_handler(int irq, void *dev_id);

static int switch_interrupt_init(void){
    int ret, i = 0;
    printk(KERN_INFO "switch interrupt init!\n");
    for(i = 0; i<4; i++){
        ret = gpio_request(sw[i], "SWITCH");
        ret = request_irq(gpio_to_irq(sw[i]),(irq_handler_t)irq_handler, IRQF_TRIGGER_RISING, "IRQ", (void *)(irq_handler));
        if(ret<0){
            printk(KERN_INFO "SWITCH gpio request faild!\n");
        }
    }
    return 0;
}

static void switch_interrupt_exit(void){
    int i;
    printk(KERN_INFO "switch_interrupt_exit!\n");
    for(i=0; i<4; i++){
        free_irq(sw[i], (void *)irq_handler);
        gpio_free(sw[i]);
    }
    printk(KERN_INFO "all interrupt gpios freed successfully.\n");
}

irq_handler_t irq_handler(int irq, void *dev_id){
    printk(KERN_INFO "debug %d!\n", irq);
    return 0;
}

module_init(switch_interrupt_init);
module_exit(switch_interrupt_exit);
MODULE_LICENSE("GPL");