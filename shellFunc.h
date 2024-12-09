#ifndef SHELLFUNC_H
#define SHELLFUNC_H
void displayPath();
char* readstdin();
void cd(char* path);
void execComm(char* cmd);
void parse_args( char * line, char ** arg_ary );
void redirect(int fd1, int fd2);
#endif
