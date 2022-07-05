#include <linux/module.h>    
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/usb.h>
#include <linux/usb/input.h>
#include <linux/hid.h>
#include <linux/netdevice.h>

#define VENDOR_ID 0x05C6
#define DEVICE_ID 0x9091

struct driver_info {
        char            *description;
        int              flag;
};

static const struct driver_info test_info = {
	.description = "Biao Wang test driver info",
};


static struct usb_device_id usb_test_table[] = {
        {USB_DEVICE_INTERFACE_NUMBER(VENDOR_ID, DEVICE_ID, 1), .driver_info=(unsigned long)&test_info},
	{ } /* Terminating entry */
};

MODULE_DEVICE_TABLE(usb, usb_test_table);

static int usb_test_probe(struct usb_interface *intf,const struct usb_device_id *prod)
{
	struct driver_info *info;
	info = (struct driver_info *)prod->driver_info;
	printk("[%s] description: %s \n",__func__, info->description);
	return 0;
}

static void usb_test_disconnect(struct usb_interface *intf)
{
	printk("[%s] \n",__func__);
}

static struct usb_driver usb_test_driver = {
	.name 		= "usb_test_driver_info",
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

MODULE_AUTHOR("Bjørn Mork <bjorn@mork.no>");
MODULE_DESCRIPTION("Qualcomm MSM Interface (QMI) WWAN driver");
MODULE_LICENSE("GPL");
