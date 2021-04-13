#Work title
TARGET=guimp

#Directories
OBJ_DIR=obj
SRC_DIR=src
LIBUI_DIR=libui/
INC_DIRS=inc/ libui/inc/
LIB_DIRS=$(LIBUI_DIR)

#Compilation related indications
CC=clang
CFLAGS=-Wall -Wextra -Werror
LIBS=m ui#m stands for mathlib

#From there we use the info to compile everything.
SRC_FILE_NAMES = main.c
SOURCES=$(addprefix $(SRC_DIR)/, $(SRC_FILE_NAMES))
OBJS:=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC_FLAGS=$(addprefix -I,$(INC_DIRS))
LIBIDR_FLAGS=$(addprefix -L,$(LIB_DIRS))
CFLAGS+=$(INC_FLAGS)
LIBS_FLAGS=$(addprefix -l,$(LIBS))
VPATH=$(SRC_DIR)

.phony: $(TARGET) clean re

$(TARGET): $(OBJS) inc/guimp.h
	@make -j -C $(LIBUI_DIR)
	@$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBIDR_FLAGS) $(LIBS_FLAGS)
	@echo "Compilation succeeded."

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c inc/guimp.h |$(OBJ_DIR)
	@$(COMPILE.c) $(OUTPUT_OPTIONS) -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJS) $(TARGET)

re: clean $(TARGET)
