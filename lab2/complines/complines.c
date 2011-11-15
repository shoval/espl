
#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE* f1;
  FILE* f2;
  const int len = 128;

  if (argc != 3) {
    printf("Insufficient arguments\n");
  } else {
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");

    if (f1 == NULL || f2 == NULL) {
      printf("Unable to read files\n");
      return 0;
    }

    char str1[len];
    char str2[len];
    int i;
    for (i=0; i<len; ++i) {
      str1[i] = 0;
      str2[i] = 0;
    }
    int count = 0;
    while (fgets(str1, 128, f1) && fgets(str2, 128, f2)) {
      ++count;
      for (i=0; i<len; ++i) {
        if ((str1[i] || str2[i]) && str1[i] != str2[i]) {
          //printf("%i: failed on %i\n", count, i);
          printf("-%i: %s", count, str1);
          printf("+%i: %s", count, str2);
          break;
        }
      }
      for (i=0; i<len; ++i) {
        str1[i] = 0;
        str2[i] = 0;
      }
    }
  }
  return 0;
}


