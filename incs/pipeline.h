#ifndef ABBOSHELL_H
#define ABBOSHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils.h"

char** readLine();
void execLine(char** args);

#endif
