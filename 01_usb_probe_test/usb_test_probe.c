#include <linux/module.h>    
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/usb.h>
#include <linux/usb/input.h>
#include <linux/hid.h>
#include <linux/netdevice.h>

#define VENDOR_ID 0x2C7C
#define DEVICE_ID 0x0125

static struct usb_device_id usb_test_table[] = {
        { USB_DEVICE(VENDOR_ID, DEVICE_ID) },
        { } /* Terminating entry */
};

MODULE_DEVICE_TABLE(usb, usb_test_table);

static int usb_test_probe(struct usb_interface *intf,const struct usb_device_id *prod)
{
	printk("[%s] \n",__func__);
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

MODULE_AUTHOR("BiaoWang>");
MODULE_DESCRIPTION("BiaoWang Test");
MODULE_LICENSE("GPL");
