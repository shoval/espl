#include <stdio.h>
 
int main (int argc, char *argv[])
{
  for (argc = argc-1; argc>0; argc--)
  {
    printf("%s ", argv[argc]);
  }
  printf("\n");
  return 0;
}