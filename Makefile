SHELL=/bin/bash

PROJECT_NAME=c-boilerplate

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c17
# Libs
CFLAGS += -lraylib
# Defines
CFLAGS += -D_XOPEN_SOURCE=500
# Environments
CFLAGS_DEBUG = -g
CFLAGS_RELEASE = -O3

# Directories
SRC_DIR = src
BIN_DIR = bin
DEBUG_DIR = $(BIN_DIR)/debug
RELEASE_DIR = $(BIN_DIR)/release
OBJ_DIR = .obj

# Target executable name
TARGET_DEBUG = $(DEBUG_DIR)/${PROJECT_NAME}
TARGET_RELEASE = $(RELEASE_DIR)/${PROJECT_NAME}

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
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(TARGET_RELEASE): $(OBJS)
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run:
	@${TARGET_DEBUG}

run-release:
	@${TARGET_RELEASE}

watch:
	@while inotifywait -e modify,create,delete ./libs/game/src/ ; do \
		cd ./libs/game/ && make; \
		cd ../../; \
	done

.PHONY: all clean release debug watch run-release run
