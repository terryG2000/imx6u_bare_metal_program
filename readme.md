# 打包镜像方法
## 正点原子
```shell
 ./imxdownload <.bin file> <SD Card>
```
   

## 百问
-e  用户程序链接地址
```shell
./tools/mkimage -n ./tools/imximage.cfg.cfgtmp -T imximage -e 0x80100000 -d led.bin led.imx
```
 