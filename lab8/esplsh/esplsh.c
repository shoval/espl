#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_LEN 1024
static char command[BUF_LEN+1];
static int argc;
static char *argv[BUF_LEN+1];

/* read command and remove end of line if present */
int read_command() {
  int len;

  if(fgets(command, BUF_LEN, stdin)) {
    len = strlen(command);
    if(len>0 && command[len-1]=='\n')
      command[len-1] = '\0';
    return 1;
  } 
  
  return 0;
}

#define NO_SEP '\0'
#define EOC '\1'

/* split the command line into arguments and fill argv with pointers
   to the arguments */
void split_command() {
  char *s, sep;
  int between;

  between = 1;
  argc = 0;
  sep = NO_SEP;
  for(s = command; *s; ++s) {
    switch(*s) {
    case '\"': case '\'':
      if(sep==NO_SEP) {
        sep = *s;
      } else if(sep==*s) {
        sep = '\0';
      } 
      break;
    case '\\':
      ++s;
      break;
    case ' ':
      if(!sep) {
        between = 1;
        *s = '\0';
        continue;
      }
      break;
    }
    if(between) {
      argv[argc++] = s;
      between = 0;
    }
  }
  argv[argc] = NULL;
}

/* expand arguments, substitute shell variable values etc. */
void expand_args() {
  char **a = argv;
  while(*a) {
    if(**a=='"' || **a=='\'') { /* TODO: quotes can be in any place */
      *a = strdup(*a);
      memmove(*a, *a+1, strlen(*a));
      (*a)[strlen(*a)-1] = 0;
    } else {
      *a = strdup(*a);
    }
    /* TODO: eliminate escapes \ */
    /* TODO: expand environment variables */
    ++a;
  }
}

/* free arguments allocated during expansion */
void free_args() {
  char **a = argv;
  while(*a) {
    free(*a);
    ++a;
  }
}

/* run an external program */
void run_program() {
  int pid, status, inout[2], status2;
  static char ststr[8];
	
	// for pipe
	char command2[BUF_LEN+1];
	int argc2 = 0;
	char *argv2[BUF_LEN+1];
	static char ststr2[8];
	
	inout[0] = 0;
	inout[1] = 1;
	if (argc >= 3) { 
		char* filename;
		if (!strcmp(argv[argc-2], ">")) { //write to file
			filename = argv[argc-1];
			argv[argc-2] = 0;
			inout[1] = open(filename, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
			if (inout[1] == -1) {
				printf("error writing to file %s\n", filename);
				return;
			}
			//printf("write to %s. fp=%i\n", filename, inout[1]);
		} else if (!strcmp(argv[argc-2], "<")) { //read from file
			filename = argv[argc-1];
			argv[argc-2] = 0;
			inout[0] = open(filename, O_RDONLY, S_IRWXU);
			if (inout[1] == -1) {
				printf("error reading from file %s\n", filename);
				return;
			}
			//printf("read from %s\n", filename);
		} else {
			int i;
			for (i=0; i<argc-1; ++i) {
				if (!strcmp(argv[i], "|")) {
					//printf("pipe found in %i\n", i);
					strcpy(command2, argv[i+1]);
					for (argc2=0; argc2<argc-i-1; ++argc2) {
						argv2[argc2] = argv[argc2+i+1];
					}
					argv2[argc2] = 0;
					argv[i] = 0;
					if(pipe(inout) == -1) {
						perror("pipe call error");
						return;
					}
					break;
				}
			}
		}
	}
	
	//test
	/*
	int j = 0;
	while (j < argc2) {
		printf("%s ", argv2[j]);
		++j;
	}
	printf("\n");
	*/

  /* TODO: input, output redirection */
  /* TODO: pipelines */
  /* TODO: background commands */

	pid=fork();
  if(pid==0) { // first child
		printf("in first child");
		if (argc2 == 0) {
			dup2(inout[0], 0);
		} else {
			close(inout[0]);
		}
		dup2(inout[1], 1);
		execvp(argv[0], argv);
		perror(argv[0]);
  } else if(pid > 0) { // parent
		printf("first child is: %i\n", pid);
		if (argc2 > 0) { 
			int pid2=fork();
			if (pid2==0) { // second child
				printf("in second child");
				close(inout[1]);
				dup2(inout[0], 0);
				execvp(argv2[0], argv2);
				perror(argv2[0]);
			} else if (pid2>0) { // still parent
				printf("second child is: %i\n", pid2);
				waitpid(pid2, &status2, 0);
				sprintf(ststr2, "%d", status2);
				setenv("?", ststr2, 1);
			} else {
				perror(getenv("SHELL")); /* problem while forking, not due to a particular program */
			}
		} else {
			waitpid(pid, &status, 0);
			sprintf(ststr, "%d", status);
			setenv("?", ststr, 1);
		}
  } else {
    perror(getenv("SHELL")); /* problem while forking, not due to a particular program */
  }
}

int main(int _argc, char **_argv) {
  /* clear shell variables and  re-assign a minimum set */
  clearenv();
  setenv("PATH", ":/bin:/usr/bin", 1);
  setenv("PROMPT", "$ ", 1);
  setenv("SHELL", _argv[0], 1);

  signal(SIGINT, SIG_IGN); /* ignore ^C */

  while(1) {
    printf("%s", getenv("PROMPT"));
    if(!read_command())
      break;
    split_command();
    if(!argc)
      continue;
    expand_args();
    /* process builtin commands */
    if(!strcmp(argv[0],"exit")) {
      break;
    } else if(!strcmp(argv[0],"set")) {
      if(argc!=3) {
        fprintf(stderr, "set: two arguments required\n");
        continue;
      }
      setenv(argv[1], argv[2], 1);
    } else if(!strcmp(argv[0], "cd")) {
      if(argc!=2) {
        fprintf(stderr, "cd: one argument required\n");
        continue;
      }
      if(chdir(argv[1])==-1) {
        perror("cd");
      }
    } else if(!strcmp(argv[0], "pwd")) {
      if(argc!=1) {
        fprintf(stderr, "pwd: no arguments allowed\n");
        continue;
      }
      printf("%s\n", getcwd(command, BUF_LEN));
    } else {
      /* run external command */
      run_program();
    }
    free_args();
  }
  printf("\n");

  return 0;
}
    

    
