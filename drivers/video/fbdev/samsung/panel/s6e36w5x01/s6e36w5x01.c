/*
 * linux/drivers/video/fbdev/exynos/panel/rm69091/rm69091.c
 *
 * S6E3HAB Dimming Driver
 *
 * Copyright (c) 2016 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/of_gpio.h>
#include <video/mipi_display.h>
#include "../panel.h"
#include "../panel_function.h"
#ifdef CONFIG_USDM_PANEL_DIMMING
#include "../dimming.h"
#include "../panel_dimming.h"
#endif
#include "../panel_drv.h"
#include "../panel_debug.h"
#include "s6e36w5x01.h"
#include "oled_common.h"

#ifdef PANEL_PR_TAG
#undef PANEL_PR_TAG
#define PANEL_PR_TAG	"ddi"
#endif

//minwoo76945.kim Todo
//#ifdef CONFIG_USDM_PANEL_DIMMING
int generate_brt_step_table(struct brightness_table *brt_tbl)
{
	int ret = 0;
	int i = 0, j = 0, k = 0;

	if (unlikely(!brt_tbl || !brt_tbl->brt)) {
		panel_err("invalid parameter\n");
		return -EINVAL;
	}
	if (unlikely(!brt_tbl->step_cnt)) {
		if (likely(brt_tbl->brt_to_step)) {
			panel_info("we use static step table\n");
			return ret;
		} else {
			panel_err("invalid parameter, all table is NULL\n");
			return -EINVAL;
		}
	}

	brt_tbl->sz_brt_to_step = 0;
	for(i = 0; i < brt_tbl->sz_step_cnt; i++)
		brt_tbl->sz_brt_to_step += brt_tbl->step_cnt[i];

	brt_tbl->brt_to_step =
		(u32 *)kmalloc(brt_tbl->sz_brt_to_step * sizeof(u32), GFP_KERNEL);

	if (unlikely(!brt_tbl->brt_to_step)) {
		panel_err("alloc fail\n");
		return -EINVAL;
	}
	brt_tbl->brt_to_step[0] = brt_tbl->brt[0];
	i = 1;
	while (i < brt_tbl->sz_brt_to_step) {
		for (k = 1; k < brt_tbl->sz_brt; k++) {
			for (j = 1; j <= brt_tbl->step_cnt[k]; j++, i++) {
				brt_tbl->brt_to_step[i] = disp_interpolation64(brt_tbl->brt[k - 1] * disp_pow(10, 2),
					brt_tbl->brt[k] * disp_pow(10, 2), j, brt_tbl->step_cnt[k]);
				brt_tbl->brt_to_step[i] = disp_pow_round(brt_tbl->brt_to_step[i], 2);
				brt_tbl->brt_to_step[i] = disp_div64(brt_tbl->brt_to_step[i], disp_pow(10, 2));
				if (brt_tbl->brt[brt_tbl->sz_brt - 1] < brt_tbl->brt_to_step[i]) {

					brt_tbl->brt_to_step[i] = disp_pow_round(brt_tbl->brt_to_step[i], 2);
				}
				if (i >= brt_tbl->sz_brt_to_step) {
					panel_err("step cnt over %d %d\n", i, brt_tbl->sz_brt_to_step);
					break;
				}
			}
		}
	}
	return ret;
}

//#endif /* CONFIG_USDM_PANEL_DIMMING */

int s6e36w5x01_maptbl_init_gamma_mode2_brt(struct maptbl *tbl)
{
	struct panel_info *panel_data;
	struct panel_device *panel;
	struct panel_dimming_info *panel_dim_info;
	//todo:remove
	panel_info("++\n");
	if (tbl == NULL) {
		panel_err("maptbl is null\n");
		return -EINVAL;
	}

	if (tbl->pdata == NULL) {
		panel_err("pdata is null\n");
		return -EINVAL;
	}

	panel = tbl->pdata;
	panel_data = &panel->panel_data;

	panel_dim_info = panel_data->panel_dim_info[PANEL_BL_SUBDEV_TYPE_DISP];

	if (panel_dim_info == NULL) {
		panel_err("panel_dim_info is null\n");
		return -EINVAL;
	}

	if (panel_dim_info->brt_tbl == NULL) {
		panel_err("panel_dim_info->brt_tbl is null\n");
		return -EINVAL;
	}

	generate_brt_step_table(panel_dim_info->brt_tbl);

	/* initialize brightness_table */
	memcpy(&panel->panel_bl.subdev[PANEL_BL_SUBDEV_TYPE_DISP].brt_tbl,
			panel_dim_info->brt_tbl, sizeof(struct brightness_table));

	return 0;
}

