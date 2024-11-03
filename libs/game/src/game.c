#include "game.h"
#include <raylib.h>
#include <stdlib.h>

GameContext context;

ColorExtended color = {.color = {.r = 0, .g = 255, .b = 255, .a = 255}};

void update(void *ctx) {
  GameContext context = *(GameContext *)ctx;
  color.bits = (color.bits + 1) % (1 << 24);
  color.color.a = 255;
  if (IsKeyPressed(KEY_A)) {
    printf("A was pressed: \n");
  }
}

void render(void *ctx) {
  GameContext context = *(GameContext *)ctx;
  BeginDrawing();

  ClearBackground(RED);
  DrawTextEx(context.fira_code, "4", (Vector2){190, 200}, 50, 550,
             DARKBLUE);
  DrawLine(1, 1, 200, 200, DARKBLUE);
  DrawTexture(context.fira_code.texture, 0, 0, color.color);

  DrawFPS(0, 0);

  EndDrawing();
}

bool should_exit(void) { return WindowShouldClose(); }

void *start_game(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Init");

  SetTargetFPS(60);

  GameContext *context = malloc(sizeof(GameContext));
  context->fira_code = LoadFont("/usr/share/fonts/TTF/FiraCode-Regular.ttf");
  return context;
}
