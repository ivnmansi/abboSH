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
#include "jobs.h"
#include "colors.h"

char* getPrompt(void);
char** readLine(void);
int execBuiltIn(char** args);
void execFork(char** args, int isBackground, JobList* jobList);
void execLine(char** args, JobList* jobList);

#endif
