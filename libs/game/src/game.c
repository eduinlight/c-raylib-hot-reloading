#include "game.h"
#include <raylib.h>
#include <stdint.h>

void update(void *ctx) {
  if (IsKeyPressed(KEY_A)) {
    printf("A was pressed: \n");
  }
}

void render(void *ctx) {
  GameContext context = *(GameContext *)ctx;
  BeginDrawing();

  ClearBackground(BLACK);
  const char *text = "Hi, welcome to raylib";
  const uint32_t font_size = 50;
  const uint32_t spacing = 2;
  Vector2 text_size =
      MeasureTextEx(context.fira_code, text, font_size, spacing);
  const uint32_t x = GetScreenWidth() * 0.5 - text_size.x * 0.5;
  const uint32_t y = GetScreenHeight() * 0.5 - text_size.y * 0.5;
  DrawTextEx(context.fira_code, text, (Vector2){.x = x, .y = y}, font_size,
             spacing, WHITE);

  EndDrawing();
}

bool should_exit(void) { return WindowShouldClose(); }

void *start_game(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Init");
  SetWindowState(FLAG_WINDOW_RESIZABLE);

  GameContext *context = malloc(sizeof(GameContext));
  context->fira_code = LoadFont("/usr/share/fonts/TTF/FiraCode-Regular.ttf");
  return context;
}
