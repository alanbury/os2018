#include <stdio.h>
#include <unistd.h>
int main() {
printf("Main before fork()\n");
int pid = fork();
	if (pid == 0) {
		printf("I am child 1 after fork1(), launching ps -ef\n");
		char *args[]= { "/bin/ps", "-ef" , NULL};
		execvp("/bin/ps", args);
	}
int pid2 = fork();
	if (pid2 == 0) {
		printf("I am child 1 after fork2(), launching free -h\n");
		char *args[]= { "/bin/free", "-h" , NULL};
		execvp("/bin/ps", args);
	}
return 0;
}
