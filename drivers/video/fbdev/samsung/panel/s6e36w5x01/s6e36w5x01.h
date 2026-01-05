/*
 * linux/drivers/video/fbdev/exynos/panel/s6e36w5x01/s6e36w5x01.h
 *
 * Header file for S6E36W5X01 Dimming Driver
 *
 * Copyright (c) 2016 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __S6E36W5X01_H__
#define __S6E36W5X01_H__

#include <linux/types.h>
#include <linux/kernel.h>

#include "../panel_drv.h"
#include "../panel.h"
#include "../maptbl.h"
#include "oled_function.h"
#include "oled_common_dump.h"

#define S6E36W5X01_CELL_ID_REG		0xA9
#define S6E36W5X01_CELL_ID_OFS		0
#define S6E36W5X01_CELL_ID_LEN		11

#define S6E36W5X01_COORDINATE_REG	0xA1
#define S6E36W5X01_COORDINATE_OFS	0
#define S6E36W5X01_COORDINATE_LEN	4

#define S6E36W5X01_ID_REG		0x04
#define S6E36W5X01_ID_OFS		0
#define S6E36W5X01_ID_LEN		3

#define S6E36W5X01_OCTA_ID_REG		0xA1
#define S6E36W5X01_OCTA_ID_OFS		11
#define S6E36W5X01_OCTA_ID_LEN		20

#define S6E36W5X01_CHIP_ID_REG		0xD6
#define S6E36W5X01_CHIP_ID_OFS		0
#define S6E36W5X01_CHIP_ID_LEN		5

#define S6E36W5X01_DATE_REG		0xA1
#define S6E36W5X01_DATE_OFS		4
#define S6E36W5X01_DATE_LEN		7

#define S6E36W5X01_CODE_REG		0xD6
#define S6E36W5X01_CODE_OFS		0
#define S6E36W5X01_CODE_LEN		5

/* for panel dump */
#define S6E36W5X01_RDDPM_REG		0x0A
#define S6E36W5X01_RDDPM_OFS		0
#define S6E36W5X01_RDDPM_LEN		1

#define S6E36W5X01_RDDSM_REG		0x0E
#define S6E36W5X01_RDDSM_OFS		0
#define S6E36W5X01_RDDSM_LEN		1

#define S6E36W5X01_ERR_REG		0xE5
#define S6E36W5X01_ERR_OFS		0
#define S6E36W5X01_ERR_LEN		5

#define S6E36W5X01_ERR_FG_REG		0xEE
#define S6E36W5X01_ERR_FG_OFS		0
#define S6E36W5X01_ERR_FG_LEN		1

#define S6E36W5X01_DSI_ERR_REG		0x05
#define S6E36W5X01_DSI_ERR_OFS		0
#define S6E36W5X01_DSI_ERR_LEN		1

#define S6E36W5X01_SELF_DIAG_REG	0x0F
#define S6E36W5X01_SELF_DIAG_OFS	0
#define S6E36W5X01_SELF_DIAG_LEN	1

enum s6e36w5x01_function {
	S6E36W5X01_MAPTBL_INIT_GAMMA_MODE2_BRT,
	S6E36W5X01_MAPTBL_GETIDX_ACL_CONTROL,
	S6E36W5X01_MAPTBL_GETIDX_HBM_TRANSITION_CONTROL,
	S6E36W5X01_MAPTBL_GETIDX_ELVSS_TEMP,
	S6E36W5X01_DUMP_SHOW_ERROR_FLAG,
	S6E36W5X01_DUMP_SHOW_ERROR,
	S6E36W5X01_COND_IS_SMOOTH_DIMMING_AVAILABLE,
	MAX_S6E36W5X01_FUNCTION
};

extern struct pnobj_func s6e36w5x01_function_table[MAX_S6E36W5X01_FUNCTION];

#undef DDI_FUNC
#define DDI_FUNC(_index) (s6e36w5x01_function_table[_index])

enum {
	GAMMA_MAPTBL,
	GAMMA_MODE2_MAPTBL,
	TSET_MAPTBL,
	ACL_CONTROL_MAPTBL,
	HBM_ACL_CONTROL_MAPTBL,
	NORMAL_ACL_ONOFF_MAPTBL,
	HBM_ACL_ONOFF_MAPTBL,
	HBM_TRANSITION_MAPTBL,
	LPM_WRDISBV_MAPTBL,
	HBM_ONOFF_MAPTBL,
	ELVSS_TEMP_MAPTBL,
	VINIT_TEMP_MAPTBL,
	VCL_TEMP_MAPTBL,
	SMOOTH_DIMMING_FRAME_MAPTBL,
	MAX_MAPTBL,
};

