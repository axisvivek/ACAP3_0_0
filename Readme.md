```bash

(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ source /opt/axis/acapsdk/3.00.0/cortexa9hf-neon/environment-setup-cortexa9hf-neon-poky-linux-gnueabi

(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ create-package.sh
makearm-poky-linux-gnueabi-gcc  -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a9 --sysroot=/opt/axis/acapsdk/3.00.0/cortexa9hf-neon/sysroots/cortexa9hf-neon-poky-linux-gnueabi  -O2 -pipe -g -feliminate-unused-debug-types    -c -o hello_world.o hello_world.c
arm-poky-linux-gnueabi-gcc  -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a9 --sysroot=/opt/axis/acapsdk/3.00.0/cortexa9hf-neon/sysroots/cortexa9hf-neon-poky-linux-gnueabi hello_world.o -o helloworld
eap-create.sh
No package.conf file found
Created package.conf using default values... ok
Reading local package.conf... ok
Package architecture: cortexa9hf-neon
Validating Package config...

[Error] * PACKAGENAME cannot be empty
We need to fix package.conf Please answer the following questions:

* PACKAGENAME cannot be empty
PACKAGENAME: Package name or description [] hello_world
checking APPTYPE 'armv7hf'
* APPNAME cannot be empty
APPNAME: Name of application executable [] helloworld
package.conf created.
Info: Created an empty param.conf
Saving Package config: 'package.conf'...ok
Creating Package: 'hello_world_1_0_0_armv7hf.eap'... ok
Copying LICENSE file... ok

To install and run the package, you can use a browser and surf to the following page,
(replace axis_device_ip with the IP number of your Axis video product)

http://axis_device_ip/#settings/apps

Or simply use the script and type
eap-install.sh install

(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ eap-install.sh installTarget IP address []: 192.168.1.152
Target root password []: pass
installing hello_world_1_0_0_armv7hf.eap
Installation succeded
to start your application type
  eap-install.sh start
(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ eap-install.sh start
starting helloworld
Package started
to stop your application type
  eap-install.sh stop

(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ curl -u root:pass --digest --noproxy "*" http://192.168.1.152/axis-cgi/systemlog.cgi?appname=helloworld

----- Contents of SYSTEM_LOG for 'helloworld' -----


2020-02-05T13:42:05.156+05:30 axis-accc8ec54674 [ INFO    ] helloworld[0]: starting helloworld
2020-02-05T13:42:05.264+05:30 axis-accc8ec54674 [ INFO    ] helloworld[30353]: Hello, World!
(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ -u root:pass --digest --noproxy "*"-u root:pass --digest --noproxy "*"-u root:pass --digest --noproxy "*"-u root:pass --digest --noproxy "*"


(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ curl -u root:pass -i --digest --noproxy "*" http://192.168.1.152/axis-cgi/param.cgi?action=list&group=Properties.EmbeddedDevelopment.EmbeddedDevelopment


```