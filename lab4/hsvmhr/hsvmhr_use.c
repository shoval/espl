#include <stdio.h>

int hsvmhr(char *arg1, char *arg2);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Insufficient arguments (needs 2)\n");
    return 0;
  }
  
  printf("hsvmhr returns: %i\n", hsvmhr(argv[1], argv[2]));
  
  return 0;
}
