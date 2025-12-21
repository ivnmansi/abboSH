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
