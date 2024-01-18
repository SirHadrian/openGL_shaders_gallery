#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

#define INFO      "INFO"
#define DEBUG     "DEBUG"

void LOG(char const * tag, char const * message);

#endif
