#include <linux/module.h>    
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/usb.h>
#include <linux/usb/cdc.h>
#define VENDOR_ID 0x2C7C
#define DEVICE_ID 0x0125
#define MAX_NUM_PORTS  (8)
static const struct driver_info usb_test_info;

struct driver_info {
	char		*description;
	int		flags;
#define FLAG_A		0x0001
#define FLAG_B		0x0002
#define FLAG_C		0x0004
#define FLAG_D		0x0008
	int	(*bind)(struct usb_interface *);
	void	(*unbind)(struct usb_interface *);
};

static int usb_test_bind(struct usb_interface *intf)
{
	printk("[%s]\n",__func__);
	return 0;
}

static void usb_test_unbind(struct usb_interface *intf)
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
	.flags = FLAG_A | FLAG_B,
	.bind = usb_test_bind,
	.unbind = usb_test_unbind,
};

static int usb_test_probe(struct usb_interface *intf,const struct usb_device_id *prod)
{

	struct device *ddev = &intf->dev;
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usb_host_interface *iface_desc = intf->cur_altsetting;
	
	struct usb_endpoint_descriptor *endpoint;
	struct usb_endpoint_descriptor *interrupt_in_endpoint[MAX_NUM_PORTS];
	struct usb_endpoint_descriptor *interrupt_out_endpoint[MAX_NUM_PORTS];
	struct usb_endpoint_descriptor *bulk_in_endpoint[MAX_NUM_PORTS];
	struct usb_endpoint_descriptor *bulk_out_endpoint[MAX_NUM_PORTS];

	int i;
	int num_interrupt_in = 0;
	int num_interrupt_out = 0;
	int num_bulk_in = 0;
	int num_bulk_out = 0;


	printk("[%s] \n",__func__);

        for( i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (usb_endpoint_is_bulk_in(endpoint)) {
			/* we found a bulk in endpoint */
			dev_dbg(ddev, "found bulk in on endpoint %d\n", i);
			if (num_bulk_in < MAX_NUM_PORTS) {
				bulk_in_endpoint[num_bulk_in] = endpoint;
				++num_bulk_in;
			}
		}

		if (usb_endpoint_is_bulk_out(endpoint)) {
			/* we found a bulk out endpoint */
			dev_dbg(ddev, "found bulk out on endpoint %d\n", i);
			if (num_bulk_out < MAX_NUM_PORTS) {
				bulk_out_endpoint[num_bulk_out] = endpoint;
				++num_bulk_out;
			}
		}

		if (usb_endpoint_is_int_in(endpoint)) {
			/* we found a interrupt in endpoint */
			dev_dbg(ddev, "found interrupt in on endpoint %d\n", i);
			if (num_interrupt_in < MAX_NUM_PORTS) {
				interrupt_in_endpoint[num_interrupt_in] =
						endpoint;
				++num_interrupt_in;
			}
		}

		if (usb_endpoint_is_int_out(endpoint)) {
			/* we found an interrupt out endpoint */
			dev_dbg(ddev, "found interrupt out on endpoint %d\n", i);
			if (num_interrupt_out < MAX_NUM_PORTS) {
				interrupt_out_endpoint[num_interrupt_out] =
						endpoint;
				++num_interrupt_out;
			}
		}
	}


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
