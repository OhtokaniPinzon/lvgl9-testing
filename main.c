/*
 * Copyright 2023 NXP 
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
//#include "lv_drivers/wayland/wayland.h"  
//#include "lv_drivers/display/fbdev.h"  
#include "lvgl/src/drivers/display/fb/lv_linux_fbdev.h"  
#include "lv_drivers/indev/evdev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

#define V_RES 1280
#define H_RES 720

//#define DISP_BUF_SIZE (128 * 1024)


static lv_display_t* hal_init(void)
{
	lv_display_t* disp = NULL;

    /*Linux Wayland device init*/
//    lv_wayland_init();
//    disp = lv_wayland_create_window(H_RES, V_RES, "Window Title", NULL);

	return disp;
}

bool close_cb(lv_disp_t * disp)
{
    printf("\nInside close callback function!!\n");
    printf("Program exit...\n");
    lv_deinit();
//    lv_wayland_deinit();

    exit(0);
}


int main(int argc, char ** argv)
{
	printf("************ LVGL demos **********\r\n");

    lv_disp_t * disp;

//bdev_init();
    /*LittlevGL init*/
    lv_init();
	printf("lv_init\r\n");
	disp = lv_linux_fbdev_create();
	lv_linux_fbdev_set_file(disp, "/dev/fb0");
    /*Linux Wayland device init*/
//	lv_wayland_init();
	printf("lv_wayland_init\r\n");
//	disp = lv_wayland_create_window(H_RES, V_RES, "Window Title", close_cb);
//    disp = lv_display_create(H_RES, V_RES);

	lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);

    lv_color32_t * buf1 = NULL;
    lv_color32_t * buf2 = NULL;

    /* Initialize draw buffer */
    buf1 = lv_malloc(H_RES * V_RES * sizeof(lv_color32_t));
    if (!buf1)
    {
        printf("********************** failed to allocate draw buffer 1\r\n");
        LV_LOG_ERROR("failed to allocate draw buffer 1");
        return NULL;
    }

    buf2 = lv_malloc(H_RES * V_RES * sizeof(lv_color32_t));
    if (!buf2)
    {
        printf("********************** failed to allocate draw buffer 2\r\n");
        LV_LOG_ERROR("failed to allocate draw buffer 2");
        return NULL;
    }

//	lv_display_set_flush_cb(disp, flush_cb);
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
	}

demo_end:
	lv_deinit();
	return 0;
}

