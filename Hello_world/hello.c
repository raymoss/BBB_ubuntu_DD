#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raymoss<itsraymoss@gmail.com>");
MODULE_DESCRIPTION("Hello world demo");
MODULE_VERSION("1.0");

static char *name="BEE";
module_param(name,charp,S_IRUGO);
MODULE_PARM_DESC(name,"The name to display in the message");

static int  __init helloBBB(void){
    printk(KERN_INFO"BBB:Hey %s , the module is loaded",name);
    return 0;
}

static void __exit byeBBB(void){
    printk(KERN_INFO"BBB:Bye, unloading the module");
}

module_init(helloBBB);
module_exit(byeBBB);
