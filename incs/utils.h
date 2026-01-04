#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void formatBuffer(char* buffer, ssize_t buffer_len);
char** splitBuffer(char* buffer);
void removeArg(char** args, int position);
void freeArgs(char** args);

#endif
