/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Bring-up markers for the joan (msm8998) port. Each marker is followed by a
 * short delay so a live `dmesg -w` over USB ships the line before a silent
 * secure-side reset can take the SoC down.
 */
#ifndef __KGSL_JOAN_TRACE_H
#define __KGSL_JOAN_TRACE_H

#include <linux/delay.h>
#include <linux/printk.h>

extern int kgsl_joan_trace;
extern int kgsl_joan_perf;
extern int kgsl_joan_zapresume;

#define JTRACE(fmt, ...)						\
	do {								\
		if (kgsl_joan_trace) {					\
			pr_info("joan-kgsl: " fmt "\n", ##__VA_ARGS__);	\
			mdelay(kgsl_joan_trace);			\
		}							\
	} while (0)

#endif
