// SPDX-License-Identifier: GPL-2.0
/*
 * Intel Lakefield PCH pinctrl/GPIO driver
 *
 * Copyright (C) 2020, Intel Corporation
 * Author: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
 */

#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include <linux/pinctrl/pinctrl.h>

#include "pinctrl-intel.h"

#define LKF_PAD_OWN	0x020
#define LKF_PADCFGLOCK	0x070
#define LKF_HOSTSW_OWN	0x090
#define LKF_GPI_IS	0x100
#define LKF_GPI_IE	0x110

#define LKF_GPP(r, s, e, g)				\
	{						\
		.reg_num = (r),				\
		.base = (s),				\
		.size = ((e) - (s) + 1),		\
		.gpio_base = (g),			\
	}

#define LKF_COMMUNITY(b, s, e, g)			\
	INTEL_COMMUNITY_GPPS(b, s, e, g, LKF)

/* Lakefield */
static const struct pinctrl_pin_desc lkf_pins[] = {
	/* EAST */
	PINCTRL_PIN(0, "MDSI_A_TE0"),
	PINCTRL_PIN(1, "MDSI_A_TE1"),
	PINCTRL_PIN(2, "PANEL0_AVDD_EN"),
	PINCTRL_PIN(3, "PANEL0_BKLTEN"),
	PINCTRL_PIN(4, "PANEL0_BKLTCTL"),
	PINCTRL_PIN(5, "PANEL1_AVDD_EN"),
	PINCTRL_PIN(6, "PANEL1_BKLTEN"),
	PINCTRL_PIN(7, "PANEL1_BKLTCTL"),
	PINCTRL_PIN(8, "THC0_SPI1_IO_0"),
	PINCTRL_PIN(9, "THC0_SPI1_IO_1"),
	PINCTRL_PIN(10, "THC0_SPI1_IO_2"),
	PINCTRL_PIN(11, "THC0_SPI1_IO_3"),
	PINCTRL_PIN(12, "THC0_SPI1_CSB"),
	PINCTRL_PIN(13, "THC0_SPI1_CLK"),
	PINCTRL_PIN(14, "THC0_SPI1_RESETB"),
	PINCTRL_PIN(15, "THC0_SPI1_CLK_FB"),
	PINCTRL_PIN(16, "SPI_TOUCH_CLK_FB"),
	PINCTRL_PIN(17, "THC1_SPI2_IO_0"),
	PINCTRL_PIN(18, "THC1_SPI2_IO_1"),
	PINCTRL_PIN(19, "THC1_SPI2_IO_2"),
	PINCTRL_PIN(20, "THC1_SPI2_IO_3"),
	PINCTRL_PIN(21, "THC1_SPI2_CSB"),
	PINCTRL_PIN(22, "THC1_SPI2_CLK"),
	PINCTRL_PIN(23, "THC1_SPI2_RESETB"),
	PINCTRL_PIN(24, "THC1_SPI2_CLK_FB"),
	PINCTRL_PIN(25, "eSPI_IO_0"),
	PINCTRL_PIN(26, "eSPI_IO_1"),
	PINCTRL_PIN(27, "eSPI_IO_2"),
	PINCTRL_PIN(28, "eSPI_IO_3"),
	PINCTRL_PIN(29, "eSPI_CSB"),
	PINCTRL_PIN(30, "eSPI_RESETB"),
	PINCTRL_PIN(31, "eSPI_CLK"),
	PINCTRL_PIN(32, "eSPI_CLK_FB"),
	PINCTRL_PIN(33, "FAST_SPI0_IO_0"),
	PINCTRL_PIN(34, "FAST_SPI0_IO_1"),
	PINCTRL_PIN(35, "FAST_SPI0_IO_2"),
	PINCTRL_PIN(36, "FAST_SPI0_IO_3"),
	PINCTRL_PIN(37, "FAST_SPI0_CSB_0"),
	PINCTRL_PIN(38, "FAST_SPI0_CSB_2"),
	PINCTRL_PIN(39, "FAST_SPI0_CLK"),
	PINCTRL_PIN(40, "FAST_SPI_CLK_FB"),
	PINCTRL_PIN(41, "FAST_SPI0_CSB_1"),
	PINCTRL_PIN(42, "ISH_GP_12"),
	PINCTRL_PIN(43, "THC0_SPI1_INTB"),
	PINCTRL_PIN(44, "THC1_SPI2_INTB"),
	PINCTRL_PIN(45, "PANEL0_AVEE_EN"),
	PINCTRL_PIN(46, "PANEL0_VIO_EN"),
	PINCTRL_PIN(47, "PANEL1_AVEE_EN"),
	PINCTRL_PIN(48, "PANEL1_VIO_EN"),
	PINCTRL_PIN(49, "PANEL0_RESET"),
	PINCTRL_PIN(50, "PANEL1_RESET"),
	PINCTRL_PIN(51, "ISH_GP_15"),
	PINCTRL_PIN(52, "ISH_GP_16"),
	PINCTRL_PIN(53, "ISH_GP_17"),
	PINCTRL_PIN(54, "ISH_GP_18"),
	PINCTRL_PIN(55, "ISH_GP_19"),
	PINCTRL_PIN(56, "ISH_GP_20"),
	PINCTRL_PIN(57, "ISH_GP_21"),
	PINCTRL_PIN(58, "ISH_GP_22"),
	PINCTRL_PIN(59, "ISH_GP_23"),
	/* NORTHWEST */
	PINCTRL_PIN(60, "MCSI_GPIO_0"),
	PINCTRL_PIN(61, "MCSI_GPIO_1"),
	PINCTRL_PIN(62, "MCSI_GPIO_2"),
	PINCTRL_PIN(63, "MCSI_GPIO_3"),
	PINCTRL_PIN(64, "LPSS_I2C0_SDA"),
	PINCTRL_PIN(65, "LPSS_I2C0_SCL"),
	PINCTRL_PIN(66, "LPSS_I2C1_SDA"),
	PINCTRL_PIN(67, "LPSS_I2C1_SCL"),
	PINCTRL_PIN(68, "LPSS_I2C2_SDA"),
	PINCTRL_PIN(69, "LPSS_I2C2_SCL"),
	PINCTRL_PIN(70, "LPSS_I2C3_SDA"),
	PINCTRL_PIN(71, "LPSS_I2C3_SCL"),
	PINCTRL_PIN(72, "LPSS_I2C4_SDA"),
	PINCTRL_PIN(73, "LPSS_I2C4_SCL"),
	PINCTRL_PIN(74, "LPSS_I2C5_SDA"),
	PINCTRL_PIN(75, "LPSS_I2C5_SCL"),
	PINCTRL_PIN(76, "LPSS_I3C0_SDA"),
	PINCTRL_PIN(77, "LPSS_I3C0_SCL"),
	PINCTRL_PIN(78, "LPSS_I3C0_SCL_FB"),
	PINCTRL_PIN(79, "LPSS_I3C1_SDA"),
	PINCTRL_PIN(80, "LPSS_I3C1_SCL"),
	PINCTRL_PIN(81, "LPSS_I3C1_SCL_FB"),
	PINCTRL_PIN(82, "ISH_I2C0_SDA"),
	PINCTRL_PIN(83, "ISH_I2C0_SCL"),
	PINCTRL_PIN(84, "ISH_I2C1_SCL"),
	PINCTRL_PIN(85, "ISH_I2C1_SDA"),
	PINCTRL_PIN(86, "DBG_PMODE"),
	PINCTRL_PIN(87, "BJTAG_TCK"),
	PINCTRL_PIN(88, "BJTAG_TDI"),
	PINCTRL_PIN(89, "BJTAGX"),
	PINCTRL_PIN(90, "BPREQ_B"),
	PINCTRL_PIN(91, "BJTAG_TMS"),
	PINCTRL_PIN(92, "BPRDY_B"),
	PINCTRL_PIN(93, "BJTAG_TDO"),
	PINCTRL_PIN(94, "BJTAG_TRST_B_0"),
	PINCTRL_PIN(95, "ISH_I3C0_SDA"),
	PINCTRL_PIN(96, "ISH_I3C0_SCL"),
	PINCTRL_PIN(97, "ISH_I3C0_SCL_FB"),
	PINCTRL_PIN(98, "AVS_I2S_BCLK_0"),
	PINCTRL_PIN(99, "AVS_I2S_MCLK_0"),
	PINCTRL_PIN(100, "AVS_I2S_SFRM_0"),
	PINCTRL_PIN(101, "AVS_I2S_RXD_0"),
	PINCTRL_PIN(102, "AVS_I2S_TXD_0"),
	PINCTRL_PIN(103, "AVS_I2S_BCLK_1"),
	PINCTRL_PIN(104, "AVS_I2S_SFRM_1"),
	PINCTRL_PIN(105, "AVS_I2S_RXD_1"),
	PINCTRL_PIN(106, "AVS_I2S_TXD_1"),
	PINCTRL_PIN(107, "AVS_I2S_BCLK_2"),
	PINCTRL_PIN(108, "AVS_I2S_SFRM_2"),
	PINCTRL_PIN(109, "AVS_I2S_RXD_2"),
	PINCTRL_PIN(110, "AVS_I2S_TXD_2"),
	PINCTRL_PIN(111, "AVS_I2S_BCLK_3"),
	PINCTRL_PIN(112, "AVS_I2S_SFRM_3"),
	PINCTRL_PIN(113, "AVS_I2S_RXD_3"),
	PINCTRL_PIN(114, "AVS_I2S_TXD_3"),
	PINCTRL_PIN(115, "AVS_I2S_BCLK_4"),
	PINCTRL_PIN(116, "AVS_I2S_SFRM_4"),
	PINCTRL_PIN(117, "AVS_I2S_RXD_4"),
	PINCTRL_PIN(118, "AVS_I2S_TXD_4"),
	PINCTRL_PIN(119, "AVS_I2S_SFRM_5"),
	PINCTRL_PIN(120, "AVS_I2S_RXD_5"),
	PINCTRL_PIN(121, "AVS_I2S_TXD_5"),
	PINCTRL_PIN(122, "AVS_I2S_BCLK_5"),
	PINCTRL_PIN(123, "AVS_SNDW_CLK_0"),
	PINCTRL_PIN(124, "AVS_SNDW_DATA_0"),
	PINCTRL_PIN(125, "AVS_SNDW_CLK_1"),
	PINCTRL_PIN(126, "AVS_SNDW_DATA_1"),
	PINCTRL_PIN(127, "AVS_SNDW_CLK_2"),
	PINCTRL_PIN(128, "AVS_SNDW_DATA_2"),
	PINCTRL_PIN(129, "AVS_SNDW_CLK_3"),
	PINCTRL_PIN(130, "AVS_SNDW_DATA_3"),
	PINCTRL_PIN(131, "VISA_PTI_CH0_D0_internal"),
	PINCTRL_PIN(132, "VISA_PTI_CH0_D1_internal"),
	PINCTRL_PIN(133, "VISA_PTI_CH0_D2_internal"),
	PINCTRL_PIN(134, "VISA_PTI_CH0_D3_internal"),
	PINCTRL_PIN(135, "VISA_PTI_CH0_D4_internal"),
	PINCTRL_PIN(136, "VISA_PTI_CH0_D5_internal"),
	PINCTRL_PIN(137, "VISA_PTI_CH0_D6_internal"),
	PINCTRL_PIN(138, "VISA_PTI_CH0_D7_internal"),
	PINCTRL_PIN(139, "VISA_PTI_CH0_CLK_internal"),
	PINCTRL_PIN(140, "VISA_PTI_CH1_D0_internal"),
	PINCTRL_PIN(141, "VISA_PTI_CH1_D1_internal"),
	PINCTRL_PIN(142, "VISA_PTI_CH1_D2_internal"),
	PINCTRL_PIN(143, "VISA_PTI_CH1_D3_internal"),
	PINCTRL_PIN(144, "VISA_PTI_CH1_D4_internal"),
	PINCTRL_PIN(145, "VISA_PTI_CH1_D5_internal"),
	PINCTRL_PIN(146, "VISA_PTI_CH1_D6_internal"),
	PINCTRL_PIN(147, "VISA_PTI_CH1_D7_internal"),
	PINCTRL_PIN(148, "VISA_PTI_CH1_CLK_internal"),
	/* WEST */
	PINCTRL_PIN(149, "LPSS_UART0_TXD"),
	PINCTRL_PIN(150, "LPSS_UART0_RXD"),
	PINCTRL_PIN(151, "LPSS_UART0_RTS_B"),
	PINCTRL_PIN(152, "LPSS_UART0_CTS_B"),
	PINCTRL_PIN(153, "LPSS_UART1_RXD"),
	PINCTRL_PIN(154, "LPSS_UART1_TXD"),
	PINCTRL_PIN(155, "LPSS_UART1_RTS_B"),
	PINCTRL_PIN(156, "LPSS_UART1_CTS_B"),
	PINCTRL_PIN(157, "ISH_UART0_RXD"),
	PINCTRL_PIN(158, "ISH_UART0_TXD"),
	PINCTRL_PIN(159, "ISH_UART0_RTSB"),
	PINCTRL_PIN(160, "ISH_UART0_CTSB"),
	PINCTRL_PIN(161, "LPSS_SSP_0_CLK"),
	PINCTRL_PIN(162, "LPSS_SSP_0_CLK_FB"),
	PINCTRL_PIN(163, "LPSS_SSP_0_FS0"),
	PINCTRL_PIN(164, "LPSS_SSP_0_FS1"),
	PINCTRL_PIN(165, "LPSS_SSP_0_RXD"),
	PINCTRL_PIN(166, "LPSS_SSP_0_TXD"),
	PINCTRL_PIN(167, "ISH_UART1_RXD"),
	PINCTRL_PIN(168, "ISH_UART1_TXD"),
	PINCTRL_PIN(169, "ISH_UART1_RTSB"),
	PINCTRL_PIN(170, "ISH_UART1_CTSB"),
	PINCTRL_PIN(171, "LPSS_SSP_1_FS0"),
	PINCTRL_PIN(172, "LPSS_SSP_1_FS1"),
	PINCTRL_PIN(173, "LPSS_SSP_1_CLK"),
	PINCTRL_PIN(174, "LPSS_SSP_1_CLK_FB"),
	PINCTRL_PIN(175, "LPSS_SSP_1_RXD"),
	PINCTRL_PIN(176, "LPSS_SSP_1_TXD"),
	PINCTRL_PIN(177, "LPSS_SSP_2_CLK"),
	PINCTRL_PIN(178, "LPSS_SSP_2_CLK_FB"),
	PINCTRL_PIN(179, "LPSS_SSP_2_FS0"),
	PINCTRL_PIN(180, "LPSS_SSP_2_FS1"),
	PINCTRL_PIN(181, "LPSS_SSP_2_RXD"),
	PINCTRL_PIN(182, "LPSS_SSP_2_TXD"),
	PINCTRL_PIN(183, "ISH_SPI0_CSB0"),
	PINCTRL_PIN(184, "ISH_SPI0_CSB1"),
	PINCTRL_PIN(185, "ISH_SPI0_CLK"),
	PINCTRL_PIN(186, "ISH_SPI0_MISO"),
	PINCTRL_PIN(187, "ISH_SPI0_MOSI"),
	PINCTRL_PIN(188, "ISH_GP_0"),
	PINCTRL_PIN(189, "ISH_GP_1"),
	PINCTRL_PIN(190, "ISH_GP_2"),
	PINCTRL_PIN(191, "ISH_GP_13"),
	PINCTRL_PIN(192, "ISH_GP_3"),
	PINCTRL_PIN(193, "ISH_GP_4"),
	PINCTRL_PIN(194, "ISH_GP_5"),
	PINCTRL_PIN(195, "ISH_GP_6"),
	PINCTRL_PIN(196, "ISH_GP_7"),
	PINCTRL_PIN(197, "ISH_GP_8"),
	PINCTRL_PIN(198, "ISH_GP_9"),
	PINCTRL_PIN(199, "ISH_GP_10"),
	PINCTRL_PIN(200, "ISH_GP_11"),
	PINCTRL_PIN(201, "ISH_GP_14"),
	PINCTRL_PIN(202, "ISH_GP_15"),
	PINCTRL_PIN(203, "ISH_GP_22"),
	PINCTRL_PIN(204, "ISH_GP_12"),
	PINCTRL_PIN(205, "ISH_GP_30_USB_OC"),
	PINCTRL_PIN(206, "LPDDRx_RESET0_n"),
	PINCTRL_PIN(207, "UFS_RESET_B"),
	PINCTRL_PIN(208, "UFS_REFCLK0"),
	PINCTRL_PIN(209, "EMMC_SD_CLK"),
	PINCTRL_PIN(210, "EMMC_SD_D0"),
	PINCTRL_PIN(211, "EMMC_SD_D1"),
	PINCTRL_PIN(212, "EMMC_SD_D2"),
	PINCTRL_PIN(213, "EMMC_SD_D3"),
	PINCTRL_PIN(214, "EMMC_D4"),
	PINCTRL_PIN(215, "EMMC_D5"),
	PINCTRL_PIN(216, "EMMC_D6"),
	PINCTRL_PIN(217, "EMMC_D7"),
	PINCTRL_PIN(218, "EMMC_SD_CMD"),
	PINCTRL_PIN(219, "EMMC_RCLK"),
	PINCTRL_PIN(220, "SDCARD_CLK_FB"),
	PINCTRL_PIN(221, "SD_Virtual_GPIO"),
	PINCTRL_PIN(222, "OSC_CLK_OUT_NFC"),
	PINCTRL_PIN(223, "OSC_CLK_OUT_CAM_0"),
	PINCTRL_PIN(224, "OSC_CLK_OUT_CAM_1"),
	PINCTRL_PIN(225, "OSC_CLK_OUT_CAM_2"),
	PINCTRL_PIN(226, "OSC_CLK_OUT_CAM_3"),
	PINCTRL_PIN(227, "PCIe_LINKDOWN"),
	PINCTRL_PIN(228, "NFC_CLK_REQ"),
	PINCTRL_PIN(229, "PCIE_CLKREQ_N_DEV2"),
	PINCTRL_PIN(230, "PCIE_CLKREQ_N_DEV3"),
	PINCTRL_PIN(231, "PCIE_CLKREQ_N_DEV4"),
	PINCTRL_PIN(232, "PCIE_CLKREQ_N_DEV1"),
	PINCTRL_PIN(233, "PCIE_CLKREQ_N_DEV0"),
	PINCTRL_PIN(234, "GMBUS_1_SCL"),
	PINCTRL_PIN(235, "GMBUS_1_SDA"),
	PINCTRL_PIN(236, "GMBUS_0_SCL"),
	PINCTRL_PIN(237, "GMBUS_0_SDA"),
	/* SOUTHEAST */
	PINCTRL_PIN(238, "COMPUTE_PMIC_SVID_DATA"),
	PINCTRL_PIN(239, "COMPUTE_PMIC_SVID_CLK"),
	PINCTRL_PIN(240, "COMPUTE_PMIC_SVID_ALERT_B"),
	PINCTRL_PIN(241, "ROP_PMIC_I2C_SCL"),
	PINCTRL_PIN(242, "ROP_PMIC_I2C_SDA"),
	PINCTRL_PIN(243, "ISH_TYPEC_I2C2_SDA"),
	PINCTRL_PIN(244, "ISH_TYPEC_I2C2_SCL"),
	PINCTRL_PIN(245, "COMPUTE_PMU_PROCHOT_B"),
	PINCTRL_PIN(246, "PMU_CATERR_B"),
	PINCTRL_PIN(247, "COMPUTE_PMIC_VR_READY"),
	PINCTRL_PIN(248, "FORCE_FW_RELOAD"),
	PINCTRL_PIN(249, "ROP_PMIC_IRQ_ISH_GPIO31_TPC_ALERT_B"),
	PINCTRL_PIN(250, "ROP_PMIC_RESET_B"),
	PINCTRL_PIN(251, "ROP_PMIC_STNBY_SLP_S0_B"),
	PINCTRL_PIN(252, "ROP_PMIC_THERMTRIP_B"),
	PINCTRL_PIN(253, "MODEM_CLKREQ"),
	PINCTRL_PIN(254, "TPC0_BSSB_SBU1"),
	PINCTRL_PIN(255, "TPC0_BSSB_SBU2"),
	PINCTRL_PIN(256, "OSC_CLK_OUT_CAM_4"),
	PINCTRL_PIN(257, "HPD1"),
	PINCTRL_PIN(258, "HPD0"),
	PINCTRL_PIN(259, "PMC_TIME_SYNC_0"),
	PINCTRL_PIN(260, "PMC_TIME_SYNC_1"),
	PINCTRL_PIN(261, "OSC_CLK_OUT_CAM_5"),
	PINCTRL_PIN(262, "ISH_GP_20"),
	PINCTRL_PIN(263, "ISH_GP_16"),
	PINCTRL_PIN(264, "ISH_GP_17"),
	PINCTRL_PIN(265, "ISH_GP_18"),
	PINCTRL_PIN(266, "ISH_GP_19"),
};

