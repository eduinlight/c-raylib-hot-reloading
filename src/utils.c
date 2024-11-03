#include "utils.h"

void print_inotify_event(const struct inotify_event *event) {
  printf("Event Details:\n");
  printf("  Watch Descriptor: %d\n", event->wd);
  printf("  Mask: %u\n", event->mask);
  printf("  Cookie: %u\n", event->cookie);
  printf("  Length: %u\n", event->len);

  if (event->len > 0 && event->name[0] != '\0') {
    printf("  Name: %s\n", event->name);
  }

  printf("  Event Type(s):\n");

  // Print event types based on the mask
  if (event->mask & IN_ACCESS)
    printf("    IN_ACCESS (File was accessed)\n");
  if (event->mask & IN_MODIFY)
    printf("    IN_MODIFY (File was modified)\n");
  if (event->mask & IN_ATTRIB)
    printf("    IN_ATTRIB (Metadata changed)\n");
  if (event->mask & IN_CLOSE_WRITE)
    printf("    IN_CLOSE_WRITE (File opened for writing was closed)\n");
  if (event->mask & IN_CLOSE_NOWRITE)
    printf("    IN_CLOSE_NOWRITE (File not opened for writing was closed)\n");
  if (event->mask & IN_OPEN)
    printf("    IN_OPEN (File was opened)\n");
  if (event->mask & IN_MOVED_FROM)
    printf("    IN_MOVED_FROM (File was moved from X)\n");
  if (event->mask & IN_MOVED_TO)
    printf("    IN_MOVED_TO (File was moved to X)\n");
  if (event->mask & IN_CREATE)
    printf("    IN_CREATE (File or directory was created)\n");
  if (event->mask & IN_DELETE)
    printf("    IN_DELETE (File or directory was deleted)\n");
  if (event->mask & IN_DELETE_SELF)
    printf("    IN_DELETE_SELF (Watched file or directory was deleted)\n");
  if (event->mask & IN_MOVE_SELF)
    printf("    IN_MOVE_SELF (Watched file or directory was moved)\n");
  if (event->mask & IN_UNMOUNT)
    printf("    IN_UNMOUNT (Filesystem containing the watched object was "
           "unmounted)\n");
  if (event->mask & IN_Q_OVERFLOW)
    printf("    IN_Q_OVERFLOW (Event queue overflowed)\n");
  if (event->mask & IN_IGNORED)
    printf("    IN_IGNORED (Watch was removed)\n");

  // Handle unknown or multiple events
  if (!(event->mask &
        (IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE | IN_CLOSE_NOWRITE |
         IN_OPEN | IN_MOVED_FROM | IN_MOVED_TO | IN_CREATE | IN_DELETE |
         IN_DELETE_SELF | IN_MOVE_SELF | IN_UNMOUNT | IN_Q_OVERFLOW |
         IN_IGNORED))) {
    printf("    UNKNOWN (Unknown event mask)\n");
  }
}
