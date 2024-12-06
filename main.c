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
  char* args[256];
  char line[256];
  while(1){
    
    // checks the path again and again! Super duper cool
    char path[256];
    if(getcwd(path, sizeof(path)) != NULL){
      printf("%s: $ ", path);
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

      // extra newline
      if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
      }

      parse_args(line, args);
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
      printf("%s: $ ", path);
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
