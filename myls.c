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
#define DIRSIZ 14
char *fmtname(char *path){
	static char buf[DIRSIZ+1];
	char *p;
	if(strncmp(path,"./",2) == 0){
		path += 2;	
	}
	for(p = path+strlen(path);p >= path;--p)
			;
	++p;
	if(strlen(p) > DIRSIZ)return p;
	memmove(buf,p,strlen(p));
	memset(buf+strlen(p),' ',DIRSIZ-strlen(p));
	return buf;
			
}
void ls(char * path){
	char buf[512],*p;
	int fd;
	DIR*dir;
	struct dirent* de;
	struct stat st;
	
	if((fd = open(path,0)) < 0){
   		 perror("ls:cannot open");
		return;
	}	
	if(fstat(fd,&st) < 0){
		printf("ls:cannot stat %s\n",path);
		return;
	}
	if(S_ISDIR(st.st_mode)){
		if(strlen(path)+1+DIRSIZ +1 > sizeof(buf)){
			printf("ls:path too long\n");
		}	
		strcpy(buf,path);
		p = buf+strlen(buf);
		*p++ = '/';
		if ((dir = opendir(path)) == NULL) {
		    perror("ls cannot open");
		    return;
		}
		while((de = readdir(dir)) != NULL){
			if(de->d_ino == 0){
				continue;	
			}
			memmove(p,de->d_name,DIRSIZ);
			if(stat(buf,&st) < 0){
				perror("ls:cannot stat");
				continue;	
			}	
			printf("%s %ld %ld \n",fmtname(buf),st.st_ino,st.st_size);
		}
	}
	else if(S_ISREG(st.st_mode)){
			printf("%s %ld %ld \n",fmtname(path),st.st_ino,st.st_size);
			
	}
}
int main(int argc,char * argv[]){
	if(argc < 2){

		ls(".");
		exit(0);	
	}
	for(int i = 1;i < argc;++i){
		ls(argv[i]);
			
	}
	exit(0);
}
