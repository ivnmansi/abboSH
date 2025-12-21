#include "builtin.h"

int changeDirectory(char** args){
  char* desDirectory;
  if(args[1] == NULL){
    desDirectory = getenv("HOME");
  }
  else {
    desDirectory = args[1];
  }

  if(chdir(desDirectory) != 0){
    perror("abboSH");
  }

  return 1;
}

int exitShell(char** args){
  free(args);
  printf("Bye bye!\n");
  exit(0);
}
