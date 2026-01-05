/*
 * linux/drivers/video/fbdev/exynos/panel/sw83109/sw83109_m54x_resol.h
 *
 * Header file for Panel Driver
 *
 * Copyright (c) 2019 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __S6E36W5X01_WATCH_FE_SMALL_RESOL_H__
#define __S6E36W5X01_WATCH_FE_SMALL_RESOL_H__

#include <dt-bindings/display/panel-display.h>
#include "../panel.h"
#include "s6e36w5x01.h"
#include "s6e36w5x01_dimming.h"

struct panel_vrr s6e36w5x01_watch_fe_small_default_panel_vrr[] = {
 	[S6E36W5X01_VRR_60HS] = {
		.fps = 60,
		.te_sw_skip_count = 0,
		.te_hw_skip_count = 0,
		.mode = VRR_HS_MODE,
	},
 };

static struct panel_vrr *s6e36w5x01_watch_fe_small_default_vrrtbl[] = {
 	&s6e36w5x01_watch_fe_small_default_panel_vrr[S6E36W5X01_VRR_60HS],
 };

static struct panel_resol s6e36w5x01_watch_fe_small_default_resol[] = {
	[S6E36W5X01_RESOL_396x396] = {
		.w = 396,
		.h = 396,
		.comp_type = PN_COMP_TYPE_NONE,
		.available_vrr = s6e36w5x01_watch_fe_small_default_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e36w5x01_watch_fe_small_default_vrrtbl),
	},
};

#if defined(CONFIG_USDM_PANEL_DISPLAY_MODE)
static struct common_panel_display_mode s6e36w5x01_watch_fe_small_display_mode[] = {
 	[S6E36W5X01_SMALL_DISPLAY_MODE_396x396_60HS] = {
		.name = PANEL_DISPLAY_MODE_396x396_60HS,
		.resol = &s6e36w5x01_watch_fe_small_default_resol[S6E36W5X01_RESOL_396x396],
		.vrr = &s6e36w5x01_watch_fe_small_default_panel_vrr[S6E36W5X01_VRR_60HS],
	},
 };

static struct common_panel_display_mode *s6e36w5x01_watch_fe_small_display_mode_array[] = {
 	[S6E36W5X01_SMALL_DISPLAY_MODE_396x396_60HS] = &s6e36w5x01_watch_fe_small_display_mode[S6E36W5X01_SMALL_DISPLAY_MODE_396x396_60HS],
 };

static struct common_panel_display_modes s6e36w5x01_watch_fe_small_display_modes = {
	.num_modes = ARRAY_SIZE(s6e36w5x01_watch_fe_small_display_mode),
	.modes = (struct common_panel_display_mode **)&s6e36w5x01_watch_fe_small_display_mode_array,
};
#endif /* CONFIG_USDM_PANEL_DISPLAY_MODE */
#endif /* __S6E36W5X01_WATCH_FE_SMALL_RESOL_H__ */
