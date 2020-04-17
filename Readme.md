```bash

(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ source /opt/axis/acapsdk/3.00.1/cortexa9hf-neon/environment-setup-cortexa9hf-neon-poky-linux-gnueabi

(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ create-package.sh
(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ eap-install.sh install
(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ eap-install.sh start
starting helloworld
Package started
to stop your application type
  eap-install.sh stop

(base) vivek@VIVEK-PC:/mnt/d/WindowsSubsytemLinux/March2020/hello_world$ curl -u root:pass --digest --noproxy "*" http://192.168.1.152/axis-cgi/systemlog.cgi?appname=helloworld

----- Contents of SYSTEM_LOG for 'helloworld' -----


$ sudo apt-get install libprotobuf-c0-dev protobuf-c-compiler
```


## Using cross and docker
```bat


> cargo install cross
 
> cross test --target armv7-unknown-linux-gnueabihf

> cross build --target=mips64-unknown-linux-gnuabi64

> cp .\target\armv7-unknown-linux-gnueabihf\debug\websocket_new ..\..\


```
