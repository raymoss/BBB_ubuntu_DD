#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>

static dev_t first;
static int __init initializer(void){
printk(KERN_INFO"Moss:Char device registered");
if(alloc_chrdev_region(&first,0,3,"Char_driver")<0){
return -1;
}
printk(KERN_INFO"Moss:<Major,Minor>:<%d,%d>",MAJOR(first),MINOR(first));
return 0;
}
static void __exit destructor(void){
unregister_chrdev_region(first,3);
printk(KERN_INFO"Moss:Unregistered drivers");
}
module_init(initializer);
module_exit(destructor);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Moss<itsraymoss@gmail.com>");
MODULE_DESCRIPTION("First char device");