int s6e36w5x01_maptbl_getidx_acl_control(struct maptbl *tbl)
{
	struct panel_device *panel = (struct panel_device *)tbl->pdata;
	struct panel_bl_device *panel_bl;
	struct panel_info *panel_data;
	int row;

	if (panel == NULL) {
		panel_err("panel is null\n");
		return -EINVAL;
	}
	panel_bl = &panel->panel_bl;
	panel_data = &panel->panel_data;

	if (is_hbm_brightness(panel_bl, panel_bl->props.brightness)) {
		row = panel_data->props.adaptive_control = S6E36W5X01_ACL_RATIO_8;
	} else {
		row = panel_data->props.adaptive_control = S6E36W5X01_ACL_RATIO_0;
	}

	panel_info("set acl %d\n", row);
	return maptbl_index(tbl, 0, row, 0);
}

int s6e36w5x01_maptbl_getidx_smooth_dimming_control(struct maptbl *tbl)
{
	struct panel_device *panel = (struct panel_device *)tbl->pdata;
	struct panel_bl_device *panel_bl;
	struct panel_info *panel_data;
	int row = 0, layer = 0;

	if (panel == NULL) {
		panel_err("panel is null\n");
		return -EINVAL;
	}
	panel_bl = &panel->panel_bl;
	panel_data = &panel->panel_data;

	row = 1;
	layer = is_hbm_brightness(panel_bl, panel_bl->props.brightness);

	return maptbl_index(tbl, layer, row, 0);
}

int s6e36w5x01_get_cell_id(struct panel_device *panel, void *buf)
{
	u8 date[7] = { 0, }, coordinate[4] = { 0, };
	struct panel_info *panel_data;

	if (panel == NULL) {
		panel_err("panel is null\n");
		return -EINVAL;
	}
	panel_data = &panel->panel_data;

	panel_resource_copy(panel, date, "date");
	panel_resource_copy(panel, coordinate, "coordinate");

	snprintf(buf, PAGE_SIZE, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
		date[0], date[1], date[2], date[3], date[4], date[5], date[6],
		coordinate[0], coordinate[1], coordinate[2], coordinate[3]);
	
	return 0;
}

int s6e36w5x01_get_manufacture_date(struct panel_device *panel, void *buf)
{
	u8 date[7] = { 0, };
	u16 year;
	u8 month, day, hour, min;

	struct panel_info *panel_data;

	if (panel == NULL) {
		panel_err("panel is null\n");
		return -EINVAL;
	}
	panel_data = &panel->panel_data;

	panel_resource_copy(panel, date, "date");

	year = ((date[0] & 0xF0) >> 4) + 2011;
	month = date[0] & 0xF;
	day = date[1] & 0x1F;
	hour = date[2] & 0x1F;
	min = date[3] & 0x3F;

	snprintf(buf, PAGE_SIZE, "%d, %d, %d, %d:%d\n",
				year, month, day, hour, min);

	return 0;
}

