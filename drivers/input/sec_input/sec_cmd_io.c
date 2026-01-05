// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2022 Samsung Electronics Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/stat.h>
#include <linux/err.h>
#include <linux/sched.h>
#include <linux/sysfs.h>

#include <linux/miscdevice.h>
#include <linux/mutex.h>

#include "sec_cmd.h"
#include "sec_input.h"

#define ENABLE_DEBUG_LOG		0

#define IOCTL_SEC_CMD_IO_READ		_IOR('R', 0, struct sec_cmd_io_data)
#define IOCTL_SEC_CMD_IO_WRITE		_IOW('W', 0, struct sec_cmd_io_data)
#define IOCTL_SEC_CMD_IO_TESE		_IOW('T', 1, struct sec_cmd_io_data)
#define IOCTL_SEC_CMD_IO		_IO('I', 0)

#define TYPE_FIRMWARE_UPDATE		1
#define TYPE_FIRMWARE_LENGTH		2

#define CMD_FIRMWARE_UPDATE		1
#define CMD_OTHERS			2

#define MODE_FIRMWARE_UPDATE_START	1
#define MODE_FIRMWARE_UPDATE_DATA_INFO	2
#define MODE_FIRMWARE_UPDATE_DATA_STORE	3

#define SEC_CMD_IODATA_SIZE		2048

struct sec_cmd_io_data {
	int type;
	int cmd;
	int mode;
	int number;
	int length;
	char data[SEC_CMD_IODATA_SIZE];
};

struct sec_cmd_data *g_data;

static long sec_cmd_ioctl(struct file *file, unsigned int cmd,  void __user *p, int compat_mode)
{
	static struct sec_cmd_io_data l_io_data;
	struct sec_ts_plat_data *plat_data = g_data->dev->platform_data;
	int ii;

	mutex_lock(&g_data->io_lock);

	if (cmd == IOCTL_SEC_CMD_IO_READ) {
	} else if (cmd == IOCTL_SEC_CMD_IO) {
	} else if (cmd == IOCTL_SEC_CMD_IO_WRITE) {

		if (copy_from_user((void *)&l_io_data, p, sizeof(struct sec_cmd_io_data))) {
			input_err(true, g_data->dev, "%s: failed to copy_form_user\n", __func__);
			mutex_unlock(&g_data->io_lock);
			return -EFAULT;
		}
		input_info(true, g_data->dev, "%s: type: %d, cmd: %d, mode: %d, number: %d, length: %d\n",
				__func__, l_io_data.type, l_io_data.cmd, l_io_data.mode, l_io_data.number, l_io_data.length);

		if (ENABLE_DEBUG_LOG)
			input_err(true, g_data->dev, "%s: %x %x %x %x %x %x %x %x %x %x\n",
					__func__, l_io_data.data[0], l_io_data.data[1], l_io_data.data[2], l_io_data.data[3], l_io_data.data[4],
					l_io_data.data[5], l_io_data.data[6], l_io_data.data[7], l_io_data.data[8], l_io_data.data[9]);

		if (l_io_data.cmd == CMD_FIRMWARE_UPDATE) {
			if (l_io_data.mode == MODE_FIRMWARE_UPDATE_DATA_INFO) {
				if (!plat_data->external_firmware_data) {
					if (l_io_data.length <= 0) {
						input_err(true, g_data->dev, "%s: invalid length\n", __func__);
						mutex_unlock(&g_data->io_lock);
						return -ENOMEM;
					}
					plat_data->external_firmware_data = vmalloc(l_io_data.length);
					if (!plat_data->external_firmware_data) {
						mutex_unlock(&g_data->io_lock);
						return -ENOMEM;
					}
					plat_data->external_firmware_size = l_io_data.length;
				}
			} else if (l_io_data.mode == MODE_FIRMWARE_UPDATE_DATA_STORE) {
				unsigned int pos = (unsigned int)((l_io_data.number - 1) * SEC_CMD_IODATA_SIZE);

				if (l_io_data.number <= 0) {
					input_err(true, g_data->dev, "%s: invalid number\n", __func__);
					mutex_unlock(&g_data->io_lock);
					return -ENOMEM;
				}

				if (pos + l_io_data.length > plat_data->external_firmware_size) {
					input_err(true, g_data->dev, "%s: over than data size\n", __func__);
					mutex_unlock(&g_data->io_lock);
					return -ENOMEM;
				}

				if (ENABLE_DEBUG_LOG)
					input_info(true, g_data->dev,
							"%s: store: number: %d, length: %d, cur_size: %d\n",
							__func__, l_io_data.number, l_io_data.length, pos + l_io_data.length);
				for (ii = 0; ii < l_io_data.length; ii++)
					plat_data->external_firmware_data[pos + ii] = l_io_data.data[ii];
			} else {
				input_info(true, g_data->dev, "%s: mode: %x\n", __func__, l_io_data.mode);
			}
		} else {
		}
	} else {
		input_info(true, g_data->dev, "%s: cmd: %x\n", __func__, cmd);
	}

	mutex_unlock(&g_data->io_lock);
	return 0;
}

static long sec_cmd_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return sec_cmd_ioctl(file, cmd, (void __user *)arg, 0);
}

static long sec_cmd_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return sec_cmd_ioctl(file, cmd, (void __user *)arg, 1);
}

static int sec_cmd_ioctl_open(struct inode *inode, struct file *file)
{
	input_info(true, g_data->dev, "%s\n", __func__);
	return 0;
}

static int sec_cmd_ioctl_close(struct inode *inode, struct file *file)
{
	input_info(true, g_data->dev, "%s\n", __func__);
	return 0;
}

static const struct file_operations io_misc_fos = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = sec_cmd_unlocked_ioctl,
	.compat_ioctl = sec_cmd_compat_ioctl,
	.open = sec_cmd_ioctl_open,
	.release = sec_cmd_ioctl_close,
};

static struct miscdevice io_misc_device[3] = {
	{
		/* tsp1 */
		.fops = &io_misc_fos,
		.minor = MISC_DYNAMIC_MINOR,
		.name = "idio1",
	},
	{
		/* tsp2 */
		.fops = &io_misc_fos,
		.minor = MISC_DYNAMIC_MINOR,
		.name = "idio2",
	},
	{
		/* spen */
		.fops = &io_misc_fos,
		.minor = MISC_DYNAMIC_MINOR,
		.name = "idio3",
	}
};

int sec_cmd_io_init(struct sec_cmd_data *data, int devt)
{
	struct miscdevice *pmiscdevice;
	int ret;

	switch (devt) {
	case SEC_CLASS_DEVT_TSP:
	case SEC_CLASS_DEVT_TSP1:
		pmiscdevice = &io_misc_device[0];
		break;
	case SEC_CLASS_DEVT_TSP2:
		pmiscdevice = &io_misc_device[1];
		break;
	case SEC_CLASS_DEVT_WACOM:
		pmiscdevice = &io_misc_device[2];
		break;
	default:
		input_err(true, data->dev, "%s: not support device type: %d\n", __func__, devt);
		return -ENODEV;
	}

	mutex_init(&data->io_lock);

	ret = misc_register(pmiscdevice);
	if (ret < 0)
		return -ENODEV;

	input_info(true, data->dev, "%s: misc_register: ret: %d\n", __func__, ret);

	g_data = data;
	return 0;
}
EXPORT_SYMBOL(sec_cmd_io_init);

MODULE_DESCRIPTION("Samsung input cmd io");
MODULE_LICENSE("GPL");
