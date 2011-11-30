#include <stdio.h>

int atodst(char* num) {
  int i = 0;
  int tot = 0;
  while (num[i] != '\0') {
    int temp = num[i] - '0';
    //printf("%c : %i\n", num[i], temp);
    tot = 10 * tot + temp;
    ++i;
  }
  return tot;
}
