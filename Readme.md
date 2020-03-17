```bash

(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ source /opt/axis/acapsdk/3.00.0/cortexa9hf-neon/environment-setup-cortexa9hf-neon-poky-linux-gnueabi

(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ create-package.sh
(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ eap-install.sh install
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

$ sudo apt-get install libprotobuf-c0-dev protobuf-c-compiler
```