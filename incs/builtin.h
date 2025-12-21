#ifndef BUILTIT_H
#define BUILTIT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int changeDirectory(char** args);
int exitShell(char** args);
int printHelp();
int printWelcome(char** args);

#endif

