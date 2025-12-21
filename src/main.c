#include "pipeline.h"
 


int main(){
  
  char** args;

  while(true){
    printf("shell > ");
    args = readLine();
    execLine(args);
  }
  

  return 0;
}

