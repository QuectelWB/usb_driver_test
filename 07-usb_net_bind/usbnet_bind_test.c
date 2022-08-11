#include <linux/module.h>    
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/version.h>
#if LINUX_VERSION_CODE > KERNEL_VERSION(4,15,0)
#include <linux/mii.h>
#endif
#include <linux/usb.h>
#include <linux/usb/cdc.h>
#include <linux/netdevice.h>
#include <linux/ethtool.h>
#include <linux/etherdevice.h>
#include <linux/usb/usbnet.h>
#define VENDOR_ID 0x2C7C
#define DEVICE_ID 0x0125

static const struct driver_info usb_test_info;

static int usbnet_test_bind(struct usbnet *dev, struct usb_interface *intf);

static void usbnet_test_unbind(struct usbnet *dev, struct usb_interface *intf);


static int usbnet_test_bind(struct usbnet *dev, struct usb_interface *intf)
{
	printk("[%s]\n",__func__);
	return 0;
}

static void usbnet_test_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	printk("[%s]\n",__func__);
}


static struct usb_device_id usb_test_table[] = {
	
		{
		USB_DEVICE_AND_INTERFACE_INFO(
				VENDOR_ID, 
				DEVICE_ID,
				USB_CLASS_COMM,
				USB_CDC_SUBCLASS_ETHERNET,
				USB_CDC_PROTO_NONE),
			.driver_info = (unsigned long)&usb_test_info,
		},
		{},
};

MODULE_DEVICE_TABLE(usb, usb_test_table);

static const struct driver_info usb_test_info = {
	.description = "CDC USB Test",
	.flags = FLAG_NO_SETINT | FLAG_MULTI_PACKET | FLAG_WWAN,
	.bind = usbnet_test_bind,
	.unbind = usbnet_test_unbind,
};

static int usb_test_probe(struct usb_interface *intf,const struct usb_device_id *prod)
{
	printk("[%s] \n",__func__);
	usbnet_probe(intf,prod);
	return 0;
}

static void usb_test_disconnect(struct usb_interface *intf)
{
	printk("[%s] \n",__func__);
}


static struct usb_driver usb_test_driver = {
	.name =		"usb_test_bind",
	.id_table =	usb_test_table,
	.probe =	usb_test_probe,
	.disconnect =	usb_test_disconnect,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.reset_resume =	usbnet_resume,
	.supports_autosuspend = 1,
	.disable_hub_initiated_lpm = 1,
};

static int __init usb_test_init(void)
{
	return usb_register(&usb_test_driver);
}

/*** 

module_usb_driver(usb_test_driver);

***/


static void __exit usb_test_exit(void)
{
	usb_deregister(&usb_test_driver);
}

module_init(usb_test_init);
module_exit(usb_test_exit);

MODULE_AUTHOR("Bjørn Mork <bjorn@mork.no>");
MODULE_DESCRIPTION("Qualcomm MSM Interface (QMI) WWAN driver");
MODULE_LICENSE("GPL");
