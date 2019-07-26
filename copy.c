#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[]){
	int fd_orig, fd_dest;
	char *buf;
	int cnt;
	int w_cnt;
	int select;
	if (argc != 3){
		printf("Usage : %s <orig file> <dest file> \n", argv[0]);
		return 0;
	}
	if((fd_orig = open(argv[1], O_RDONLY)) != -1){
		buf = malloc(4096);
		if (0 == access(argv[2], F_OK)){
			printf("file is already\r\n");
			printf("1. overwirte?\r\n2. append?\r\n3. done?");
			scanf("%d", &select);
			if (select == 1){
				if (fd_dest = open(argv[2], O_WRONLY | O_TRUNC | O_SYNC, 0644)){
					do{
						cnt = 0;
						w_cnt = 0;
						cnt = read(fd_orig, buf, 4096);
						w_cnt = write(fd_dest, buf, cnt);	
						if (cnt == w_cnt)
							continue;
						else if (cnt == -1 || w_cnt == -1)
							printf("read or write error");
					}while( cnt != 0 );
					printf("copy done %s -> %s \r\n", argv[1], argv[2]);
				}else{
					printf("Failed to open %s \n", argv[2]);
					close(fd_orig);
					return -1;
				}
			} else if (select == 2) {
					if (fd_dest = open(argv[2], O_WRONLY | O_APPEND | O_SYNC, 0644)){
					do{
						cnt = 0;
						w_cnt = 0;
						cnt = read(fd_orig, buf, 4096);
						w_cnt = write(fd_dest, buf, cnt);	
						if (cnt == w_cnt)
							continue;
						else if (cnt == -1 || w_cnt == -1)
							printf("read or write error");
					}while( cnt != 0 );
					printf("copy done %s -> %s \r\n", argv[1], argv[2]);
				}else{
					printf("Failed to open %s \n", argv[2]);
					close(fd_orig);
					return -1;
				}
			} else {
				printf("you select done");
				return 0;
			}
		} else {
			if (fd_dest = creat(argv[2], 0644)){
				do{
					cnt = 0;
					w_cnt = 0;
					cnt = read(fd_orig, buf, 4096);
					w_cnt = write(fd_dest, buf, cnt);	
			 		if (cnt == w_cnt)
						continue;
					else if (cnt == -1 || w_cnt == -1)
						printf("read or write error");
				}while( cnt != 0 );
				printf("copy done %s -> %s \r\n", argv[1], argv[2]);
			}else{
				printf("Failed to open %s \n", argv[2]);
				close(fd_orig);
				return -1;
			}
		}
		free(buf);
		while(close(fd_dest));
		while(close(fd_orig));
	}else{
		printf("Failed to open %s \n", argv[1]);
	}
	return 0;
}

