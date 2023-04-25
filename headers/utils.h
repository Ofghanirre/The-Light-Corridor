#ifndef __UTILS_H__
#define __UTILS_H__

#define CLEAR 0
#define MEMORY_ERROR -1000

#include <stdlib.h>

void cfree(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

#endif