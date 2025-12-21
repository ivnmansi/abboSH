#include "pipeline.h"
#include "utils.h"

char** readLine(){
  char* buffer = NULL;
  size_t buffer_size = 0;
  ssize_t buffer_len; 

  char** args;

  buffer_len = getline(&buffer,&buffer_size, stdin);
  
  if(buffer_len == -1){
    printf("ERROR");
    exit(EXIT_FAILURE);
  }
  
  formatBuffer(buffer, buffer_len);
  args = splitBuffer(buffer);
  free(buffer);

  return args;
}

void execLine(char** args){
  pid_t pid = fork();

  if(pid == 0){
    execvp(args[0], args);

    printf("Command not found\n");
    exit(EXIT_FAILURE);
  }
  else if(pid > 0){
    int status;
    waitpid(pid, &status, 0);

    if(WIFEXITED(status)){
      int exit_code = WEXITSTATUS(status);
      printf("[Process returned %d]\n",exit_code);
    }
    else if(WIFSIGNALED(status)){
      int signal_num = WTERMSIG(status);
      printf("[Terminated by signal %d]\n", signal_num);
    }
  }
}
