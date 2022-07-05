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

#define VENDOR_ID 0x2C7C
#define DEVICE_ID 0x0125

#define MAX_BL_NUM  11
enum blacklist_reason {
		BLACKLIST_NONE = 0,
		BLACKLIST_SENDSETUP = 1,
		BLACKLIST_RESERVED_IF = 2
};

struct blacklist_info {
	/* bitfield of interface numbers for BLACKLIST_SENDSETUP */
	const unsigned long sendsetup;
	/* bitfield of interface numbers for BLACKLIST_RESERVED_IF */
	const unsigned long reserved;
};

static const struct blacklist_info usb_blacklist_info = {
	.sendsetup = BIT(0) | BIT(1),
	.reserved = BIT(4),
};

static struct usb_device_id usb_test_table[] = {
        {USB_DEVICE(VENDOR_ID, DEVICE_ID), 
	.driver_info=(unsigned long)&usb_blacklist_info},
	{ } /* Terminating entry */
};

MODULE_DEVICE_TABLE(usb, usb_test_table);


static bool is_blacklisted(const u8 ifnum, enum blacklist_reason reason,
			   const struct blacklist_info *blacklist)
{
	unsigned long num;
	const unsigned long *intf_list;

	if (blacklist) {
		if (reason == BLACKLIST_SENDSETUP)
			intf_list = &blacklist->sendsetup;
		else if (reason == BLACKLIST_RESERVED_IF)
			intf_list = &blacklist->reserved;
		else {
			BUG_ON(reason);
			return false;
		}

		for_each_set_bit(num, intf_list, MAX_BL_NUM + 1) {
			if (num == ifnum)
				return true;
		}
	}
	return false;
}


static int usb_test_probe(struct usb_interface *intf,const struct usb_device_id *prod)
{
	struct usb_interface_descriptor *iface_desc;

	iface_desc = &intf->cur_altsetting->desc;

	if (is_blacklisted(
		iface_desc->bInterfaceNumber,
		BLACKLIST_RESERVED_IF,
		(const struct blacklist_info *) prod->driver_info))
			return -ENODEV;	

	printk("[%s] \n",__func__);
	return 0;
}

static void usb_test_disconnect(struct usb_interface *intf)
{
	printk("[%s] \n",__func__);
}

static struct usb_driver usb_test_driver = {
	.name 		= "usb_test_blacklist",
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
