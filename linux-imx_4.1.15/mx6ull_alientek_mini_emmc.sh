#!/bin/sh
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- imx_atk_mini_emmc_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- all -j16

rm ~/OSD_share/zImage
cp arch/arm/boot/zImage ~/OSD_share
rm ~/OSD_share/imx6ull-atk-mini-emmc.dtb
cp arch/arm/boot/dts/imx6ull-atk-mini-emmc.dtb ~/OSD_share