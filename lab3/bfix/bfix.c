
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 1
#define LINELEN 128

int main(int argc, char *argv[]) {
  int help, showmsg, reverse, opt;
  int nsecs, tfnd;
  
  help = 0;
  showmsg = 0;
  reverse = 0;
  while ((opt = getopt(argc, argv, "hrm")) != -1) {
    switch (opt) {
      case 'h':
        help = 1;
        break;
      case 'r':
        reverse = 1;
        break;
      case 'm':
        showmsg = 1;
        break;
    }
  }
  
  if (help) {
    printf("  -h     give this help list\n  -r     reverse the differences\n  -m     print a message each time a change is applied\n");
    return 0;
  } else if (argc-optind < 2) {
    // files not specified
    printf("Insufficient arguments\n");
    return 0;
  }
  
  FILE* f1; // binary file
  FILE* f2; // differences file
  int j;

  f1 = fopen(argv[optind], "r+");
  f2 = fopen(argv[optind+1], "r");

  if (f1 == NULL || f2 == NULL) {
    printf("Unable to read files\n");
    return 0;
  }

  char line[LINELEN];
  for (j=0; j<LINELEN; ++j) {
    line[j] = 0;
  }
  
  int count = 0;
  char word[3][LINELEN] = {"ss", "ff", "hh"};
  word[0][0] = '\0';
  word[1][0] = '\0';
  word[2][0] = '\0';
  
  int wordc = 0;
  
  while (fgets(line, LINELEN, f2)) {
    ++count;
    //printf("%i: %s", count, line);
    for (j=0; j<LINELEN && wordc<3; ++j) {
      char c = line[j];
      
      if (isdigit(c)) {
        int len = strlen(word[wordc]);
        word[wordc][len] = c;
        word[wordc][len+1] = '\0';
      } else if (strlen(word[wordc]) > 0) {
        ++wordc;
      }
    }
    // word - 0:position, 1:should-be, 2:is
    //printf("%s, %s, %s\n", word[0], word[1], word[2]);
    long int pos = strtol(word[0], NULL, 10);
    char bshould = strtol(word[1], NULL, 10);
    char bis = strtol(word[2], NULL, 10);
    //printf("%li, %c, %c\n", pos, bshould, bis);
    
    if (reverse) {
      char temp = bshould;
      bshould = bis;
      bis = temp;
    }
    
    // make changes to the file
    char c;
    fseek(f1, pos, SEEK_SET);
    fread(&c, 1, 1, f1);
    //printf("found: %c\n", c);
    if ((int)c == (int)bis) { 
      // verify that the char about to be changed is as expected
      fseek(f1, pos, SEEK_SET);
      fwrite(&bshould, 1, 1, f1);
      printf("Replaced %i with %i at position %li\n", bis, bshould, pos);
    }
    //printf("\n");
    
    wordc = 0;
    word[0][0] = '\0';
    word[1][0] = '\0';
    word[2][0] = '\0';
    for (j=0; j<LINELEN; ++j) {
      line[j] = 0;
    }
  }

  fclose(f1);
  fclose(f2);
  return 0;
}
