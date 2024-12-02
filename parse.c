#include <strings.h>

void parse_args( char * line, char ** arg_ary ){
  char* token; int i = 0;
  while((token = strsep(&line, " ")) != NULL){
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
  return; 
}

// I thik we need to add to this parse though to consider semicolons [;] and such
