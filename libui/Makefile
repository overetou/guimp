#Work title
TARGET=libui.a
TEST_OUT=windows_demo

#Directories
OBJ_DIR=obj
SRC_DIR=src
INC_DIRS=inc
LIB_DIRS=.
SDL_DIR=sdl2

#Compilation related indications
CC=clang
CFLAGS=-Wall -Wextra -Werror
LIBS=SDL2 SDL2_image SDL2_ttf m#m stands for mathlib

#From there we use the info to compile everything.
SRC_FILE_NAMES = ui.c security.c dimension_resolutions.c simple_buttons.c basic_stuff.c \
elem.c blocking.c display.c events.c sensibility.c premade_callbacks.c radio_buttons.c \
data_printing.c checkbox_button.c
SOURCES=$(addprefix $(SRC_DIR)/, $(SRC_FILE_NAMES))
OBJS:=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC_FLAGS=$(addprefix -I,$(INC_DIRS))
LIBDIR_FLAGS=$(addprefix -L,$(LIB_DIRS))
CFLAGS+= $(INC_FLAGS)
LIBS_FLAGS=$(addprefix -l,$(LIBS))
VPATH=$(SRC_DIR)

.phony: $(TARGET) clean re

all: $(TEST_OUT)

$(SDL_DIR):
	mkdir $(SDL_DIR)
	git clone https://github.com/libsdl-org/SDL.git sdl2/SDL
	cd $(SDL_DIR)/SDL/ && mkdir build && cd build && ../configure && make
	git clone https://gitlab.freedesktop.org/freetype/freetype.git $(SDL_DIR)/freetype
	cd $(SDL_DIR)/freetype && sh autogen.sh && ./configure FT2_CONFIG=../freetype/builds/unix/freetype-config && make
	cd $(SDL_DIR) && curl https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.zip --output SDL2_ttf-2.0.15.zip && unzip SDL2_ttf-2.0.15.zip && cd SDL2_ttf-2.0.15 && \
	./configure && make
	cd $(SDL_DIR) && curl https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.zip --output SDL2_image-2.0.5.zip && unzip SDL2_image-2.0.5.zip && cd SDL2_image-2.0.5 && \
	./configure && make

$(TARGET): $(OBJS) $(INC_DIRS)/ui.h
	@ar rcs $@ $(OBJS)

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIRS)/ui.h |$(OBJ_DIR) $(SDL_DIR)
	@$(COMPILE.c) -g $(OUTPUT_OPTIONS) -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJS) $(TARGET)

$(TEST_OUT): $(TARGET) tests/windows_demo.c
	$(CC) -g $(INC_FLAGS) -o $@ tests/windows_demo.c $(LIB_DIRFLAGS) $(LIBS_FLAGS) $<

re: clean $(TARGET)
