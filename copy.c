#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	int fd_orig, fd_dest;
	char *buf;
	if (argc != 3){

		printf("Usage : %s <orig file> <dest file>\n", argv[0]);
		return 0;
	}
	if((fd_orig = open(argv[1], O_RDONLY)) != -1){
		int cnt;
		buf = malloc(4096);
		if (fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)){
			do{
				cnt = 0;
				cnt = read(fd_orig, buf, 4096);
			if( cnt == write(fd_dest, buf, cnt))		
				continue;
			}while( cnt != 0 );
		}else{
			printf("Failed to open %s \n", argv[2]);
			close(fd_orig);
			return -1;
		}
		printf("copy done %s -> %s", argv[1], argv[2]);
		free(buf);
	while(close(fd_dest));
	while(close(fd_orig));
	}else{
		printf("Failed to open %s \n", argv[1]);
	}
	return 0;
}

