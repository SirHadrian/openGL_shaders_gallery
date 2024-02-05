#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#define ERROR_N_DIE(errno, msg) \
        do { \
                fprintf(stderr, "ERROR: %s:%d - %s | %s\n", __FILE__, __LINE__, \
                                strerror(errno), msg); \
                exit(EXIT_FAILURE); \
        } while(0)

#define ALLOW_UNUSED __attribute__((unused))
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef enum { False = 0, True = 1 } Bool;

typedef unsigned int        uint;
typedef unsigned long int   ulint;
typedef unsigned char       uchar;

#endif /* UTILS_H */
