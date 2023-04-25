#include "utils.h"

unsigned int __FLAG_MEMORY_ERROR__ = 0;

void cfree(void* ptr)
{
    if (ptr != NULL) {
        free(ptr);
    }
}