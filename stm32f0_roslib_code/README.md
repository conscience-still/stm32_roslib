## stm32f0_rosserial bsp for ros node communication

![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL3N6X21tYml6X3BuZy91Y2RZbUdYTGlhOWljVThpYkVyTzFNVlEwT3pocmliaFh3VGxyM2dxU29pYWVDa1VqeW5Ca21vWFFncUdtVjVWSVUzNFZEWWN2ZGpTZ3lmcU8wbEtIeUpTQ3R3LzY0MA?x-oss-process=image/format,png,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x5bjYzMTU3OTc0MQ==,size_16,color_FFFFFF,t_70)

作者：良知犹存

转载授权以及围观：欢迎添加微信公众号：羽林君

***



第一步：

解压 toolchain压缩包

第二步：

```
export  PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/home/lyn//M0/gcc-arm-none-eabi-4_9-2015q3/bin
```





其中：/home/lyn//M0/gcc-arm-none-eabi-4_9-2015q3/bin 是我解压toolchain的目录，大家可以按照自己解压的实际目录进行配置

第三步：

make



第四步：

把编译生成的main.bin 文件下载到板子中



最后：

如有不懂可以看我写的这篇《[STM32通过rosserial接入ROS通讯开发](https://blog.csdn.net/lyn631579741/article/details/112727595)》文章，也可以关注我公账号后台回复 **联系我**，与我微信交流。

