#!/bin/bash
bear -- make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean
bear -- make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- imx_atk_mini_emmc_defconfig
bear -- make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
bear -- make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- all -j16

rm ~/OSD_share/image/zImage
cp arch/arm/boot/zImage ~/OSD_share/image
rm ~/OSD_share/image/imx6ull-atk-mini-emmc.dtb
cp arch/arm/boot/dts/imx6ull-atk-mini-emmc.dtb ~/OSD_share/image