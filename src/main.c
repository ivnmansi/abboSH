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
    for(int i=0; args[i] != NULL; i++){
      free(args[i]);
    }
    free(args);
  }
  return 0;
}

