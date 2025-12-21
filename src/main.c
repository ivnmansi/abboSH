#include "pipeline.h"
 
int main(){
  
  char** args;
  char* prompt;

  while(1){
    prompt = getPrompt();
    printf("%s", prompt);
    free(prompt);
    args = readLine();
    execLine(args);
    free(args);
  }
  return 0;
}

