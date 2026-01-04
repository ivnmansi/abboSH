#include "pipeline.h"
 
int main(){
  char** args;
  char* prompt;

  execFile(".ash");

  while(1){
    prompt = getPrompt();
    printf("%s", prompt);
    free(prompt);
    args = readLine();
    execLine(args);
    freeArgs(args);
  }
  return 0;
}

