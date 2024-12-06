#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "cd.h"

int cd(char* path){
  printf("%s\n", path);
  if(chdir(path) == 0){
    return 0;
  }
  return 1;
}
