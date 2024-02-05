#include <stdio.h>
#include <time.h>

#include "logger.h"

char const *const tags[] = {
        "DEBUG",
        "INFO"
};

void LOG(char const *tag, char const *message)
{
        time_t now;
        time(&now);

        printf("%s [%s]: %s\n", ctime(&now), tag, message);
}
