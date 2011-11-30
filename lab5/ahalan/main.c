void ahalan();
void write();

int main(int arg, char **argv) {
	ahalan();
	return 0;
}

int myputs(char *s) {
  write(1, s, length(s));
}

int length(char *s) {
  char *t = s;
  while(*t) ++t;
  return t-s;
}