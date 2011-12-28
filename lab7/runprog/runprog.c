#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int pid = fork();
	if (pid) {
		int exval = 0;
		waitpid(pid, &exval, 0);
		printf("exit: %i\n", WEXITSTATUS(exval));
	} else {
		++argv;
		execvp(argv[0], argv);
		printf("child: %i\n", pid);
	}
	return 8;
}


