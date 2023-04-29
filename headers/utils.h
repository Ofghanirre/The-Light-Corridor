#ifndef __UTILS_H__
#define __UTILS_H__

#define CLEAR 0
#define MEMORY_ERROR -1000

#include <stdlib.h>
#include <stdio.h>

extern unsigned int __FLAG_MEMORY_ERROR__;
extern FILE * log_file;

void set_logging_file(const char * path);
void set_logging();
void free_logging_file();

int print_log(const char * format, ...);

#endif