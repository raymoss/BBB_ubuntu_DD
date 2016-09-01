#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>
static dev_t first;
static struct cdev c_dev;
static struct class *cl;
static char c;
static int my_open(struct inode *i,struct file *f){
printk(KERN_INFO"Moss: open()\n");
return 0;
}
static int my_close(struct inode *i,struct file *f){
printk(KERN_INFO"Moss:close()\n");
return 0;
}
static ssize_t my_read(struct file *f,char __user *buf,size_t len, loff_t *off){
printk(KERN_INFO "Driver: read()\n");
	if (*off == 0)
	{
		if (copy_to_user(buf, &c, 1) != 0)
			return -EFAULT;
		else
		{
			(*off)++;
			return 1;
		}
	}
	else
		return 0;
}
static ssize_t my_write(struct file *f,const char __user *buf,size_t len,loff_t *off){
printk(KERN_INFO"MOss:write()\n");
if (copy_from_user(&c,buf+len-1,1)!=0)
        return -EFAULT;
else
return len;
}
static struct file_operations moss_fops=
{
.owner = THIS_MODULE,
.open=my_open,
.write=my_write,
.read=my_read,
.release=my_close
};

static int __init ofcd_init(void){
int ret;
struct device *dev_ret;
printk(KERN_INFO"Moss:Initializing driver");
if ((ret=alloc_chrdev_region(&first,0,1,"Moss")<0))
return ret;
if (IS_ERR(cl=class_create(THIS_MODULE,"chardrv"))){
unregister_chrdev_region(first,1);
return PTR_ERR(cl);
}
if (IS_ERR(device_create(cl,NULL,first,NULL,"mynull"))){
class_destroy(cl);
unregister_chrdev_region(first,1);
return PTR_ERR(dev_ret);
}
cdev_init(&c_dev,&moss_fops);
if(ret=cdev_add(&c_dev,first,1)<0){
device_destroy(cl,first);
class_destroy(cl);
unregister_chrdev_region(first,1);
return ret;
}
return 0;
}

static void __exit ofcd_exit(void){
cdev_del(&c_dev);
device_destroy(cl,first);
class_destroy(cl);
unregister_chrdev_region(first,1);
printk(KERN_INFO"Moss:Unregistering driver");
}

module_init(ofcd_init);
module_exit(ofcd_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ray MOss <itsraymoss@gmail.com>");
MODULE_DESCRIPTION("Second character driver");

