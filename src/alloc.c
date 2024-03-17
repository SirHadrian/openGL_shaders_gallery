#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "alloc.h"
#include "utils.h"

#undef malloc

void*
alloc(size_t size)
{
        void *mem;

        mem = malloc(size);
        if (mem == NULL) {
                ERROR_N_DIE(errno, "");
                exit(1);
        }

        return mem;
}
