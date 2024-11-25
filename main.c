/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include "drivers/led/display/drv_disp_microbit.h"
#include "boards/bbc/microbit_v2/bbc_microbit_v2.h"

int main(void)
{
	board_init();

	drv_disp_print(MB_DISPLAY_MODE_SINGLE, 150, "Hello world");

	while (true) {
		k_msleep(1000);
	}

	return 0;
}
