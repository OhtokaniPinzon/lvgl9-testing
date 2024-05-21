# Copyright 2023 NXP
# SPDX-License-Identifier: BSD-3-Clause

#
# Makefile
#

CC ?= gcc
LVGL_DIR_NAME = lvgl
LVGL_DIR = ${shell pwd}
CPPFLAGS = -I$(LVGL_DIR)/ -I$(INC_DIR_SRC)/ -I$(INC_DIR_GENERATED)/ -g3 -ggdb -O0
CFLAGS = -O0 -g3 -ggdb -I$(LVGL_DIR)/ -I$(INC_DIR_SRC)/ -I$(INC_DIR_GENERATED)/ -Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wall -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wshift-negative-value -Wstack-usage=2048 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare -DUSE_WAYLAND
LDFLAGS = -lm -lwayland-client -lxkbcommon -lwayland-cursor -lrt -Llvgl/src/drivers/wayland/protocols/libdf-wayland-xdg-application-stable-latest

#BIN = $(BIN_DIR)/demo
BIN_DIR = ./bin
OBJ_DIR = ./obj
INC_DIR_SRC = ./src
INC_DIR_GENERATED = ./src/generated

BIN = lvgl-demos

#Collect the files to compile
#MAINSRC = ./main.c

include $(LVGL_DIR)/lvgl/lvgl.mk


#CSRCS +=$(LVGL_DIR)/lvgl/demos/*.c

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))

MAINOBJ = $(MAINSRC:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

## MAINOBJ -> OBJFILES

.PHONY: all
all: default

%.o: %.c
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo "CC $<"
#@mkdir obj_files
#@mv $(OBJS) ./obj_files/

main.o: main.c
	$(CC) $(CFLAGS) -c -g $< -o $@

.PHONY: default
default: $(AOBJS) $(COBJS) main.o
	$(CC) -o $(BIN) main.o $(AOBJS) $(COBJS) $(LDFLAGS)
	
	mkdir deploy
	mv $(BIN) deploy/
	
	@mkdir -p obj_files
	@mv *.o ./obj_files/
	
.PHONY: clean
clean: 
	rm -rf $(BIN) $(AOBJS) $(COBJS) main.o obj_files/ deploy/

print-%:
	@echo $*=$($*)
