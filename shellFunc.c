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
  
  pid_t child = fork();
  if(child == 0){
    if(execvp(args[0], args) == -1){
      perror("execvp not working? That's quite annoying");
      exit(1);
    }
  }
  else{
    wait(NULL);
  }

}
