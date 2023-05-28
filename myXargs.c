#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<limits.h>
#include<stddef.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>

#define MAX_LEN 100
char * readFromInput(){
	char buf[512],c;
	int index = -1;
	while(read(0,&c,sizeof(char))){
		if(c == '\n'){
			break;	
		}	
		else{
			buf[++index] = c;	
		}
	}
	if(index == -1){
		return NULL;	
	}
	char *p = (char*)malloc((index+1) *sizeof(char));
	memmove(p,buf,index+1);
	return p;
}
int main(int argc,char * argv[]){
	if(argc < 2){
		perror("xargs need more parameters");
		exit(1);	
	}
	char *argvNew[MAX_LEN];
	for(int i = 1;i < argc;++i){
		argvNew[i-1] = argv[i]	;
	}
	char *r;
	while((r = readFromInput()) != NULL){
		argvNew[argc-1] = r;
		argvNew[argc] = NULL;
		if(fork() == 0){
			execvp(argvNew[0],argvNew)	;
			free(r);
			exit(0);
		}	
		else{
			wait(0);	
		}
	}
	exit(0);
}