enum {
	READ_ID,
	READ_COORDINATE,
	READ_CODE,
	READ_ELVSS,
	READ_MTP,
	READ_DATE,
	READ_OCTA_ID,
	READ_CHIP_ID,
	READ_AOR,
	READ_RDDPM,
	READ_RDDSM,
	READ_ERR,
	READ_ERR_FG,
	READ_DSI_ERR,
	READ_SELF_DIAG,
};

enum {
	RES_ID,
	RES_COORDINATE,
	RES_CODE,
	RES_ELVSS,
	RES_MTP,
	RES_DATE,
	RES_OCTA_ID,
	RES_CHIP_ID,
	/* for brightness debugging */
	RES_AOR,
	RES_RDDPM,
	RES_RDDSM,
	RES_ERR,
	RES_ERR_FG,
	RES_DSI_ERR,
	RES_SELF_DIAG,
};

static u8 S6E36W5X01_ID[S6E36W5X01_ID_LEN];
static u8 S6E36W5X01_COORDINATE[S6E36W5X01_COORDINATE_LEN];
static u8 S6E36W5X01_CODE[S6E36W5X01_CODE_LEN];
static u8 S6E36W5X01_DATE[S6E36W5X01_DATE_LEN];
static u8 S6E36W5X01_OCTA_ID[S6E36W5X01_OCTA_ID_LEN];
/* for brightness debugging */
static u8 S6E36W5X01_CHIP_ID[S6E36W5X01_CHIP_ID_LEN];
static u8 S6E36W5X01_RDDPM[S6E36W5X01_RDDPM_LEN];
static u8 S6E36W5X01_RDDSM[S6E36W5X01_RDDSM_LEN];
static u8 S6E36W5X01_ERR[S6E36W5X01_ERR_LEN];
static u8 S6E36W5X01_ERR_FG[S6E36W5X01_ERR_FG_LEN];
static u8 S6E36W5X01_DSI_ERR[S6E36W5X01_DSI_ERR_LEN];
static u8 S6E36W5X01_SELF_DIAG[S6E36W5X01_SELF_DIAG_LEN];


static struct rdinfo s6e36w5x01_rditbl[] = {
	[READ_ID] = RDINFO_INIT(id, DSI_PKT_TYPE_RD, S6E36W5X01_ID_REG, S6E36W5X01_ID_OFS, S6E36W5X01_ID_LEN),
	[READ_COORDINATE] = RDINFO_INIT(coordinate, DSI_PKT_TYPE_RD, S6E36W5X01_COORDINATE_REG, S6E36W5X01_COORDINATE_OFS, S6E36W5X01_COORDINATE_LEN),
	[READ_CODE] = RDINFO_INIT(code, DSI_PKT_TYPE_RD, S6E36W5X01_CODE_REG, S6E36W5X01_CODE_OFS, S6E36W5X01_CODE_LEN),
	[READ_DATE] = RDINFO_INIT(date, DSI_PKT_TYPE_RD, S6E36W5X01_DATE_REG, S6E36W5X01_DATE_OFS, S6E36W5X01_DATE_LEN),
	[READ_OCTA_ID] = RDINFO_INIT(octa_id, DSI_PKT_TYPE_RD, S6E36W5X01_OCTA_ID_REG, S6E36W5X01_OCTA_ID_OFS, S6E36W5X01_OCTA_ID_LEN),
	/* for brightness debugging */
	[READ_CHIP_ID] = RDINFO_INIT(chip_id, DSI_PKT_TYPE_RD, S6E36W5X01_CHIP_ID_REG, S6E36W5X01_CHIP_ID_OFS, S6E36W5X01_CHIP_ID_LEN),
	[READ_RDDPM] = RDINFO_INIT(rddpm, DSI_PKT_TYPE_RD, S6E36W5X01_RDDPM_REG, S6E36W5X01_RDDPM_OFS, S6E36W5X01_RDDPM_LEN),
	[READ_RDDSM] = RDINFO_INIT(rddsm, DSI_PKT_TYPE_RD, S6E36W5X01_RDDSM_REG, S6E36W5X01_RDDSM_OFS, S6E36W5X01_RDDSM_LEN),
	[READ_ERR] = RDINFO_INIT(err, DSI_PKT_TYPE_RD, S6E36W5X01_ERR_REG, S6E36W5X01_ERR_OFS, S6E36W5X01_ERR_LEN),
	[READ_ERR_FG] = RDINFO_INIT(err_fg, DSI_PKT_TYPE_RD, S6E36W5X01_ERR_FG_REG, S6E36W5X01_ERR_FG_OFS, S6E36W5X01_ERR_FG_LEN),
	[READ_DSI_ERR] = RDINFO_INIT(dsi_err, DSI_PKT_TYPE_RD, S6E36W5X01_DSI_ERR_REG, S6E36W5X01_DSI_ERR_OFS, S6E36W5X01_DSI_ERR_LEN),
	[READ_SELF_DIAG] = RDINFO_INIT(self_diag, DSI_PKT_TYPE_RD, S6E36W5X01_SELF_DIAG_REG, S6E36W5X01_SELF_DIAG_OFS, S6E36W5X01_SELF_DIAG_LEN),
};

