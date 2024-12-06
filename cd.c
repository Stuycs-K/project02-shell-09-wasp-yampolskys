#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "cd.h"

char* cd(char* path){
  char cwd[256];
  if(chdir(path) == 0){
    getcwd(cwd, sizeof(cwd));
    return cwd;
  }
  return NULL;
}
