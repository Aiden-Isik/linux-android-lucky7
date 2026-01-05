/*
 * linux/drivers/video/fbdev/exynos/panel/s6e36w5x01/s6e36w5x01_dimming.h
 *
 * Header file for S6E36W5X01 Dimming Driver
 *
 * Copyright (c) 2016 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __S6E36W5X01_DIMMING_H__
#define __S6E36W5X01_DIMMING_H__
#include <linux/types.h>
#include <linux/kernel.h>
#include "../dimming.h"
#include "s6e36w5x01.h"

#define S6E36W5X01_NR_TP (11)

#define S6E36W5X01_NR_LUMINANCE (256)
#define S6E36W5X01_TARGET_LUMINANCE (600)

#define S6E36W5X01_NR_HBM_LUMINANCE (256)
#define S6E36W5X01_TARGET_HBM_LUMINANCE (600)

#define S6E36W5X01_NR_STEP (256)
#define S6E36W5X01_HBM_STEP (45)
#define S6E36W5X01_TOTAL_STEP (S6E36W5X01_NR_STEP + S6E36W5X01_HBM_STEP)

#ifdef CONFIG_USDM_PANEL_AOD_BL
#define S6E36W5X01_AOD_NR_LUMINANCE (4)
#define S6E36W5X01_AOD_TARGET_LUMINANCE (60)
#endif

#define S6E36W5X01_TOTAL_NR_LUMINANCE (S6E36W5X01_NR_LUMINANCE + S6E36W5X01_NR_HBM_LUMINANCE)

#endif /* __S6E36W5X01_DIMMING_H__ */