static DEFINE_RESUI(id, &s6e36w5x01_rditbl[READ_ID], 0);
static DEFINE_RESUI(coordinate, &s6e36w5x01_rditbl[READ_COORDINATE], 0);
static DEFINE_RESUI(code, &s6e36w5x01_rditbl[READ_CODE], 0);
static DEFINE_RESUI(elvss, &s6e36w5x01_rditbl[READ_ELVSS], 0);
static DEFINE_RESUI(mtp, &s6e36w5x01_rditbl[READ_MTP], 0);
static DEFINE_RESUI(date, &s6e36w5x01_rditbl[READ_DATE], 0);
static DEFINE_RESUI(octa_id, &s6e36w5x01_rditbl[READ_OCTA_ID], 0);
/* for brightness debugging */
static DEFINE_RESUI(aor, &s6e36w5x01_rditbl[READ_AOR], 0);
static DEFINE_RESUI(chip_id, &s6e36w5x01_rditbl[READ_CHIP_ID], 0);
static DEFINE_RESUI(rddpm, &s6e36w5x01_rditbl[READ_RDDPM], 0);
static DEFINE_RESUI(rddsm, &s6e36w5x01_rditbl[READ_RDDSM], 0);
static DEFINE_RESUI(err, &s6e36w5x01_rditbl[READ_ERR], 0);
static DEFINE_RESUI(err_fg, &s6e36w5x01_rditbl[READ_ERR_FG], 0);
static DEFINE_RESUI(dsi_err, &s6e36w5x01_rditbl[READ_DSI_ERR], 0);
static DEFINE_RESUI(self_diag, &s6e36w5x01_rditbl[READ_SELF_DIAG], 0);

static struct resinfo s6e36w5x01_restbl[] = {
	[RES_ID] = RESINFO_INIT(id, S6E36W5X01_ID, RESUI(id)),
	[RES_COORDINATE] = RESINFO_INIT(coordinate, S6E36W5X01_COORDINATE, RESUI(coordinate)),
	[RES_CODE] = RESINFO_INIT(code, S6E36W5X01_CODE, RESUI(code)),
	[RES_DATE] = RESINFO_INIT(date, S6E36W5X01_DATE, RESUI(date)),
	[RES_OCTA_ID] = RESINFO_INIT(octa_id, S6E36W5X01_OCTA_ID, RESUI(octa_id)),
	[RES_CHIP_ID] = RESINFO_INIT(chip_id, S6E36W5X01_CHIP_ID, RESUI(chip_id)),
	[RES_RDDPM] = RESINFO_INIT(rddpm, S6E36W5X01_RDDPM, RESUI(rddpm)),
	[RES_RDDSM] = RESINFO_INIT(rddsm, S6E36W5X01_RDDSM, RESUI(rddsm)),
	[RES_ERR] = RESINFO_INIT(err, S6E36W5X01_ERR, RESUI(err)),
	[RES_ERR_FG] = RESINFO_INIT(err_fg, S6E36W5X01_ERR_FG, RESUI(err_fg)),
	[RES_DSI_ERR] = RESINFO_INIT(dsi_err, S6E36W5X01_DSI_ERR, RESUI(dsi_err)),
	[RES_SELF_DIAG] = RESINFO_INIT(self_diag, S6E36W5X01_SELF_DIAG, RESUI(self_diag)),
};

