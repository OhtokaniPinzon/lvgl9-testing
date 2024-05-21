/*
 * Copyright 2023 NXP 
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl/src/drivers/wayland/wayland.h"  
#include "lvgl/src/indev/lv_indev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

#define H_RES 1280
#define V_RES 800


static lv_display_t* hal_init(void)
{
	lv_display_t* disp = NULL;

    /*Linux Wayland device init*/
    lv_wayland_init();
    disp = lv_wayland_create_window(H_RES, V_RES, "Window Title", NULL);

	return disp;
}

bool close_cb(lv_disp_t * disp)
{
    printf("\nInside close callback function!!\n");
    printf("Program exit...\n");
    lv_deinit();
    lv_wayland_deinit();

    exit(0);
}


int main(int argc, char ** argv)
{
	printf("************ LVGL demos **********\r\n");

    lv_disp_t * disp;

    /*LittlevGL init*/
    lv_init();
	printf("lv_init\r\n");

    /*Linux Wayland device init*/
	disp = hal_init();
	printf("lv_wayland_init\r\n");

	lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);

    lv_color32_t * buf1 = NULL;
    lv_color32_t * buf2 = NULL;

    /* Initialize draw buffer */
    buf1 = lv_malloc(H_RES * V_RES * sizeof(lv_color32_t)*4);
    if (!buf1)
    {
        printf("********************** failed to allocate draw buffer 1\r\n");
        LV_LOG_ERROR("failed to allocate draw buffer 1");
        return NULL;
    }

    buf2 = lv_malloc(H_RES * V_RES * sizeof(lv_color32_t)*4);
    if (!buf2)
    {
        printf("********************** failed to allocate draw buffer 2\r\n");
        LV_LOG_ERROR("failed to allocate draw buffer 2");
        return NULL;
    }

	lv_display_set_buffers(disp, buf1, buf2, H_RES * V_RES * sizeof(lv_color32_t)*8, LV_DISPLAY_RENDER_MODE_DIRECT);
    printf("Disp = %d \n", (int)disp);

	if (disp == NULL) {
		printf("display initialization failure!\r\n");
		return 1;
	}


	if (!lv_demos_create(&argv[1], argc - 1)) {
		printf("lv_demos initialization failure!\r\n");
		lv_demos_show_help();
		goto demo_end;
	}

	while (1) {
		uint32_t delay = lv_timer_handler();
		if (delay < 1) delay = 1;
		usleep(delay * 1000);
		lv_tick_inc(50);
	}

demo_end:
	lv_deinit();
	return 0;
}

