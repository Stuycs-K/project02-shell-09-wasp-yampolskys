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
#include "cd.h"

int main(){
  char* args[256];
  char line[256];
  while(1){
    
    // checks the path again and again! Super duper cool
    char path[256];
    if(getcwd(path, sizeof(path)) != NULL){
      printf("\e[1;38;2;0;200;0m%s:\e[0m $ ", path);
    }
    else{
      perror("error with getting path\n");
      exit(1);
    }

    while(fgets(line, 256, stdin)){
      if(feof(stdin)) {
        printf("\n");
        exit(0);
      }
      if(strncmp(line,"exit", 4) == 0){
        exit(0);
      }
      if(strncmp(line,"cd",2) == 0){
        parse_args(line, args);
        printf("%s\n", args[1]);
        cd(args[1]);
      }

      // extra newline
      if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
      }

      // execvp() and wait(), as well as parsing for ";" here
      char lineCop[256];
      strcpy(lineCop, line);
      char* lineCopy = lineCop;
      char* token;
      while((token = strsep(&lineCopy, ";")) != NULL){
        printf("%s\n", token);
        parse_args(token, args);
        pid_t child = fork();
        if(child == 0){
          if(execvp(args[0], args) == -1){
            perror("something happened :(");
            exit(1);
          }
        } else {
          int status;
          waitpid(child, &status, 0);
        }
      }

      printf("\e[1;38;2;0;200;0m%s:\e[0m: $ ", path);
    }
  }
    
    return 0;
}

// some bugs: "echo" does not get rid of quotation marks
