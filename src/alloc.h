#include <stdlib.h>

#define         malloc                          "malloc disabled"
#define         MALLOC(size, type)              alloc( (size) * sizeof(type) )

extern void* alloc(size_t size);
