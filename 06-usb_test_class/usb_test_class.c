#include <linux/module.h>    
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/usb.h>
#include <linux/usb/input.h>
#include <linux/hid.h>
#include <linux/netdevice.h>
#include <linux/bitops.h>
#include <linux/jiffies.h>
#include <linux/errno.h>
#include <linux/usb/cdc.h>


static struct usb_device_id usb_test_table[] = {
	{USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_NCM, USB_CDC_PROTO_NONE),},
	{ USB_VENDOR_AND_INTERFACE_INFO(0x0bdb, USB_CLASS_COMM, USB_CDC_SUBCLASS_MBIM, USB_CDC_PROTO_NONE),},
	{ USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_MBIM, USB_CDC_PROTO_NONE),},
	{ } /* Terminating entry */
};


MODULE_DEVICE_TABLE(usb, usb_test_table);

static int usb_test_probe(struct usb_interface *intf,const struct usb_device_id *prod)
{
	struct usb_interface_descriptor *iface_desc = &intf->cur_altsetting->desc;

	unsigned int bInterfaceClass = (unsigned int)iface_desc->bInterfaceClass;
	unsigned int bInterfaceSubClass = (unsigned int)iface_desc->bInterfaceSubClass;
	unsigned int bInterfaceProtocol = (unsigned int)iface_desc->bInterfaceProtocol;

	printk("[%s] 0x%x, 0x%x,0x%x \n",__func__,bInterfaceClass,bInterfaceSubClass,bInterfaceProtocol);
	return 0;
}

static void usb_test_disconnect(struct usb_interface *intf)
{
	printk("[%s] \n",__func__);
}

static struct usb_driver usb_test_driver = {
	.name 		= "usb_test",
	.id_table 	= usb_test_table,
	.probe		= usb_test_probe,
	.disconnect	= usb_test_disconnect,
};


static int __init usb_test_init(void)
{
	return usb_register(&usb_test_driver);
}

static void __exit usb_test_exit(void)
{
	usb_deregister(&usb_test_driver);
}

module_init(usb_test_init);
module_exit(usb_test_exit);

MODULE_AUTHOR("VincentW <biao.wang>");
MODULE_DESCRIPTION("BW USB driver driver");
MODULE_LICENSE("GPL");
