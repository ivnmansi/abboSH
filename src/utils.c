#include "utils.h"

void formatBuffer(char* buffer, ssize_t buffer_len){
  if(buffer_len < 1){
    return;
  }
  buffer[buffer_len -1] = '\0';
}

/**
* @brief Splits a string into an array of words
* @param buffer String
*/
char** splitBuffer(char* buffer){
  int i=0;
  char** splitedBuffer = NULL;

  char* token = strtok(buffer, "\t\r\n\a ");
  while(token != NULL){
    i++;
    char** temp = realloc(splitedBuffer, (i+1)*sizeof(char*));
    splitedBuffer = temp;

    splitedBuffer[i-1] = strdup(token);
    splitedBuffer[i] = NULL;

    token = strtok(NULL, " \t\r\n\a");
  }
  return splitedBuffer;
}


void removeArg(char** args, int position){
  int i = position;
  while(args[i+1] != NULL){
    args[i] = args[i+1];
    i++;
  }
  args[i] = NULL;
}

void freeArgs(char** args){
  for(int i=0;args[i]!=NULL;i++){
    free(args[i]);
  }
  free(args);
}
