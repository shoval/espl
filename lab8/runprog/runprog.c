#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSGSIZE 1

int main(int argc, char *argv[]) {
	int shownums, opt, p[2], j, pid, prevnew;
	char inbuf[MSGSIZE];

	shownums = 0;
	if (argc > 1 && strcmp(argv[1], "-n") == 0) {
		shownums = 1;
		++argv;
		--argc;
	}

	j = 1;
	while (j < argc) {
		printf("%s ", argv[j]);
		++j;
	}
	printf("\n");

	/* open pipe */

	if(pipe(p) == -1)
	{
		perror("pipe call error");
		return 1;
	}

	switch(pid = fork()){
	case -1: perror("error: fork call");
		return 2;

	case 0: /* if child then write down pipe */
		close(p[0]); /* first close the read end of the pipe */
		dup2(p[1], 1);
		++argv;
		execvp(argv[0], argv);
		break;
	default:  /* parent reads pipe */
		close(p[1]); /* first close the write end of the pipe*/
		j = 0;
		prevnew = 1;
		while(read(p[0], inbuf, MSGSIZE)) {
			if (shownums && prevnew) {
				prevnew = 0;
				printf(" %i: ", ++j);
			}
			printf("%s", inbuf);
			if (shownums && inbuf[0] == '\n') {
				prevnew = 1;
			}
		}
		int exval = 0;
		waitpid(pid, &exval, 0);
		printf("exit: %i\n", WEXITSTATUS(exval));
	}

	return 0;
}


