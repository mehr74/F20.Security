#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// gcc bufoverflow.c -O0 -no-pie -fno-stack-protector -o bufoverflow

void read_input()
{

  char buf[120] = {0};
  unsigned int read_bytes = 0;

  puts("Hi! Please provide input.");

  while (read_bytes < 120)
  {
    // make sure that no more than 120 bytes are read to prevent buffer overflow
    unsigned int val = read(0, (buf + read_bytes), 120);
    read_bytes += val;
    printf("Input provided. It was \"%s\".\n", buf);
  }

  return; //nothing can ever go wrong here
}

void secret_function()
{
  puts("Secret function found!");
  execl("/bin/sh", "sh", NULL);
}

int main(void)
{
  // disable buffering for standard streams
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  read_input();
  //TODO: do something with the input
  return 0;
}
