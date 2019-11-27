#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int bar(char *arg, char *out)
{
  strcpy(out, arg);
  return 0;
}

int foo(char *arg)
{
  char buf1[400]="Welcome to ce40442 class.\n";
  char buf2[200];
  bar(arg, buf2);
  printf(buf1);
  
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    char *msg[]={
      "/bin/user/echo",
      "target5: argc != 2",
      0
    };
    execv(msg[0], msg);
  }
  foo(argv[1]);
  
  return 0;
}
