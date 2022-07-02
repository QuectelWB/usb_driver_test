# 如何驱动里屏蔽某个interface

# driver_info 里带上一些模块信息

# bind 接口是怎么被调用到的

WUSB: wireless USB

一些USB硬盘不能被被识别，禁用uas 方法

usb stat urb: status -32

solution:

	echo "options usb-storage quirks=idVendor:idProduct:u" | sudo tee /etc/modprobe.d/anyname.conf
	sudo update-initramfs -u
	
	
	gemfield@ai01:/etc/modprobe.d$ cat quirks.conf 
	options usb-storage quirks=0x174c:0x2362:u


