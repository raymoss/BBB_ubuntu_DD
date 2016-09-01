#include "linux/usb.h"
#include "linux/kernel.h"
#include "linux/module.h"
#include <linux/slab.h>
static struct urb *urb;
static struct usb_device *device;
static unsigned char *data;
static unsigned char *recvdata;

static void usb_irq(struct urb *urb);
static int usb_probe(struct usb_interface *interface,const struct usb_device_id *id){
    int retval;
    struct usb_host_interface *iface_desc;
    struct usb_endpoint_descriptor *endpoint;
    int i;
    iface_desc=interface->cur_altsetting;
    printk(KERN_INFO"MOSS:Usb interface %d now probed: (%04X,%04X)\n",iface_desc->desc.bInterfaceNumber,id->idVendor,id->idProduct);
    printk(KERN_INFO"MOSS:ID->bNumEndpoints: %02X\n",iface_desc->desc.bNumEndpoints);
    for (i=0;i<iface_desc->desc.bNumEndpoints;i++){
        endpoint = &iface_desc->endpoint[i].desc;
        printk(KERN_INFO"MOSS:ED[%d]->bEndpointAddress:0x%02X\n",i,endpoint->bEndpointAddress);
        printk(KERN_INFO "MOSS:ED[%d]->bmAttributes: 0x%02X\n",
                i, endpoint->bmAttributes);
        printk(KERN_INFO "MOSS:ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
                i, endpoint->wMaxPacketSize, endpoint->wMaxPacketSize);
    }
    device = interface_to_usbdev(interface);
    urb=usb_alloc_urb(0,GFP_KERNEL);
    if(!urb){
        printk(KERN_ERR"Failed to create urb");
        goto error;
    }
    data=kmalloc(5*sizeof(char),GFP_KERNEL);

    int pipe = usb_rcvintpipe(device, endpoint->bEndpointAddress);
	int maxp = usb_maxpacket(device, pipe, usb_pipeout(pipe));
    printk(KERN_INFO"maxp=%d",maxp);
    usb_fill_int_urb(urb,device,usb_rcvintpipe(device,endpoint->bEndpointAddress),data, maxp ,usb_irq,device,endpoint->bInterval);
    /* send the data out the bulk port */
    printk(KERN_INFO"Successfully created the urb");
    retval = usb_submit_urb(urb, GFP_KERNEL);
    printk(KERN_INFO"Successfully created the urb %d",retval);
    if (retval) {
        printk(KERN_ERR"%s - failed submitting write urb, error %d", __FUNCTION__, retval);
        goto error;
    }

    // idiom = kmalloc(sizeof(struct idiom_device), GFP_KERNEL);
    // if (!idiom) return NULL; /* failure */
    // memset(idiom, 0, sizeof(*idiom));
    //
    //     /* fill the URB data structure using the FILL_INT_URB macro */
    //     static void idiom_irq(struct urb *urb); /* forward declaration */
    // 	int pipe = usb_rcvintpipe(udev, endpoint->bEndpointAddress);
    // 	int maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
    //
    // 	FILL_INT_URB(&idiom->urb, udev, pipe, idiom->data, maxp > 3 ? 3 : maxp,
    // 		      idiom_irq, idiom, endpoint->bInterval);
    //
    //
    //     /* register the URB within the USB subsystem */
    //     if (usb_submit_urb(&idiom->urb)) {
    // 	kfree(idiom);
    // 	return NULL;
    //     }
    return 0;
    error:
        //usb_deregister(&mouse_driver);
        return -1;
}
static void usb_irq(struct urb *urb){
int retval;
    switch(urb->status)
{
    case 0:
        printk(KERN_INFO"Success");
        break;
}

    //printk(KERN_INFO"MOSS: Status of urb: %d",urb->status);
    recvdata=urb->transfer_buffer;
    if((*recvdata)==2){
        printk(KERN_INFO"MOSS: Right click pressed: %d",(*recvdata));
        printk(KERN_INFO"MOSS: x shift : %d",*(recvdata+1));
        printk(KERN_INFO"MOSS: y shift : %d",*(recvdata+2));
}
if((*recvdata)==0){
    printk(KERN_INFO"MOSS: Right click released: %d",(*recvdata));
    printk(KERN_INFO"MOSS: X shift: %d",*(recvdata+1));
    printk(KERN_INFO"MOSS: y shift: %d",*(recvdata+2));
}
resubmit:
retval = usb_submit_urb (urb, GFP_ATOMIC);
if (retval)
    printk(KERN_INFO"can't resubmit retval %d",retval);
}


static void usb_disconnect(struct usb_interface *interface){
    printk(KERN_INFO"MOSS: Disconnecting %d USB device",interface->cur_altsetting->desc.bInterfaceNumber);
}
static struct usb_device_id usb_table[] = {
        {USB_DEVICE(0x045e,0x0797)},{}

    };
MODULE_DEVICE_TABLE(usb,usb_table);
static struct usb_driver mouse_driver =
    {
        .name="mouse_driver",
        .probe=usb_probe,
        .disconnect=usb_disconnect,
        .id_table = usb_table,
    };
static int __init usb_init(void){
        return usb_register(&mouse_driver);
    }
static void __exit usb_exit(void){
        return usb_deregister(&mouse_driver);
    }


module_init(usb_init);
module_exit(usb_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RayMoss<itsraymoss@gmail.com>");
MODULE_DESCRIPTION("USB MOuse Driver");
