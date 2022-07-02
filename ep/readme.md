# EP 才是usb 读写的关键


	struct usb_host_endpoint {
		struct usb_endpoint_descriptor		desc;
		struct usb_ss_ep_comp_descriptor	ss_ep_comp;
		struct list_head		urb_list;
		void				*hcpriv;
		struct ep_device		*ep_dev;	/* For sysfs info */

		unsigned char *extra;   /* Extra descriptors */
		int extralen;
		int enabled;
		int streams;
	};

	
	struct usb_endpoint_descriptor {
		__u8  bLength;
		__u8  bDescriptorType;

		__u8  bEndpointAddress;
		__u8  bmAttributes;
		__le16 wMaxPacketSize;
		__u8  bInterval;

		/* NOTE:  these two are _only_ in audio endpoints. */
		/* use USB_DT_ENDPOINT*_SIZE in bLength, not sizeof. */
		__u8  bRefresh;
		__u8  bSynchAddress;
	} __attribute__ ((packed));

驱动里什么时候


一个设备最多可以包含16个端点，每个端点的地址为0-15


端点0既可以给主机发送数据，也可以接收主机发送过来的数据，而其它端点均为单向。


除了端点0，其余的端点在设备配置之前不能与主机通信，只有向主机报告这些端点的特性并被确认后才能被激活。


 端点0，是设备的默认控制端点，在设备上电后就存在并可以使用，在Set Config之前所有的传输都是通过端点0传输的。


	·端点的总线访问频率要求
   	·端点的总线延迟要求
   	·端点的带宽要求
   	·端点的端点号
   	·对错误处理的要求
   	·端点能接收或发送的包的最大长度
   	·端点的传送类型
   	·端点与主机的数据传送方向

Hub 为什么只有in端点，没有out?


## pipe

数据缓存区

USB设备各各端点之间的数据传输连接

管道与USB设备中的端点逐个对应，并且各个管道的数据传输是相互独立的。


pipe 格式

- stream
- message


