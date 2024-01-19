#include "../include/logger.h"

void
LOG(char const * tag, char const * message)
{
   time_t now;

   time(&now);
   printf("%s [%s]: %s\n", ctime(&now), tag, message);
}
