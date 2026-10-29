/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __KGSL_A540_RAIL_H
#define __KGSL_A540_RAIL_H

struct device;

void kgsl_a540_gfx_apply_open_loop(struct device *dev);
int kgsl_a540_gfx_set_opp_config(struct device *dev);

#endif
