#include "builtin.h"

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

int exitShell(char** args){
  free(args);
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
      args[i] = NULL;
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

      args[i] = NULL;
    }
    i++;
  }
}
