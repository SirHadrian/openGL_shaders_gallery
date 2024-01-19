#ifndef LOGGER_H
#define LOGGER_H

#define INFO      "INFO"
#define DEBUG     "DEBUG"

#ifdef DEBUG
#define D(msg) \
        do { \
                fprintf(stderr, "DEBUG: %s:%d - %s\n", __FILE__, __LINE__, msg); \
        } while(0)
#else
#define D(x) \
        do {} while(0)
#endif

void LOG(char const * tag, char const * message);

#endif /* LOGGER_H */
