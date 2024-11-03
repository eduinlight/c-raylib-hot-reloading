#pragma once

#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

typedef void (*change_handler)();

void watch_file_changes(void *libgame_filename, change_handler handler);
