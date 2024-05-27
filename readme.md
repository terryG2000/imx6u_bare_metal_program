# 打包镜像方法
## 正点原子
```shell
 ./imxdownload <.bin file> <SD Card>
```
   

## 百问
无法使用这个打包程序 打包正点原子板卡的程序
-e  用户程序链接地址
```shell
./tools/mkimage -n ./tools/imximage.cfg.cfgtmp -T imximage -e 0x80100000 -d led.bin led.imx
dd if=/dev/zero of=1k.bin bs=1024 count=1 # 创建一个1k 的文件
cat 1k.bin relocate.imx > relocate.img # 将头部1k  和镜像烧写到relocate镜像中
dd if=./relocate.img  of=/dev/sdc bs=1024 count=1
```

 