static const struct intel_padgroup lkf_community0_gpps[] = {
	LKF_GPP(0, 0, 31, 0),		/* EAST_0 */
	LKF_GPP(1, 32, 59, 32),		/* EAST_1 */
};

static const struct intel_padgroup lkf_community1_gpps[] = {
	LKF_GPP(0, 60, 91, 64),		/* NORTHWEST_0 */
	LKF_GPP(1, 92, 123, 96),	/* NORTHWEST_1 */
	LKF_GPP(2, 124, 148, 128),	/* NORTHWEST_2 */
};

static const struct intel_padgroup lkf_community2_gpps[] = {
	LKF_GPP(0, 149, 180, 160),	/* WEST_0 */
	LKF_GPP(1, 181, 212, 192),	/* WEST_1 */
	LKF_GPP(2, 213, 237, 224),	/* WEST_2 */
};

static const struct intel_padgroup lkf_community3_gpps[] = {
	LKF_GPP(0, 238, 266, 256),	/* SOUTHEAST */
};

static const struct intel_community lkf_communities[] = {
	LKF_COMMUNITY(0, 0, 59, lkf_community0_gpps),		/* EAST */
	LKF_COMMUNITY(1, 60, 148, lkf_community1_gpps),		/* NORTHWEST */
	LKF_COMMUNITY(2, 149, 237, lkf_community2_gpps),	/* WEST */
	LKF_COMMUNITY(3, 238, 266, lkf_community3_gpps),	/* SOUTHEAST */
};

static const struct intel_pinctrl_soc_data lkf_soc_data = {
	.pins = lkf_pins,
	.npins = ARRAY_SIZE(lkf_pins),
	.communities = lkf_communities,
	.ncommunities = ARRAY_SIZE(lkf_communities),
};

static const struct acpi_device_id lkf_pinctrl_acpi_match[] = {
	{ "INT34C4", (kernel_ulong_t)&lkf_soc_data },
	{ }
};
MODULE_DEVICE_TABLE(acpi, lkf_pinctrl_acpi_match);

static INTEL_PINCTRL_PM_OPS(lkf_pinctrl_pm_ops);

static struct platform_driver lkf_pinctrl_driver = {
	.probe = intel_pinctrl_probe_by_hid,
	.driver = {
		.name = "lakefield-pinctrl",
		.acpi_match_table = lkf_pinctrl_acpi_match,
		.pm = &lkf_pinctrl_pm_ops,
	},
};
module_platform_driver(lkf_pinctrl_driver);

MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_DESCRIPTION("Intel Lakefield PCH pinctrl/GPIO driver");
MODULE_LICENSE("GPL v2");
