#include <stdlib.h>
#include <stdio.h>
#include "font.h"

void prsym(int idx) {
	int iline;
	char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idx];
	for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline)
		printf("%s\n", (*symbol)[iline]);
}

void prsymWord(int idxes[]) {
	int idx;
	for(idx = 0;; ++idx) {
				if(!idxes[idx])
					break;
				printf("%i : %i\n", idx, idxes[idx]);
			}
	/*
	int iline;
	for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline) {
		int i;
		for (i=0; i < sizeof(idxes); ++i) {
		  char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idxes[i]];
		  printf("%s", (*symbol)[iline]);
		}
	}
	*/
}


int main(int argc, char **argv) {
	/*
	char bla = argv[1][0];
	int bli = bla - 32;
	printf("%i\n", bli);
	*/
	int numbers[] = {1, 2, 3, 4, 5};
	//printf("%i\n", numbers[1]);
	prsymWord(numbers);
	return 0;
}
