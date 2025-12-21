#include "pipeline.h"
 


int main(int argc, char** argv){

  while(true){
    printf("shell > ");
    readLine();


  }
  

  return 0;
}

int readLine(){
  char* buffer = NULL;
  size_t buffer_size = 0;
  ssize_t buffer_len; 

  char** args;

  buffer_len = getline(&buffer,&buffer_size, stdin);
  
  if(buffer_len == -1){
    printf("ERROR");
    return 0;
  }
  
  formatBuffer(buffer, buffer_len);
  args = splitBuffer(buffer);
  free(buffer);

  

  return 0;
}
