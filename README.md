##BBB_ubuntu_DD:
**Device drivers for BeagleBoneBlack on ubuntu**

###SUMMARY:
This repo is for tracking the progress of development of device drviers on beagle bone black. We have implemented following drivers :

1. Hello world: This driver module is basic driver to describe the functionality of __init and __exit functions in kernel. We are also using module_param function to pass runtime parameter to the module so that the module can be flexible.

2. drivers/ioctl: This driver represent the ioctl functionality of char devices. We are first allocating char device number (MAJAOR and MINOR) for our driver. Next we are associating the driver to file operations functions such as open,close and ioctl. We are creating a char device class for our driver which is then associated with a device node using dev_create function. We have created a query app which will interact with our driver and check the functionality of it.

3. drivers/usb : This driver describe how basic usb probe and disconnect functions of driver work. First , we register the usb driver with the usb device using its vendor and product id. Later on connecting the device, this driver is loaded and probe function is called. In probe function, we have printed the device info such as its interfaces, its endpoints info , description etc.. Similarly, when it is removed or ejected , pen_disconnect function is called.

4. **drivers/mouse** : On the basis of above mentioned drivers , we have created a custom mouse driver for microsoft mouse. The functionality of this mouse is whenever we press right clicked and released , it prints some message along with x shift and y shift with respect to previous position. We are communicating with the device using urb's in interrupt mode. 

###Current goals:
1. Setup the router for assigning a static ip to the board so that it can be configured from any where in the world. DONE
2. Create a script and cron job which will peridically check if the public ip is changed or not. If it is changed then it will send a mail to raymogg account. DONE
3. Build basic char drivers and drivers with ioctl functionality . DONE
4. Build usb mouse driver for Beesama. DONE
5. Build tty driver on the board and check its functionality. PENDING 
6. Build usb-serial driver on the board and check its functionality. PENDING

###PROCESS:
1. Installed vim ,ssmtp and git inside the board.
2. Need to edit ssmtp config file in /etc/ssmtp/ssmtp.conf for setting up the system.
3. Set cronjob for sending the change in public ip to raymogg. Command used crontab -e . Inside that file add file name.
4. Currently installed cross compiler for arm system from this site https://eewiki.net/display/linuxonarm/BeagleBone+Black#BeagleBoneBlack-ARMCrossCompiler:GCC
5. Export variable CC with the location of the cross compiler.
6. Compile driver

