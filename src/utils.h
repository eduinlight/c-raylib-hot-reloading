#pragma once

#include <stdio.h>
#include <sys/inotify.h>

void print_inotify_event(const struct inotify_event *event);
