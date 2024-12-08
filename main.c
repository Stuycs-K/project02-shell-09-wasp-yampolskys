#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "parse.h"
//#include "cd.h"
//

void displayPath();
char* readstdin();
void cd(char* path);
void execComm(char* cmd);

int main(){
  char* line;
  char* token;
  
  while(1){
    
    displayPath();
    line = readstdin();

    // checks for end-of-file character/essentially making sure command + D works
    if(feof(stdin)){
      return 0;
    }

    // extra newline
    if(line[strlen(line)-1] == '\n'){
      line[strlen(line)-1] = '\0';
    }

    char lineCop[256];
    strcpy(lineCop, line);
    char* lineCopy = lineCop;
    while((token = strsep(&lineCopy, ";")) != NULL){
      execComm(token);
    }

  }

    return 0;
}


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


// some bugs: "echo" does not get rid of quotation marks
