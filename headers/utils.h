#ifndef __UTILS_H__
#define __UTILS_H__

#define CLEAR 0
#define MEMORY_ERROR -1000

#include <stdlib.h>
#include <stdio.h>

extern unsigned int __FLAG_MEMORY_ERROR__;

void cfree(void* ptr);

#endif