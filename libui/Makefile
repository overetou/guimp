#Work title
TARGET=libui.a

#Directories
OBJ_DIR=obj
SRC_DIR=src
INC_DIRS=inc
LIB_DIRS=

#Compilation related indications
CC=clang
CFLAGS=-Wall -Wextra -Werror
LIBS=SDL2 SDL2_image m#m stands for mathlib

#From there we use the info to compile everything.
SRC_FILE_NAMES = ui.c security.c calculus.c interface_elements.c basic_stuff.c elem.c blocking.c display.c
SOURCES=$(addprefix $(SRC_DIR)/, $(SRC_FILE_NAMES))
OBJS:=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC_FLAGS=$(addprefix -I,$(INC_DIRS))
LIBIDR_FLAGS=$(addprefix -L,$(LIB_DIRS))
CFLAGS+=$(INC_FLAGS)
LIBS_FLAGS=$(addprefix -l,$(LIBS))
VPATH=$(SRC_DIR)

.phony: $(TARGET) clean re

all: tests

$(TARGET): $(OBJS) $(INC_DIRS)/ui.h
	@ar rcs $@ $(OBJS)

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIRS)/ui.h |$(OBJ_DIR)
	@$(COMPILE.c) $(OUTPUT_OPTIONS) -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJS) $(TARGET)

tests: $(TARGET)
	$(CC) -g $(INC_FLAGS) tests/windows_demo.c -o windows_demo -L . -lui -lSDL2 -lSDL2_image

clean_tests:
	rm windows_demo

re: clean $(TARGET)
