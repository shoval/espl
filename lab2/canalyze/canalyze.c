
#include <stdio.h>
#include <string.h>
#include "namelist.h"

#define LINELEN 128

int sortcomp(const struct namestat *p1, const struct namestat *p2) {
  //printf("%s ? %s\n", p1->name, p2->name);
  return strcmp(p1->name, p2->name);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Insufficient arguments\n");
    return 0;
  }
  
  namelist nl = make_namelist();
  int i;

  for (i=1; i<argc; ++i) {
    FILE* f1;
    int j;
    
    f1 = fopen(argv[i], "r");
    if (f1 == NULL) {
      printf("Unable to read file %s\n", argv[i]);
      return 0;
    }

    char line[LINELEN];
    for (j=0; j<LINELEN; ++j) {
      line[j] = 0;
    }
    int count = 0;
    char word[LINELEN] = "";
    while (fgets(line, LINELEN, f1)) {
      ++count;
      for (j=0; j<LINELEN; ++j) {
        char c = line[j];
        
        if (isalpha(c) || isdigit(c)) {
          int len = strlen(word);
          word[len] = c;
          word[len+1] = '\0';
        } else if (strlen(word) > 0) {
          if (!isdigit(word[0]) && !isres(word)) {
            add_name(nl, word);
          }
          word[0] = '\0';
        }
        
      }
      for (j=0; j<LINELEN; ++j) {
        line[j] = 0;
      }
    }
  }
  
  //sort names
  qsort(nl->names, nl->size, sizeof(nl->names[0]), sortcomp);
  
  // print names
  for(i = 0; i!=nl->size; ++i) {
    printf("%i: %s\n", nl->names[i].count, nl->names[i].name);
  }
  
  return 0;
}

int isres(char* word) {
  char* res[] = {"auto", "double", "int", "long", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};
  int i = 0;
  while (res[i]) {
    if (strcmp(word, res[i]) == 0) {
      return 1;
    }
    ++i;
  }
  return 0;
}








