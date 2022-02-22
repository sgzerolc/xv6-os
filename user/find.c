#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define CURDIR "."
#define PARDIR ".."

void find(char *path, char *file){
	char buf[512], *w, *p;
	int fd;
	struct dirent de;
	struct stat st;

	// Find file/dir name after last slash
	for(w=path+strlen(path); w >= path && *w != '/'; w--)
		;
	w++;	

	if ((fd = open(path, 0)) < 0){
		fprintf(2, "find: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "find: cannot stat %s\n", path);
		close(fd);
		return;
	}

	switch (st.type)
	{
	case T_FILE:
	// file found, print path
		if (strcmp(w, file) == 0){
			printf("%s\n", path);
		}
	// file not found
		break;
	
	case T_DIR:
	// read directories
		strcpy(buf, path);
		p = buf + strlen(buf);
		*p++ = '/';
		while(read(fd, &de, sizeof(de)) == sizeof(de)){
			if(de.inum == 0)
				continue;
			memmove(p, de.name, DIRSIZ);
			p[DIRSIZ] = 0;
			if ((strcmp(de.name, CURDIR) == 0) || (strcmp(de.name, PARDIR) == 0)){ //missing part
				continue;
			} else {
				find(buf, file);
			}
			
		}
		break;
	}
	close(fd);
}


int main(int argc, char *argv[]){
	find(argv[1], argv[2]);
	exit(0);
}