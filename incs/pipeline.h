#ifndef ABBOSHELL_H
#define ABBOSHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "utils.h"
#include "builtin.h"
#include "colors.h"

char* getPrompt();
char** readLine();
int execBuiltIn(char** args);
void execFork(char** args);
void execLine(char** args);

#endif
