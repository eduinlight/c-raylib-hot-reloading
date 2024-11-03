#include "watch.h"

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUFFER_LEN ((EVENT_SIZE + 16) * 1024)

void watch_file_changes(void *libgame_filename, change_handler handler) {
  int32_t inotify_fd = inotify_init();
  if (inotify_fd < 0) {
    perror("Error initiating inotify");
    exit(EXIT_FAILURE);
  }

  uint32_t events_listening = IN_ATTRIB;
  while (true) {
    int32_t watch_descriptor = inotify_add_watch(
        inotify_fd, (char *)libgame_filename, events_listening);

    if (watch_descriptor < 0) {
      perror("Error adding a watcher for file");
      exit(EXIT_FAILURE);
    }

    printf("Watching for changes on file: %s\n", (char *)libgame_filename);

    // Buffer to store inotify events
    uint8_t buffer[BUFFER_LEN];

    // Event loop
    while (true) {
      int32_t length = read(inotify_fd, buffer, sizeof(buffer));
      if (length < 0) {
        perror("Error reading inotify");
        exit(EXIT_FAILURE);
      }

      for (int32_t i = 0; i < length;) {
        struct inotify_event event = *((struct inotify_event *)&buffer[i]);
        print_inotify_event(&event);
        if (event.mask & events_listening) {
          fprintf(stderr, "File %s modified\n", (char *)libgame_filename);
          handler();
          goto outer;
        }

        i += EVENT_SIZE + event.len;
      }
    }
  outer:
    // Clean up
    inotify_rm_watch(inotify_fd, watch_descriptor);
  }

  close(inotify_fd);
}
