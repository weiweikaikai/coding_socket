#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "commsocket.h"
#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)
        
        
#include <signal.h>

void handle(int signum)
{
	int pid = 0;
	printf("recv signum:%d ", signum);
	
	//±ÜÃâ½©Ê¬½ø³Ì
	while ((pid = waitpid(-1, NULL, WNOHANG) ) > 0)
	{
		printf("exit child proccess  pid= %d \n", pid);
		fflush(stdout);
	} 
}

int main(void)
{
	int		ret = 0;
	int 	listenfd;
	
	
	signal(SIGCHLD, handle);
	signal(SIGPIPE, SIG_IGN);
	
	ret = sckServer_init("127.0.0.1",8002, &listenfd);
	if (ret != 0)
	{
		printf("sckServer_init() err:%d \n", ret);
		return ret;
	}
	
	while(1)
	{
		int ret = 0;
		int wait_seconds = 10;
		int connfd = 0;

		ret = sckServer_accept(listenfd, &connfd,  wait_seconds);
		if (ret == Sck_ErrTimeOut)
		{
			printf("timeout....\n");
			continue;
		}
	   //printf("listenfd %d\nconfd : %d\n",listenfd,connfd);
		int pid = fork();
		if (pid == 0)
		{
			unsigned char 	recvbuf[1024];
			int recvbuflen = 1024;
				
			close(listenfd);
			while(1)
			{
				memset(recvbuf, 0, sizeof(recvbuf));
				ret = sckServer_rev(connfd, recvbuf, &recvbuflen,  10);
				if (ret != 0)
				{
					printf("func sckServer_rev() err:%d \n", ret);
					break;
				}
				ret = sckServer_send(connfd,  recvbuf, recvbuflen, 6);
				if (ret != 0)
				{
					printf("func sckServer_send() err:%d \n", ret);
					break;
				}
			}
			
			close(connfd);
			exit(ret);
		}
		else if (pid > 0)//father
		{
			close(connfd);
		}
		else if(pid == -1)
		{
		   close(connfd);
		   close(listenfd);
           ERR_EXIT("fork");
		}
	}
	
	return 0;
}
