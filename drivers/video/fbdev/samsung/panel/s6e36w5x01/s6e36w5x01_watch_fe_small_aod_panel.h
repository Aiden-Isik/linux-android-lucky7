/*
 * linux/drivers/video/fbdev/exynos/panel/s6e3fc3/s6e36w5x01_watch_fe_small_aod_panel.h
 *
 * Header file for AOD Driver
 *
 * Copyright (c) 2016 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __S6E36W5X01_WATCH_FE_SMALL_AOD_PANEL_H__
#define __S6E36W5X01_WATCH_FE_SMALL_AOD_PANEL_H__

#include "oled_common_aod.h"
#include "s6e36w5x01_aod.h"

static struct maptbl s6e36w5x01_watch_fe_small_aod_maptbl[] = {
};

static u8 S6E36W5X01_WATCH_FE_SMALL_AOD_KEY2_ENABLE[] = { 0xF0, 0x5A, 0x5A };
static u8 S6E36W5X01_WATCH_FE_SMALL_AOD_KEY2_DISABLE[] = { 0xF0, 0xA5, 0xA5 };

static DEFINE_STATIC_PACKET(s6e36w5x01_watch_fe_small_aod_key2_enable, DSI_PKT_TYPE_WR, S6E36W5X01_WATCH_FE_SMALL_AOD_KEY2_ENABLE, 0);
static DEFINE_STATIC_PACKET(s6e36w5x01_watch_fe_small_aod_key2_disable, DSI_PKT_TYPE_WR, S6E36W5X01_WATCH_FE_SMALL_AOD_KEY2_DISABLE, 0);

#if defined(CONFIG_USDM_FACTORY)
static u8 S6E36W5X01_WATCH_FE_SMALL_SELF_MASK_ENABLE[] = {
	0x7C,
	0x01, 0x00, 0xC7, 0x00, 0xC5, 0x00, 0xC5, 0x00,
	0x00, 0x00, 0x01
};
static DEFINE_STATIC_PACKET(s6e36w5x01_watch_fe_small_self_mask_enable, DSI_PKT_TYPE_WR, S6E36W5X01_WATCH_FE_SMALL_SELF_MASK_ENABLE, 0);
#else
static u8 S6E36W5X01_WATCH_FE_SMALL_SELF_MASK_ENABLE[] = {
	0x7C,
	0x01, 0x00, 0xC6, 0x00, 0xC5, 0x00, 0xC5, 0x00,
	0x00, 0x00, 0x01
};
static DEFINE_STATIC_PACKET(s6e36w5x01_watch_fe_small_self_mask_enable, DSI_PKT_TYPE_WR, S6E36W5X01_WATCH_FE_SMALL_SELF_MASK_ENABLE, 0);

#endif

static u8 S6E36W5X01_WATCH_FE_SMALL_SELF_MASK_DISABLE[] = {
	0x7C,
	0x00
};
static DEFINE_STATIC_PACKET(s6e36w5x01_watch_fe_small_self_mask_disable, DSI_PKT_TYPE_WR, S6E36W5X01_WATCH_FE_SMALL_SELF_MASK_DISABLE, 0);

static void *s6e36w5x01_watch_fe_small_aod_self_mask_ena_cmdtbl[] = {
	&PKTINFO(s6e36w5x01_watch_fe_small_aod_key2_enable),
	&PKTINFO(s6e36w5x01_watch_fe_small_self_mask_enable),
	&PKTINFO(s6e36w5x01_watch_fe_small_aod_key2_disable),
};

static void *s6e36w5x01_watch_fe_small_aod_self_mask_dis_cmdtbl[] = {
	&PKTINFO(s6e36w5x01_watch_fe_small_aod_key2_enable),
	&PKTINFO(s6e36w5x01_watch_fe_small_self_mask_disable),
	&PKTINFO(s6e36w5x01_watch_fe_small_aod_key2_disable),
};

static struct seqinfo s6e36w5x01_watch_fe_small_aod_seqtbl[] = {
	SEQINFO_INIT(SELF_MASK_ENA_SEQ, s6e36w5x01_watch_fe_small_aod_self_mask_ena_cmdtbl),
	SEQINFO_INIT(SELF_MASK_DIS_SEQ, s6e36w5x01_watch_fe_small_aod_self_mask_dis_cmdtbl),
};

static struct aod_tune s6e36w5x01_watch_fe_small_aod = {
	.name = "s6e36w5x01_watch_fe_small_aod",
	.nr_seqtbl = ARRAY_SIZE(s6e36w5x01_watch_fe_small_aod_seqtbl),
	.seqtbl = s6e36w5x01_watch_fe_small_aod_seqtbl,
	.nr_maptbl = ARRAY_SIZE(s6e36w5x01_watch_fe_small_aod_maptbl),
	.maptbl = s6e36w5x01_watch_fe_small_aod_maptbl,
	.self_mask_en = true,
};
#endif
