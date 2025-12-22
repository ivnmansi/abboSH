#ifndef BUILTIT_H
#define BUILTIT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"

int changeDirectory(char** args);
int exitShell(char** args);
int printHelp();
int printWelcome(char** args);

void reOut(char** args);
void reIn(char** args);

int execPipes(char** args);
#endif

