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

int main(){

  while(1){
    char* args[256];
    char line[256];
    
    // checks the path again and again! Super duper cool
    char path[256];
    if(getcwd(path, sizeof(path)) != NULL){
      printf("%s: $ ", path);
    }
    else{
      perror("error with getting path\n");
      exit(1);
    }

    while(fgets(line, 256, stdin) != NULL){
      if(getcwd(path, sizeof(path)) != NULL){
        printf("%s: $ ", path);
      }
      else{
        perror("error with getting path\n");
        exit(1);
      }
    }

    return 0;

  }


  /*while(fgets(line, 256, stdin) != NULL){
    printf("%s\n", line);
    parse_args(line, args);

    //pid_t child = fork(); holy crap this is the worst thing I have ever done
    if(child == -1){perror("I cannot make children"); exit(1);}
    execvp(args[0], args);
    printf("%s\n", line);
  }
  */
  return 0;
}
