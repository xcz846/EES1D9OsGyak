#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv)
{
	pid_t p = fork();
	int status;

	if(p == 0)
	{
		printf("I'm the child process.\n");
		system("/bin/ls -R /");
	}
	else if (p < 0)
	{
		fprintf(stderr, "Running fork() failed!\n");
		return 0;
	}
	else if(p > 0)
	{
		printf("I'm the parent process.\n");
		printf("Child process ID is: %d.\n", p);
		p = wait(&status);
		if(WIFEXITED(status))
		{
			printf("The process ended with exit(%d).\n", WEXITSTATUS(status));
		}
		if(WIFSIGNALED(status))
		{
			printf("The process ended with kill -%d.\n", WTERMSIG(status));
		}
	}

	exit(0);
}