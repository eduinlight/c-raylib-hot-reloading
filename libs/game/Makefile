SHELL=/bin/bash

LIB_NAME=game

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -fPIC
# Libs
# CFLAGS += -lraylib
# Defines
CFLAGS += -D_XOPEN_SOURCE=500
# Environments
CFLAGS_DEBUG = -g
CFLAGS_RELEASE = -O3

# Directories
SRC_DIR = src
LIB_DIR = lib
DEBUG_DIR = $(LIB_DIR)/debug
RELEASE_DIR = $(LIB_DIR)/release
OBJ_DIR = .obj

# Target executable name
TARGET_DEBUG = $(DEBUG_DIR)/lib${LIB_NAME}.so
TARGET_RELEASE = $(RELEASE_DIR)/lib${LIB_NAME}.so

# Find all .c files in the src directory
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Convert .c source files to .o object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: debug

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(TARGET_DEBUG)

release: CFLAGS += $(CFLAGS_RELEASE)
release: $(TARGET_RELEASE)

$(TARGET_DEBUG): $(OBJS)
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJS)

$(TARGET_RELEASE): $(OBJS)
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)

.PHONY: all clean release debug

