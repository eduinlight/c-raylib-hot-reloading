#pragma once

#include "color.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
  Font fira_code;
} GameContext;

void *start_game(void);
bool should_exit(void);
void update(void *);
void render(void *);
