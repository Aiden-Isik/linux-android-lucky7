# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the Linux kernel panel device drivers.
#

subdir-ccflags-$(CONFIG_SEC_KUNIT) += \
	-I$(srctree)/$(src)/.. \
	-Wframe-larger-than=8192 \
	-Wno-unused-variable \
	-Wunused-function \
	-Wno-missing-braces \
	-Wno-implicit-fallthrough \
	-Wformat

subdir-ccflags-y += -I$(srctree)/$(src)/../oled_common


subdir-ccflags-y += -I$(srctree)/$(src)/../oled_common

mcd-panel-s6e36w5x01_watch_fe_small-y += s6e36w5x01.o s6e36w5x01_watch_fe_small.o

obj-$(CONFIG_USDM_PANEL_S6E36W5X01) += mcd-panel-s6e36w5x01_watch_fe_small.o

