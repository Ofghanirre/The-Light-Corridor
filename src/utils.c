#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h> // pour STDOUT_FILENO

unsigned int __FLAG_MEMORY_ERROR__ = 0;

#define STANDARD_LOG_FILE stdout
int enable_log = 0;
const char * _path = NULL;

void set_logging_file(const char * path) {
    _path = path;
    FILE * f = fopen(_path, "w");
    fclose(f);
}

void set_logging() {
    enable_log = 1;
}

void free_logging_file() {
}

int print_log(const char * format, ...) {
    if (enable_log == 0) {
        return -1;
    }
    va_list args;
    va_start(args, format);
    int result = 0;
    if (_path == NULL) {
        result = vfprintf(STANDARD_LOG_FILE, format, args);
    } else {
        FILE * file = fopen(_path, "a");
        if (file == NULL) { 
            fprintf(STANDARD_LOG_FILE, "Could not open logging file : %s\n", _path); 
            result = 0;
        }
        else {
            vfprintf(file, format, args);
            fclose(file);
        }
    }

    va_end(args);
    return result;
}
