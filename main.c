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
#include "redirect.h"
#include "cd.h"

int main(){
  char* args[256];
  char line[256];
  while(1){
    
    // checks the path again and again! Super duper cool
    //
    if(feof(stdin)){
      return 0;
    }

    char path[256];
    if(getcwd(path, sizeof(path)) != NULL){
      printf("\e[1;38;2;0;200;0m%s:\e[0m $ ", path);
    }
    else{
      perror("error with getting path\n");
      exit(1);
    }

    while(fgets(line, 256, stdin)){
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

      char* redirectIn = strchr(line, '<');
      char* redirectOut = strchr(line, '>');

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
            perror("redirect input file problem");
            continue;
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
            continue;
          }
        }

        
      }

      // execvp() and wait(), as well as parsing for ";" here
      char lineCop[256];
      strcpy(lineCop, line);
      char* lineCopy = lineCop;
      char* token;
      while((token = strsep(&lineCopy, ";")) != NULL){
        printf("%s\n", token);
        parse_args(token, args);
          int i = 0;
          while (args[i] != NULL) {
            if (strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0) {
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