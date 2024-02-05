#ifndef LOGGER_H
#define LOGGER_H

enum tag {
        DEBUG = 0,
        INFO
};

#ifdef DBG
#define D(msg) \
        do { \
                fprintf(stderr, "DEBUG: %s:%d | %s\n", __FILE__, __LINE__, msg); \
        } while(0)

#define Dzu(msg, i) \
        do { \
                fprintf(stderr, "DEBUG: %s:%d | %s: %zu\n", __FILE__, __LINE__, msg, i); \
        } while(0)
#else
#define D(x, y) \
        do {} while(0)

#define Dzu(x, y) \
        do {} while(0)
#endif

void LOG(char const *tag, char const *message);

#endif /* LOGGER_H */
