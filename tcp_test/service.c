/*************************************************************************
    > File Name: service.c
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Mon 30 Nov 2015 11:48:25 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>
#include<sys/syscall.h>
#include<pthread.h>
#include<dirent.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#define ERR_EXIT(m)\
	do\
{\
	perror(m);\
	exit(1);\
}while(0);

#define MAX_CONNECT 1
#define BUFSIZE 1024


void  read_write(int connfd,struct sockaddr_in peraddr)
{
      while(1)
	  {
		  char recv_buf[BUFSIZE]={0};
		  ssize_t ret = read(connfd,recv_buf,sizeof(recv_buf)-1);
		  if(ret > 0)
		  {
              recv_buf[ret] = '\0';
    printf("client IP:%s, port:%d message:\n",inet_ntoa(peraddr.sin_addr),ntohs(peraddr.sin_port));
            fputs(recv_buf,stdout);
			printf("\n");
			write(connfd,recv_buf,strlen(recv_buf));
		  }else if(ret == 0)
		  {
    printf("client IP:%s, port:%d is close \n",inet_ntoa(peraddr.sin_addr),ntohs(peraddr.sin_port));
            close(connfd);
			exit(1);
		  }else
		  {
			  close(connfd);
			  ERR_EXIT("read");
		  }
		  memset(recv_buf,0,sizeof(recv_buf));
	  }
}


int main(int argc,char* argv[])
{
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
      if(sockfd == -1)
	  {
		  ERR_EXIT("socket");
	  }
    struct sockaddr_in srvaddr;
	memset(&srvaddr,0,sizeof(srvaddr));
   srvaddr.sin_family = AF_INET;
   srvaddr.sin_port = htons(8001);
   srvaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
   
   int opt = 1;
   if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt)) < 0)
   {
	   ERR_EXIT("setsockopt");
   }

   int ret = bind(sockfd,(struct sockaddr*)&srvaddr,sizeof(srvaddr));
   if(ret == -1)
   {
        ERR_EXIT("bind");
   }
   
   if(listen(sockfd,0) == -1)
   {
	   ERR_EXIT("listen");
   }
   
   while(1)
   {
   struct sockaddr_in peraddr;
   memset(&peraddr,0,sizeof(peraddr));
   socklen_t perlen = sizeof(peraddr);
   int connfd = accept(sockfd,(struct sockaddr*)&peraddr,&perlen);
     if(connfd == -1)
	 {
		 ERR_EXIT("accept");
	 }
    printf("client IP:%s, port:%d\n",inet_ntoa(peraddr.sin_addr),ntohs(peraddr.sin_port));

	pid_t id = fork();
	if(id < 0)
	{
     close(connfd);
     close(sockfd);
	 ERR_EXIT("fork");
	}else if(id == 0 )//child
	{
		close(sockfd);
       read_write(connfd, peraddr);
	}else // parent
	{
       close(connfd);
	}
		
	}

return  0;
}

