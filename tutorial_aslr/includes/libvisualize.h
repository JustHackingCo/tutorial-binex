#ifndef LIBVISUALIZE_H
#define LIBVISUALIZE_H

// Color definitions
#define COLOR_RED       "\x1b[31m"
#define COLOR_GREEN     "\x1b[32m"
#define COLOR_BLUE      "\x1b[34m"
#define COLOR_YELLOW    "\x1b[33m"
#define COLOR_RESET     "\x1b[0m"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t *canary = NULL;

void visualize_stack();

#endif
