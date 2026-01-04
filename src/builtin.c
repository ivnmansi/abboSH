#include "builtin.h"

/**
 * @brief Reads the config file and execs its lines
 * @param config_file Directory of the file to execs its lines
 */
void execFile(char* config_file){
  FILE* fp = fopen(config_file, "r");
  if(fp == NULL){
    return;
  }
  
  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  while((read = getline(&line,&len,fp))!=-1){
    formatBuffer(line, read);
    if(read<=1 || line[0] == '#'){
      continue;
    }

    char** args = splitBuffer(line);
    if(args[0] != NULL){
      execLine(args);
    }

    free(args);
  }
  free(line);
  fclose(fp);
}

/**
  * @brief Changes the current working directory
  * @param args Path of the destiny directory
*/
int changeDirectory(char** args){
  char* desDirectory;
  if(args[1] == NULL){
    desDirectory = getenv("HOME");
  }
  else {
    desDirectory = args[1];
  }

  if(chdir(desDirectory) != 0){
    perror("abboSH");
  }

  return 1;
}

/**
  * 
*/
int exitShell(char** args){
  freeArgs(args);
  printf("Bye bye!\n");
  exit(0);
}

void reOut(char** args){
  int i=0;
  while(args[i] != NULL){
    if(strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0){
      if(args[i+1] == NULL){
        printf("ERROR: No file to redirect\n");
        exit(EXIT_FAILURE);
      }
    
      char* file_name = args[i+1];
      int fd;

      if(strcmp(args[i], ">") == 0){
        fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      }
      else if(strcmp(args[i], ">>") == 0){
        fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
      }

      if(fd == -1){
        printf("Error opening file");
        exit(EXIT_FAILURE);
      }

      dup2(fd, STDOUT_FILENO);
      close(fd);
      
      removeArg(args,i);
      removeArg(args,i);
    }
    i++;
  }
}



void reIn(char** args){
  int i=0;
  while(args[i] != NULL){
    if(strcmp(args[i], "<") == 0 || strcmp(args[i], "<<") == 0){
      if(args[i+1] == NULL){
        printf("ERROR: No file to read\n");
        exit(EXIT_FAILURE);
      }
      
      char* file_name;

      if(strcmp(args[i],"<<") == 0){
        char* stop_word = args[i+1];
        file_name = ".tmp";

        int temp_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC,0644);

        char* line = NULL;
        size_t len = 0;
        ssize_t read;

        while(1){
          printf("heredoc> ");
          read = getline(&line, &len, stdin);
          
          if(strncmp(line, stop_word, strlen(stop_word)) == 0 && (read - 1) == strlen(stop_word)){
            break;
          }

          write(temp_fd,line,read);
        }
        free(line);
        close(temp_fd);
      }
      else if(strcmp(args[i],"<") == 0){
        file_name = args[i+1];
      }

      int fd = open(file_name, O_RDONLY);
      if(fd == -1){
        printf("ERROR: Could not open file");
        exit(EXIT_FAILURE);
      }

      dup2(fd, STDIN_FILENO);
      close(fd);

      if(strcmp(args[i], "<<") == 0){
        unlink(file_name);
      }

      removeArg(args, i);
      removeArg(args, i);
    }
    i++;
  }
}


int execPipes(char** args){
  int i = 0;
  while(args[i] != NULL){
    if((strcmp(args[i], "|") == 0) && args[i-1] != NULL && args[i+1] != NULL){
      args[i] = NULL;
      char** argsRight = &args[i+1];

      int fd[2];
      if(pipe(fd) == -1){
        printf("ERROR: Could not create pipe");
        return 0;
      }

      pid_t pid1 = fork();
      if(pid1 == 0){
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execvp(args[0], args);
        printf("ERROR: Could not exec left pipe");
        exit(EXIT_FAILURE);
      }

      pid_t pid2 = fork();
      if(pid2 == 0){
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        execvp(argsRight[0], argsRight);
        printf("ERROR: Could not exec right pipe");
        exit(EXIT_FAILURE);
      }

      close(fd[0]);
      close(fd[1]);

      waitpid(pid1, NULL, 0);
      waitpid(pid2, NULL, 0);

      return 1;
    }
    i++;
  }

  return 0;
}