enum {
	DUMP_RDDPM = 0,
	DUMP_RDDPM_SLEEP_IN,
	DUMP_RDDSM,
	DUMP_ERR,
	DUMP_ERR_FG,
	DUMP_DSI_ERR,
	DUMP_SELF_DIAG,
};


static struct dump_expect rddpm_after_display_on_expects[] = {
	{ .offset = 0, .mask = 0x80, .value = 0x80, .msg = "Booster Mode : OFF(NG)" },
	{ .offset = 0, .mask = 0x40, .value = 0x00, .msg = "Idle Mode : ON(NG)" },
	{ .offset = 0, .mask = 0x10, .value = 0x10, .msg = "Sleep Mode : IN(NG)" },
	{ .offset = 0, .mask = 0x08, .value = 0x08, .msg = "Normal Mode : SLEEP(NG)" },
	{ .offset = 0, .mask = 0x04, .value = 0x04, .msg = "Display Mode : OFF(NG)" },
};

static struct dump_expect rddpm_before_sleep_in_expects[] = {
	{ .offset = 0, .mask = 0x80, .value = 0x80, .msg = "Booster Mode : OFF(NG)" },
	{ .offset = 0, .mask = 0x40, .value = 0x00, .msg = "Idle Mode : ON(NG)" },
	{ .offset = 0, .mask = 0x10, .value = 0x10, .msg = "Sleep Mode : IN(NG)" },
	{ .offset = 0, .mask = 0x08, .value = 0x08, .msg = "Normal Mode : SLEEP(NG)" },
	{ .offset = 0, .mask = 0x04, .value = 0x00, .msg = "Display Mode : ON(NG)" },
};

static struct dump_expect rddsm_expects[] = {
	{ .offset = 0, .mask = 0xFF, .value = 0x80, .msg = "TE Mode : OFF(NG)" },
};

static struct dump_expect dsie_cnt_expects[] = {
	{ .offset = 0, .mask = 0xFF, .value = 0x00, .msg = "DSI Error Count" },
};

static struct dump_expect self_diag_expects[] = {
	{ .offset = 0, .mask = 0x40, .value = 0x40, .msg = "Panel Boosting Error" },
};

static struct dump_expect error_flag_expects[] = {
	{ .offset = 0, .mask = 0x08, .value = 0x08, .msg = "ELVDD Error" },
	{ .offset = 0, .mask = 0x04, .value = 0x04, .msg = "VLOUT3 Error" },
	{ .offset = 0, .mask = 0x40, .value = 0x40, .msg = "VLIN1 Error" },
};

static struct dump_expect error_expects[] = {
	{ .offset = 0, .mask = 0x01, .value = 0x01, .msg = "SoT Error" },
	{ .offset = 0, .mask = 0x02, .value = 0x02, .msg = "SoT sync Error" },
	{ .offset = 0, .mask = 0x04, .value = 0x04, .msg = "EoT sync Error" },
	{ .offset = 0, .mask = 0x08, .value = 0x08, .msg = "Escape Mode Entry Command Error" },
	{ .offset = 0, .mask = 0x10, .value = 0x10, .msg = "Low-Power Transmit Sync Error" },
	{ .offset = 0, .mask = 0x20, .value = 0x20, .msg = "RX Timeout" },
	{ .offset = 0, .mask = 0x40, .value = 0x40, .msg = "False Control Error" },
	{ .offset = 0, .mask = 0x80, .value = 0x80, .msg = "Data Lane Contention Detection" },
		
	{ .offset = 1, .mask = 0x01, .value = 0x01, .msg = "ECC Error, single-bit (detected and corrected)" },
	{ .offset = 1, .mask = 0x02, .value = 0x02, .msg = "ECC Error, multi-bit (detected, not corrected)" },
	{ .offset = 1, .mask = 0x04, .value = 0x04, .msg = "Checksum Error" },
	{ .offset = 1, .mask = 0x08, .value = 0x08, .msg = "DSI Data Type Not Recognized" },		
	{ .offset = 1, .mask = 0x10, .value = 0x10, .msg = "DSI VC ID Invalid" },
	{ .offset = 1, .mask = 0x20, .value = 0x20, .msg = "Invalid Transmission Length" },
	{ .offset = 1, .mask = 0x40, .value = 0x40, .msg = "Data P Lane Contention Detetion" },
	{ .offset = 1, .mask = 0x80, .value = 0x80, .msg = "DSI Protocol Violation" },		

