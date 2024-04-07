#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"

#undef malloc

void*
alloc(size_t size)
{
        return malloc(size);
}