int s6e36w5x01_get_octa_id(struct panel_device *panel, void *buf)
{
	int i, site, rework, poc;
	u8 cell_id[16], octa_id[PANEL_OCTA_ID_LEN] = { 0, };
	int len = 0;
	bool cell_id_exist = true;
	
	if (panel == NULL) {
		panel_err("panel is null\n");
		return -EINVAL;
	}
	panel_resource_copy(panel, octa_id, "octa_id");

	site = (octa_id[0] >> 4) & 0x0F;
	rework = octa_id[0] & 0x0F;
	poc = octa_id[1] & 0x0F;

	panel_dbg("site (%d), rework (%d), poc (%d)\n",
			site, rework, poc);

	panel_dbg("<CELL ID>\n");
	for (i = 0; i < 16; i++) {
		cell_id[i] = isalnum(octa_id[i + 4]) ? octa_id[i + 4] : '\0';
		panel_dbg("%x -> %c\n", octa_id[i + 4], cell_id[i]);
		if (cell_id[i] == '\0') {
			cell_id_exist = false;
			break;
		}
	}

	len += snprintf(buf + len, PAGE_SIZE - len, "%d%d%d%02x%02x",
			site, rework, poc, octa_id[2], octa_id[3]);

	if (cell_id_exist) {
		for (i = 0; i < 16; i++)
			len += snprintf(buf + len, PAGE_SIZE - len, "%c", cell_id[i]);
	}
	len += snprintf(buf + len, PAGE_SIZE - len, "\n");
	return 0;
}

int s6e36w5x01_get_manufacture_code(struct panel_device *panel, void *buf)
{
	u8 code[5] = { 0, };

	if (panel == NULL) {
		panel_err("panel is null\n");
		return -EINVAL;
	}

	panel_resource_copy(panel, code, "code");
	snprintf(buf, PAGE_SIZE, "%02X%02X%02X%02X%02X\n",
		code[0], code[1], code[2], code[3], code[4]);

	return 0;
}

int s6e36w5x01_maptbl_getidx_tset(struct maptbl *tbl)
{
	struct panel_device *panel;
	struct panel_info *panel_data;
	struct panel_bl_device *panel_bl;
	int row;

	if (!tbl || !tbl->pdata)
		return -EINVAL;

	panel = (struct panel_device *)tbl->pdata;
	if (unlikely(!panel))
		return -EINVAL;

	panel_data = &panel->panel_data;
	panel_bl = &panel->panel_bl;
	row = is_hbm_brightness(panel_bl, panel_bl->props.brightness);
	
	panel_info("tset %d\n", row);
	return maptbl_index(tbl, 0, row, 0);
}

int s6e36w5x01_dump_show_error_flag(struct dumpinfo *dump)
{
	int ret;
	u8 error_flag[S6E36W5X01_ERR_FG_LEN] = { 0, };
	struct resinfo *res;

	if (!dump)
		return -EINVAL;

	res = dump->res;
	if (!is_valid_resource(res))
		return -EINVAL;

	if (!is_resource_initialized(res))
		return -EINVAL;

	if (!res || ARRAY_SIZE(error_flag) != res->dlen) {
		panel_err("invalid resource\n");
		return -EINVAL;
	}

	ret = copy_resource(error_flag, res);
	if (unlikely(ret < 0)) {
		panel_err("failed to copy err_fg resource\n");
		return -EINVAL;
	}
	return oled_dump_show_expects(dump);
}

int s6e36w5x01_dump_show_error(struct dumpinfo *dump)
{
	int ret;
	u8 error[S6E36W5X01_ERR_LEN] = { 0, };
	struct resinfo *res;

	if (!dump)
		return -EINVAL;

	res = dump->res;
	if (!is_valid_resource(res))
		return -EINVAL;

	if (!is_resource_initialized(res))
		return -EINVAL;

	if (!res || ARRAY_SIZE(error) != res->dlen) {
		panel_err("invalid resource\n");
		return -EINVAL;
	}

	ret = copy_resource(error, res);
	if (unlikely(ret < 0)) {
		panel_err("failed to copy err resource\n");
		return -EINVAL;
	}
	return oled_dump_show_expects(dump);
}

/* required delay(ms) from display on cmd */
#define SMOOTH_DIM_DELAY_AFTER_DISPLAYON_MS 500
/* required delay(ms) from last brightnes change cmd */
#define SMOOTH_DIM_DELAY_PREV_BRIGHTNESS_MS 180