	{ .offset = 2, .mask = 0xFF, .value = 0x00, .msg = "CRC Error Count" },
	{ .offset = 3, .mask = 0xFF, .value = 0x00, .msg = "ECC1 Error Count" },
	{ .offset = 4, .mask = 0xFF, .value = 0x00, .msg = "ECC2 Error Count" },				
};

static struct dumpinfo s6e36w5x01_dmptbl[] = {
	[DUMP_RDDPM] = DUMPINFO_INIT_V2(rddpm, &s6e36w5x01_restbl[RES_RDDPM], &OLED_FUNC(OLED_DUMP_SHOW_RDDPM), rddpm_after_display_on_expects),
	[DUMP_RDDPM_SLEEP_IN] = DUMPINFO_INIT_V2(rddpm_sleep_in, &s6e36w5x01_restbl[RES_RDDPM], &OLED_FUNC(OLED_DUMP_SHOW_RDDPM_BEFORE_SLEEP_IN), rddpm_before_sleep_in_expects),
	[DUMP_RDDSM] = DUMPINFO_INIT_V2(rddsm, &s6e36w5x01_restbl[RES_RDDSM], &OLED_FUNC(OLED_DUMP_SHOW_RDDSM), rddsm_expects),
	[DUMP_DSI_ERR] = DUMPINFO_INIT_V2(dsi_err, &s6e36w5x01_restbl[RES_DSI_ERR], &OLED_FUNC(OLED_DUMP_SHOW_DSI_ERR), dsie_cnt_expects),
	[DUMP_SELF_DIAG] = DUMPINFO_INIT_V2(self_diag, &s6e36w5x01_restbl[RES_SELF_DIAG], &OLED_FUNC(OLED_DUMP_SHOW_SELF_DIAG), self_diag_expects),
	[DUMP_ERR_FG] = DUMPINFO_INIT_V2(err_fg, &s6e36w5x01_restbl[RES_ERR_FG], &DDI_FUNC(S6E36W5X01_DUMP_SHOW_ERROR_FLAG), error_flag_expects),
	[DUMP_ERR] = DUMPINFO_INIT_V2(err, &s6e36w5x01_restbl[RES_ERR], &DDI_FUNC(S6E36W5X01_DUMP_SHOW_ERROR), error_expects),
};

/* Variable Refresh Rate */
enum {
	S6E36W5X01_VRR_MODE_HS,
	MAX_S6E36W5X01_VRR_MODE,
};

enum {
	S6E36W5X01_VRR_60HS,
	MAX_S6E36W5X01_VRR,
};

enum {
	S6E36W5X01_RESOL_396x396,
};

enum {
	S6E36W5X01_SMALL_DISPLAY_MODE_396x396_60HS,
	MAX_S6E36W5X01_LARGE_DISPLAY_MODE,
};

enum {
	S6E36W5X01_ACL_RATIO_0,
	S6E36W5X01_ACL_RATIO_8,
	S6E36W5X01_ACL_RATIO_15,
	MAX_S6E36W5X01_ACL_RATIO,
};

enum {
	S6E36W5X01_SMOOTH_DIMMING_8FRAME,
	S6E36W5X01_SMOOTH_DIMMING_32FRAME,
	MAX_S6E36W5X01_SMOOTH_DIMMING,
};

enum {
	S6E36W5X01_HBM_OFF,
	S6E36W5X01_HBM_ON,
	MAX_S6E36W5X01_HBM,
};

enum {
	GE_TEMP_1,
	EQ_TEMP_0,
	LE_TEMP_MINUS1,
	LE_TEMP_MINUS15,
	MAX_TEMP,
};
int s6e36w5x01_dump_show_err_fg(struct dumpinfo *dump);
int s6e36w5x01_get_cell_id(struct panel_device *panel, void *buf);
int s6e36w5x01_get_manufacture_date(struct panel_device *panel, void *buf);
int s6e36w5x01_get_octa_id(struct panel_device *panel, void *buf);
int s6e36w5x01_get_manufacture_code(struct panel_device *panel, void *buf);
int s6e36w5x01_init(void);

#endif /* __S6E36W5X01_H__ */
