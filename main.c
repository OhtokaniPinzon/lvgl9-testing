/*
 * Copyright 2023 NXP 
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/wayland/wayland.h"  
#include "lv_drivers/indev/evdev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

#define H_RES 1280
#define V_RES 720

#define DISP_BUF_SIZE (128 * 1024)


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

    /*LittlevGL init*/
    lv_init();
	printf("lv_init\r\n");
    /*Linux Wayland device init*/
//	lv_wayland_init();
	printf("lv_wayland_init\r\n");
//	disp = lv_wayland_create_window(H_RES, V_RES, "Window Title", close_cb);
    disp = lv_display_create(H_RES, V_RES);

    printf("Disp = %d \n", disp);

	if (disp == NULL) {
		printf("display initialization failure!\r\n");
		return 1;
	}


	lv_demo_widgets();
/*
	if (!lv_demos_create(&argv[1], argc - 1)) {
		printf("lv_demos initialization failure!\r\n");
		lv_demos_show_help();
		goto demo_end;
	}
*/
	while (1) {
		uint32_t delay = lv_timer_handler();
		if (delay < 1) delay = 1;
		usleep(delay * 1000);
	}

demo_end:
	lv_deinit();
	return 0;
}

