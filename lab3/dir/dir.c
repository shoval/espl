
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
  int help, size, opt;

  help = 0;
  size = 0;
  while ((opt = getopt(argc, argv, "hl")) != -1) {
    switch (opt) {
      case 'h':
        help = 1;
        break;
      case 'l':
        size = 1;
        break;
    }
  }

  if (help) {
    printf("  -h     give this help list\n  -l     print file size in bytes before the file name.\n");
    return 0;
  } else if (argc-optind < 1) {
    // files not specified
    printf("Insufficient arguments\n");
    return 0;
  }

  DIR* dir; // binary file
  struct dirent* ent;

  dir = opendir(argv[optind]);
  if (dir == NULL) {
    printf("Unable to open directory\n");
    return 0;
  }

  while ((ent = readdir(dir)) != NULL) {
    if (ent->d_type == 8) {
      if (size) {
        struct stat sb;
        char path[513];
        path[0] = '\0';
        strcat(path, argv[optind]);
        strcat(path, "/");
        strcat(path, ent->d_name);
        if (lstat(path, &sb) == -1) {
          printf("???  ");
        } else {
          printf("%lld  ", (long long) sb.st_size);
        }
      }
      printf("%s\n", ent->d_name);
    }
  }

  closedir(dir);
  return 0;
}
