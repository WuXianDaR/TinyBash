#include<stdio.h>
#include<sys/types.h>
#include<limits.h>
#include<stddef.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#define DIRSIZ 100 
int myCompare(char *path,char * filename){
	char*p;
	for(p = path+strlen(path);p >= path&& *p != '/';--p){
		;	
	}
	++p;
	return strcmp(p,filename);
}
void find(char *path,char *filename){
	char buf[512],*p;
	int fd;
	DIR* dir;
	struct dirent* de;
	struct stat st;
	if((fd = open(path,0)) < 0){
		perror("find:cannot open");
		exit(1);	
	}
	if(fstat(fd,&st) < 0){
		perror("find:cannot fstat");
		exit(1)	;
	}
	if(S_ISREG(st.st_mode)){
		if(myCompare(path,filename) == 0){
			printf("%s\n",path);
			close(fd);
		}		
	}
	if(S_ISDIR(st.st_mode)){
		if(myCompare(path,filename) == 0){
			printf("%s\n",path);
		}		
		if(strlen(path)+1+DIRSIZ+1 > sizeof(buf)){
			printf("find:path too long\n");	
		}	
		strcpy(buf,path);
		p = buf+strlen(buf);
		*p++ = '/';
		if((dir = opendir(path)) == NULL){
			perror("find cannot opendir");
			return;	
		}
		while((de = readdir(dir)) != NULL){
			if(!strcmp(de->d_name,".") || !strcmp(de->d_name,".."))	
				continue;
			memmove(p,de->d_name,DIRSIZ);
			p[DIRSIZ] = 0;
			close(fd);
			find(buf,filename);
		}
	}
}
int main(int argc,char *argv[]){
	if(argc != 3){
		perror("Use find [path,file]\n");
		exit(1);
	}
	find(argv[1],argv[2]);
}
