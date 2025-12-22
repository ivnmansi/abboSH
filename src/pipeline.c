#define _GNU_SOURCE
#include "pipeline.h"

char* getPrompt(){
  char* working_directory = getcwd(NULL, 0);
  char host[HOST_NAME_MAX + 1];
  char* user = getenv("USER");
  char* prompt;

  gethostname(host, sizeof(host));

  asprintf(&prompt, B_MAGENTA"%s@%s %s > "RESET, user, host, working_directory);
  free(working_directory);

  return prompt;
}

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


int execBuiltIn(char** args){
  if(args[0] == NULL){
    return 0;
  } 

  if(strcmp(args[0], "cd") == 0){
    changeDirectory(args);
    return 1;
  }

  if(strcmp(args[0], "exit") == 0){
    exitShell(args);
    return 1;
  }

  // implementar el resto dsp

  return 0;
}

void execFork(char** args){
  pid_t pid = fork();

  if(pid == 0){
    reIn(args);
    reOut(args);
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

void execLine(char** args){
  if(!execBuiltIn(args)){
    if(!execPipes(args)){
      execFork(args);
    }
  }
}
