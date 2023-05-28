#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_LEN 100
int main(void){
	char cmd[MAX_LEN];	
	char *args[MAX_LEN/2+1];
	while(1){
		printf("myBash$ ");
		fflush(stdout);	
		if(fgets(cmd,MAX_LEN,stdin) == NULL){
			perror("error");
			break;	
		}
		cmd[strcspn(cmd,"\n")] = '\0';
		int i = 0;
		char *token = strtok(cmd," ");
		while(token){
			args[i] = token;
			token = strtok(NULL," ");
			++i;	
		}
		args[i] = NULL;
			/*if (strcmp(args[0], "myls") == 0) {
            char cwd[MAX_LEN];
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                perror("getcwd");
                continue;
            }
            char path[MAX_LEN];
            if (snprintf(path, sizeof(path), "%s/myls", cwd) >= sizeof(path)) {
                continue;
            }
            args[0] = path;
        }*/
		pid_t pid = fork();
		if(pid == 0){

			if(execvp(args[0],args) == -1)	{
				perror("execvp");
				exit(1);	
			}
			exit(0);
		}
		else if(pid > 0){
			wait(NULL);	
		}
		else{
			printf("fork error\n");
			exit(1);	
		}
		
	}
	return 0;
}
