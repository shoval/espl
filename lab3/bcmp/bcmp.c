
#include <stdio.h>
#define BUFFER_SIZE 1

int main(int argc, char *argv[]) {
  FILE* f1;
  FILE* f2;
  unsigned char buf1[BUFFER_SIZE];
  unsigned char buf2[BUFFER_SIZE];

  if (argc != 3) {
    printf("Insufficient arguments\n");
    return 0;
  }

  f1 = fopen(argv[1], "rb");
  f2 = fopen(argv[2], "rb");

  if (f1 == NULL || f2 == NULL) {
    printf("Unable to read files\n");
    return 0;
  }

  int count = 0;
  int found = 0;

  while(fread(buf1, BUFFER_SIZE, 1, f1)) {
    if (fread(buf2, BUFFER_SIZE, 1, f2)) {
      if (buf1[0] != buf2[0]) {
        found = 1;
        printf("byte %i -%i +%i\n", count, buf1[0], buf2[0]);
      }
    } else {
      break;
    }
    ++count;
  }

  fclose(f1);
  fclose(f2);
  return 0;
}
