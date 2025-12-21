#include "pipeline.h"
 


int main(){
  
  char** args;
  char* prompt;

  while(true){
    prompt = getPrompt();
    printf("%s", prompt);
    free(prompt);
    args = readLine();
    execLine(args);
  }
  

  return 0;
}

