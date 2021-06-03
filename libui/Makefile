#Work title
TARGET=libui.a
TEST_OUT=windows_demo

#Directories
SDL_DIR=sdl2
OBJ_DIR=obj
SRC_DIR=src
INC_DIRS=inc $(SDL_DIR)/libs/include
LIB_DIRS=. $(SDL_DIR)/libs/lib

#Compilation related indications
CC=clang
CFLAGS=-Wall -Wextra -Werror
LIBS=SDL2 SDL2_image SDL2_ttf m#m stands for mathlib

#From there we use the info to compile everything.
SRC_FILE_NAMES = ui.c security.c dimension_resolutions.c simple_buttons.c basic_stuff.c \
elem.c blocking.c display.c events.c sensibility.c premade_callbacks.c radio_buttons.c \
data_printing.c checkbox_button.c slider.c text_line_input.c perma_func_blocks.c int_manipulation.c
SOURCES=$(addprefix $(SRC_DIR)/, $(SRC_FILE_NAMES))
OBJS:=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC_FLAGS=$(addprefix -I,$(INC_DIRS))
LIBDIR_FLAGS=$(addprefix -L,$(LIB_DIRS))
CFLAGS+= $(INC_FLAGS)
LIBS_FLAGS=$(addprefix -l,$(LIBS))
VPATH=$(SRC_DIR)

CUR_DIR = $(shell pwd)

.phony: $(TARGET) clean re

all: $(TEST_OUT)

$(SDL_DIR):#This installation script is meant to be used during my scool corrections involving this lib.
	mkdir $(SDL_DIR)
	git clone https://github.com/libsdl-org/SDL.git $(SDL_DIR)/SDL
	cd $(SDL_DIR)/SDL/ && mkdir build && cd build && ../configure --prefix=$(CUR_DIR)/$(SDL_DIR)/libs && make && make install
	git clone https://gitlab.freedesktop.org/freetype/freetype.git $(SDL_DIR)/freetype
	cd $(SDL_DIR)/freetype && sh autogen.sh && ./configure --prefix=$(CUR_DIR)/$(SDL_DIR)/libs  && make && make install
	cd $(SDL_DIR) && curl https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.zip --output SDL2_ttf-2.0.15.zip \
	&& unzip SDL2_ttf-2.0.15.zip && cd SDL2_ttf-2.0.15 && \
	./configure --prefix=$(CUR_DIR)/$(SDL_DIR)/libs FT2_CONFIG=$(CUR_DIR)/$(SDL_DIR)/freetype/builds/unix/freetype-config SDL2_CONFIG=$(CUR_DIR)/$(SDL_DIR)/libs/bin/sdl2-config \
	&& make && make install
	cd $(SDL_DIR) && curl https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.zip --output SDL2_image-2.0.5.zip \
	&& unzip SDL2_image-2.0.5.zip && cd SDL2_image-2.0.5 && \
	./configure --prefix=$(CUR_DIR)/$(SDL_DIR)/libs SDL2_CONFIG=$(CUR_DIR)/$(SDL_DIR)/libs/bin/sdl2-config \
	&& make && make install

$(TARGET): $(OBJS) inc/ui.h
	@ar rcs $@ $(OBJS)

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c inc/ui.h |$(OBJ_DIR) $(SDL_DIR)
	@$(COMPILE.c) -g $(OUTPUT_OPTIONS) -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJS) $(TARGET)

$(TEST_OUT): $(TARGET) tests/windows_demo.c
	@$(CC) -g $(INC_FLAGS) -o $@ tests/windows_demo.c $(LIBDIR_FLAGS) $(LIBS_FLAGS) $<
	@echo 'Test compiled.'

re: clean $(TARGET)
