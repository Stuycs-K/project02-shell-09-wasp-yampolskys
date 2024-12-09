[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell

**Group members:** Patrick Was, Stella Yampolsky

**Team name:** InterSTELLAr WASPs

**Features:** 

Our shell implements all the required features, as well as shortening the path prompt and coloring it. 

**Reportable bugs:**
+ When using **echo** with quotation marks, the quotation marks are kept in the output. So, 
> echo abc hey mr k

will produce abc hey mr k, and 

> echo "abc hey mr k"

will produce "abc hey mr k"

**Function headers:** 

> void displayPath();

> char* readstdin();

> void cd(char* path);

> void execPipes(char* cmd);

> void execComm(char* cmd);

> void parse_args( char * line, char ** arg_ary );

> void redirect(int fd1, int fd2);

> int main()
