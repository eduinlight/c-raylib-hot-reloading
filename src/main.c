#include <raylib.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void init() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Init");

  SetTargetFPS(60);
}

void update() {
  if (IsKeyPressed(KEY_A)) {
    printf("Here: \n");
  }
}

void render() {
  BeginDrawing();

  ClearBackground(RAYWHITE);
  Font fira_code = LoadFont("/usr/share/fonts/TTF/FiraCode-Regular.ttf");
  DrawTextEx(fira_code, "Congrats! You created your first window!",
             (Vector2){190, 200}, 16, 0, DARKBLUE);
  DrawLine(1, 1, 100, 100, DARKBLUE);

  DrawFPS(0, 0);

  EndDrawing();
}

int main() {
  init();
  while (!WindowShouldClose()) {
    update();
    render();
  }

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