bool s6e36w5x01_cond_is_smooth_dimming_available(struct panel_device *panel)
{
	struct panel_bl_device *panel_bl;
	struct panel_info *panel_data;
	static ktime_t last_time;
	ktime_t now;
	s64 diff;
	bool ret = false;

	if (panel == NULL) {
		panel_err("panel is null\n");
		return -EINVAL;
	}
	panel_bl = &panel->panel_bl;
	panel_data = &panel->panel_data;
	now = ktime_get();

	if (panel->state.disp_on != PANEL_DISPLAY_ON) {
		panel_info("panel is off state, false\n");
		goto exit;
	}
	diff = ktime_to_ms(ktime_sub(now, panel->ktime_panel_disp_on));
	if (diff < SMOOTH_DIM_DELAY_AFTER_DISPLAYON_MS) {
		panel_info("diff with displayon: %lld / %d, set 8frame\n", diff, SMOOTH_DIM_DELAY_AFTER_DISPLAYON_MS);
		goto exit;
	}
	diff = ktime_to_ms(ktime_sub(now, last_time));
	if (diff < SMOOTH_DIM_DELAY_PREV_BRIGHTNESS_MS) {
		panel_info("diff with prev brt: %lld / %d, set 8frame\n", diff, SMOOTH_DIM_DELAY_PREV_BRIGHTNESS_MS);
		goto exit;
	}

	panel_dbg("time %lld / %d last %lld / %d, set 32frame\n",
		ktime_to_ms(ktime_sub(now, panel->ktime_panel_disp_on)),
		SMOOTH_DIM_DELAY_AFTER_DISPLAYON_MS,
		ktime_to_ms(ktime_sub(now, last_time)),
		SMOOTH_DIM_DELAY_PREV_BRIGHTNESS_MS);

	ret = true;
exit:
	last_time = now;
	return ret;
}

struct pnobj_func s6e36w5x01_function_table[MAX_S6E36W5X01_FUNCTION] = {
	[S6E36W5X01_MAPTBL_INIT_GAMMA_MODE2_BRT] = __PNOBJ_FUNC_INITIALIZER(S6E36W5X01_MAPTBL_INIT_GAMMA_MODE2_BRT, s6e36w5x01_maptbl_init_gamma_mode2_brt),
	[S6E36W5X01_MAPTBL_GETIDX_ACL_CONTROL] = __PNOBJ_FUNC_INITIALIZER(S6E36W5X01_MAPTBL_GETIDX_ACL_CONTROL, s6e36w5x01_maptbl_getidx_acl_control),
	[S6E36W5X01_MAPTBL_GETIDX_HBM_TRANSITION_CONTROL] = __PNOBJ_FUNC_INITIALIZER(S6E36W5X01_MAPTBL_GETIDX_HBM_TRANSITION_CONTROL, s6e36w5x01_maptbl_getidx_smooth_dimming_control),
	[S6E36W5X01_MAPTBL_GETIDX_ELVSS_TEMP] = __PNOBJ_FUNC_INITIALIZER(S6E36W5X01_MAPTBL_GETIDX_ELVSS_TEMP, s6e36w5x01_maptbl_getidx_tset),
	[S6E36W5X01_DUMP_SHOW_ERROR_FLAG] = __PNOBJ_FUNC_INITIALIZER(S6E36W5X01_DUMP_SHOW_ERROR_FLAG, s6e36w5x01_dump_show_error_flag),
	[S6E36W5X01_DUMP_SHOW_ERROR] = __PNOBJ_FUNC_INITIALIZER(S6E36W5X01_DUMP_SHOW_ERROR, s6e36w5x01_dump_show_error),
	[S6E36W5X01_COND_IS_SMOOTH_DIMMING_AVAILABLE] = __PNOBJ_FUNC_INITIALIZER(S6E36W5X01_COND_IS_SMOOTH_DIMMING_AVAILABLE, s6e36w5x01_cond_is_smooth_dimming_available),
};

int s6e36w5x01_init(void)
{
	static bool once;
	int ret;

	if (once)
		return 0;

	ret = panel_function_insert_array(s6e36w5x01_function_table,
			ARRAY_SIZE(s6e36w5x01_function_table));
	if (ret < 0)
		panel_err("failed to insert s6e36w5x01_function_table\n");

	once = true;

	return 0;
}

MODULE_DESCRIPTION("Samsung Mobile Panel Driver");
MODULE_LICENSE("GPL");
