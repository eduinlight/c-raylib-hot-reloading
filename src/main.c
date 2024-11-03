#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "watch.h"

#define LIBGAME_FILENAME "./libs/game/lib/debug/libgame.so"
#define WAIT_FOR_LIB_TO_BE_READY 100000 // 100ms

pthread_mutex_t main_mutex = PTHREAD_MUTEX_INITIALIZER;
void lock_main_mutex() { pthread_mutex_lock(&main_mutex); }
void unlock_main_mutex() { pthread_mutex_unlock(&main_mutex); }

void *(*start_game)(void);
void (*render)(void *);
void (*update)(void *);
bool (*should_exit)(void);

void dl_load_function(void *handle, const char *fun_name, void **fun_ptr) {
  dlerror();

  *fun_ptr = dlsym(handle, fun_name);

  char *error = dlerror();
  if (error) {
    fprintf(stderr, "Error finding symbol: %s\n", error);
  }
}

void refresh_lib() {
  lock_main_mutex();
  static void *libgame_handle = NULL;

  if (libgame_handle != NULL) {
    dlclose(libgame_handle);
  }

  printf("Loading library: %s\n", LIBGAME_FILENAME);
  while ((libgame_handle = dlopen(LIBGAME_FILENAME, RTLD_LAZY)) == NULL) {
    fprintf(stderr, "Error loading library: %s\n", dlerror());
    usleep(WAIT_FOR_LIB_TO_BE_READY);
  }

  dl_load_function(libgame_handle, "start_game", (void **)(&start_game));
  dl_load_function(libgame_handle, "should_exit", (void **)(&should_exit));
  dl_load_function(libgame_handle, "update", (void **)(&update));
  dl_load_function(libgame_handle, "render", (void **)(&render));

  unlock_main_mutex();
}

void *watch_file_changes_thread() {
  watch_file_changes(LIBGAME_FILENAME, refresh_lib);
  return NULL;
}

void *game_loop_thread() {
  void *context = start_game();
  while (true) {
    lock_main_mutex();
    if (should_exit()) {
      unlock_main_mutex();
      break;
    }
    update(context);
    render(context);
    unlock_main_mutex();
    usleep(0);
  }
  return NULL;
}

int main() {
  refresh_lib();

  pthread_t refresh_thread;
  if (pthread_create(&refresh_thread, NULL, watch_file_changes_thread, NULL) !=
      0) {
    perror("Error initiating watch thread");
    return EXIT_FAILURE;
  }

  pthread_t game_thread;
  if (pthread_create(&game_thread, NULL, game_loop_thread, NULL) != 0) {
    perror("Error initiating game thread");
    return EXIT_FAILURE;
  }

  pthread_join(game_thread, NULL);

  return EXIT_SUCCESS;
}
