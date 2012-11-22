/*-------------------------------------------------------

* Register setting for OmniVision CMOS Image Sensor
*
* Copyright:  (C) Copyright 2010 Marvell International Ltd.
*				Qing Xu <qingx@marvell.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.

-------------------------------------------------------*/

struct regval_list {
	u8 reg_num;
	unsigned char value;
};

static struct regval_list ov7690_default[] = {
	/* 320 x 240 */
	/*@@ OV5642_Br_ov7690_vga_yuv_1lane*/
	/*;OV7690 vga_raw*/

	{0x12, 0x80},
	{0x0c, 0x16},
	{0x48, 0x42},
	{0x41, 0x43},
	{0x81, 0xff},
	{0x21, 0x44},
	{0x16, 0x03},
	{0x39, 0x80},
	{0x12, 0x01},
	{0x82, 0x00},
	{0xd0, 0x48},
	{0x80, 0x7f},
	{0x3e, 0x20},
	{0x22, 0x00},
	{0x17, 0x69},
	{0x18, 0xa4},
	{0x19, 0x0c},
	{0x1a, 0xf6},
	/*VGA*/

	{0xc8, 0x02},
	{0xc9, 0x80},
	{0xca, 0x01},
	{0xcb, 0xe0},
	{0xcc, 0x02},
	{0xcd, 0x80},
	{0xce, 0x01},
	{0xcf, 0xe0},

	/*;;QVGA*/
	/*
	{0xc8, 0x02},
	{0xc9, 0x80},
	{0xca, 0x01},
	{0xcb, 0xe0},
	{0xcc, 0x01},
	{0xcd, 0x40},
	{0xce, 0x00},
	{0xcf, 0xf0},
	*/

	{0x85, 0x90},
	{0x86, 0x00},
	{0x87, 0x00},
	{0x88, 0x10},
	{0x89, 0x30},
	{0x8a, 0x29},
	{0x8b, 0x26},
	{0xbb, 0x80},
	{0xbc, 0x62},
	{0xbd, 0x1e},
	{0xbe, 0x26},
	{0xbf, 0x7b},
	{0xc0, 0xac},
	{0xc1, 0x1e},
	{0xb7, 0x0c},
	{0xb8, 0x04},
	{0xb9, 0x00},
	{0xba, 0x04},
	{0x5a, 0x14},
	{0x5b, 0xa2},
	{0x5c, 0x70},
	{0x5d, 0x20},
	{0x24, 0x38},
	{0x25, 0x30},
	{0x26, 0x71},
	{0xa3, 0x0b},
	{0xa4, 0x15},
	{0xa5, 0x2a},
	{0xa6, 0x51},
	{0xa7, 0x63},
	{0xa8, 0x74},
	{0xa9, 0x83},
	{0xaa, 0x91},
	{0xab, 0x9e},
	{0xac, 0xaa},
	{0xad, 0xbe},
	{0xae, 0xce},
	{0xaf, 0xe5},
	{0xb0, 0xf3},
	{0xb1, 0xfb},
	{0xb2, 0x06},
	{0x8c, 0x5d},
	{0x8d, 0x11},
	{0x8e, 0x12},
	{0x8f, 0x11},
	{0x90, 0x50},
	{0x91, 0x22},
	{0x92, 0xd1},
	{0x93, 0xa7},
	{0x94, 0x23},
	{0x95, 0x3b},
	{0x96, 0xff},
	{0x97, 0x00},
	{0x98, 0x4a},
	{0x99, 0x46},
	{0x9a, 0x3d},
	{0x9b, 0x3a},
	{0x9c, 0xf0},
	{0x9d, 0xf0},
	{0x9e, 0xf0},
	{0x9f, 0xff},
	{0xa0, 0x56},
	{0xa1, 0x55},
	{0xa2, 0x13},
	{0x14, 0x20},
	{0x13, 0xf7},
	{0x11, 0x01},
	{0xFF, 0xFF}
};

static struct regval_list ov7690_fmt_yuv422[] = {

	{0xFF, 0xFF}
};

#if 0/* TODO:*/
static struct regval_list ov7690_res_qcif[] = {
	/* 176 x 144 */
	{0xc8, 0x02},
	{0xc9, 0x80},
	{0xca, 0x01},
	{0xcb, 0xe0},
	{0xcc, 0x00},
	{0xcd, 0xB0},
	{0xce, 0x00},
	{0xcf, 0x90},

	{0xFF, 0xFF}
};
static struct regval_list ov7690_res_cif[] = {
	/* 352 x 288 */
	{0xc8, 0x02},
	{0xc9, 0x80},
	{0xca, 0x01},
	{0xcb, 0xe0},
	{0xcc, 0x01},
	{0xcd, 0x60},
	{0xce, 0x01},
	{0xcf, 0x20},

	{0xFF, 0xFF}
};
#endif

static struct regval_list ov7690_res_qvga[] = {
	/* 320 x 240 */
	{0xc8, 0x02},
	{0xc9, 0x80},
	{0xca, 0x01},
	{0xcb, 0xe0},
	{0xcc, 0x01},
	{0xcd, 0x40},
	{0xce, 0x00},
	{0xcf, 0xf0},

	{0xFF, 0xFF}
};

static struct regval_list ov7690_res_qvga_v[] = {

	/* 240 x 320 */
	{0xc8, 0x02},
	{0xc9, 0x80},
	{0xca, 0x01},
	{0xcb, 0xe0},
	{0xcc, 0x00},
	{0xcd, 0xf0},
	{0xce, 0x01},
	{0xcf, 0x40},

	{0xFF, 0xFF}
};
#if 0/* TODO: */
static struct regval_list ov7690_res_vga[] = {
	/* 640 x 480 */

	{0xc8, 0x02},
	{0xc9, 0x80},
	{0xca, 0x01},
	{0xcb, 0xe0},
	{0xcc, 0x02},
	{0xcd, 0x80},
	{0xce, 0x01},
	{0xcf, 0xe0},

	{0xFF, 0xFF}
};
#endif