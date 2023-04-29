#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h> // pour STDOUT_FILENO

unsigned int __FLAG_MEMORY_ERROR__ = 0;

#define STANDARD_LOG_FILE stdout
FILE * log_file = NULL;
int enable_log = 0;

void set_logging_file(const char * path) {
    log_file = fopen(path, "w");
    if (log_file == NULL) {
        log_file = NULL;
        return;
    }
}

void set_logging() {
    enable_log = 1;
}

void free_logging_file() {
    if (log_file != NULL) fclose(log_file);
}

int print_log(const char * format, ...) {
    if (enable_log == 0) return -1;
    va_list args;
    va_start(args, format);
    int result = vfprintf(log_file == NULL ? stdout : log_file, format, args);
    va_end(args);
    return result;
}
