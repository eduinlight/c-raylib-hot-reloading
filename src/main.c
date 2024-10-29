#include <dlfcn.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "color.c"
#include "rust.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

enum EFonts { FIRA_CODE };

typedef struct {
  Font fonts[1];
} Context;

Context init() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Init");

  SetTargetFPS(60);

  Context context = {
      .fonts = {LoadFont("/usr/share/fonts/TTF/FiraCode-Regular.ttf")}};
  return context;
}

ColorExtended color = {.bits = 0,
                       .color = {.r = 0, .g = 255, .b = 255, .a = 255}};

void update(const Context *context) {
  color.bits = (color.bits + 1) % (1 << 24);
  color.color.a = 255;
  if (IsKeyPressed(KEY_A)) {
    printf("Here: \n");
  }
}

void render(const Context *context) {
  BeginDrawing();

  ClearBackground(RAYWHITE);
  DrawTextEx(context->fonts[0], "Congrats! You created your first window!",
             (Vector2){190, 200}, 16, 0, DARKBLUE);
  DrawLine(1, 1, 100, 100, DARKBLUE);
  printf("r = %u, g = %u, b = %u, a = %u \n", color.color.r, color.color.g,
         color.color.b, color.color.a);
  DrawTexture(context->fonts[0].texture, 0, 0, color.color);

  DrawFPS(0, 0);

  EndDrawing();
}

typedef void (*fun_ptr)();

int main() {
  // Context context = init();
  // while (!WindowShouldClose()) {
  //   update(&context);
  //   render(&context);
  // }

  void *handle = dlopen("./libs/game/lib/debug/libgame.so", RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "Error loading library: %s\n", dlerror());
    return 1;
  }

  while (true) {
    // Clear any existing error
    dlerror();

    // Get the function pointer
    fun_ptr fun = (fun_ptr)dlsym(handle, "fun");
    char *error = dlerror();
    if (error) {
      fprintf(stderr, "Error finding symbol: %s\n", error);
      dlclose(handle);
      return 1;
    }

    // Call the function
    fun();

    sleep(1);

    system("cd ./libs/game && make > /dev/null");

    // Close the library
    dlclose(handle);

    // reopen lib
    handle = dlopen("./libs/game/lib/debug/libgame.so", RTLD_LAZY);
    if (!handle) {
      fprintf(stderr, "Error loading library: %s\n", dlerror());
      return 1;
    }
  }

  return EXIT_SUCCESS;
}
