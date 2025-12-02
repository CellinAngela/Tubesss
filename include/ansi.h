#ifndef ANSI_H
#define ANSI_H

#ifdef _WIN32
#include <windows.h>
#endif

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_WHITE "\x1b[37m"
#define COLOR_BRIGHT "\x1b[1m"

// Enable ANSI escape processing on Windows consoles (no-op on other platforms)
void enableAnsiColors();

#endif
