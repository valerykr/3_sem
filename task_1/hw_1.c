#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iso646.h>
#include <sys/wait.h>
#include <unistd.h>

const int N = 1000;

int main() {
	char del[] = " ,\n";

	while (1 == 1) {
		char *p;
		char *s = (char*) malloc(N*sizeof(char));
		int i = 0;
		int j = 0;
		
		scanf("%[^\n]%*c", s);
		const pid_t pid = fork();
		if (pid < 0)
			printf("fork error!");
		if (pid) {
			int status;
			waitpid(pid, &status, 0);
		} else {
			char **cmd = (char **) malloc(N*sizeof(char*));
			int k = 0;
			for (; k < N; k++)
				cmd[k] = NULL;
			for (p = strtok(s, del); p != NULL; p = strtok(NULL, del)) {
				cmd[j] = p;
				j++;
			}

			int ex_res;
			ex_res = execvp(cmd[0], cmd);
			if (ex_res == -1) {
				printf("exec error!");
				exit(-1);
			}
			free(cmd);
			free(s);
		}

	}


	return 0;
}


