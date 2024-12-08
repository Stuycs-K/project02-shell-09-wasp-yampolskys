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

