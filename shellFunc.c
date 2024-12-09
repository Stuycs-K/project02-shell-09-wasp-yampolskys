#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "shellFunc.h"

void cd(char* path){
  if(chdir(path) != 0){
    perror("cd not working");
  }
}

char* readstdin(){
  char* line = malloc(256);
  
  if(fgets(line, 256, stdin) == NULL){
    free(line);
    return NULL;
  }

  return line;
}

void displayPath(){
  char cwd[1024];
  char* shorten = getenv("HOME");

  if(getcwd(cwd, sizeof(cwd)) != NULL){
    if(strncmp(cwd, shorten, strlen(shorten)) == 0){
      printf("\e[1;38;2;0;200;0m~%s:\e[0m $ ", cwd+strlen(shorten));
    }
    else{
      printf("\e[1;38;2;0;200;0m%s:\e[0m $ ", cwd);
    }
  }
}

void parse_args( char * line, char ** arg_ary ){
  char* token; int i = 0;
  while((token = strsep(&line, " ")) != NULL){
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
  return;
}


void redirect(int fd1, int fd2) {
    int backup = dup(fd2);
    dup2(fd1, fd2);
    close(fd1);
    close(backup);
}

void execComm(char* cmd){
  char* args[256];
  parse_args(cmd, args);

  if(strcmp(args[0], "cd") == 0){
    if(args[1] != NULL){
      cd(args[1]);
    }
    else{
      chdir(getenv("HOME"));
    }
    return;
  }

  if(strcmp(args[0], "exit") == 0){
    exit(0);
  }

  char* redirectIn = strchr(cmd, '<');
  char* redirectOut = strchr(cmd, '<');
  int fdIn = -1;
  int fdOut = -1;

  if(redirectIn != NULL || redirectOut != NULL){
    char* file = NULL;

    if(redirectIn != NULL){
      file = redirectIn + 1;
      while(*file == ' '){
        file++;
      }
      fdIn = open(file, O_RDONLY);
      if(fdIn == -1){
        perror("redirect input file probelm");
        exit(1);
      }
    }

    if(redirectOut != NULL){
      file = redirectOut + 1;
      while(*file == ' '){
        file++;
      }
      fdOut = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if(fdOut == -1){
        perror("redirect output file problem");
        exit(1);
      }
    }

  }

  int i = 0;
  while(args[i] != NULL){
    if(strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0){
      args[i] = NULL;
    }
    i++;
  }
  
  pid_t child = fork();
  if(child == 0){

    if(fdIn != -1){
      redirect(fdIn, STDIN_FILENO);
    }
    if(fdOut != -1){
      redirect(fdOut, STDOUT_FILENO);
    }

    if(execvp(args[0], args) == -1){
      perror("execvp not working? That's quite annoying");
      exit(1);
    }
  }
  else{
    wait(NULL);
  }

}
