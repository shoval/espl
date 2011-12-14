#include <stdlib.h>
#include <stdio.h>
#include "font.h"

void prsym(int idx) {
	int iline;
	char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idx];
	for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline)
		printf("%s\n", (*symbol)[iline]);
}

void prsymwrd(char* word) {
  int iline;
  for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline) {
	char* tword = word;
	while (*tword != '\0') {
	  int idx = *tword - 32;
	  char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idx];
	  printf("%s", (*symbol)[iline]);
	  ++tword;
	}
	printf("\n");
  }
}

int main(int argc, char **argv) {
  if (argc == 2) {
	prsymwrd(argv[1]);
  } else {
	printf("Invalid arguments (expecting 1)\n");
  }
  return 0;
}
