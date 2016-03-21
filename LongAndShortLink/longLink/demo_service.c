/*************************************************************************
    > File Name: demo_service.c
    > Author: WK
    > Mail:18402927708@163.com 
    > Created Time: Thu 26 Nov 2015 11:56:44 PM CST
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
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define ERR_EXIT(m)\
	do\
{\
       perror(m);\
	   exit(1);\
}while(0);


#define MAX_CONNECT 5
#define BUFSIZE 1024

int main(int argc,char* argv[])
{
	// int socket(int domain, int type, int protocol);
    int sockfd= socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		ERR_EXIT("socket");
	}
   //int bind(int sockfd, const struct sockaddr *addr,
   //                socklen_t addrlen);
    
    struct sockaddr_in srvaddr;
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(8001);
	srvaddr.sin_addr.s_addr=inet_addr("0.0.0.0");
	//srvaddr.sin_addr.s_addr = INADDR_ANY;//0.0.0.0
	//  int getsockopt(int sockfd, int level, int optname,
	//                 void *optval, socklen_t *optlen)
	//  int setsockopt(int sockfd, int level, int optname,
	//           const void *optval, socklen_t optlen);
	int opt =1;
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt)) < 0)
	{
		ERR_EXIT("setsockopt");
	}
   int ret =bind(sockfd,(struct sockaddr*)&srvaddr,sizeof(srvaddr));
	if(ret < 0)
	{
		ERR_EXIT("bind");
	}
    //int listen(int sockfd, int backlog);
	if(listen(sockfd,MAX_CONNECT)<0)
	{
          ERR_EXIT("listen");
	}
   // int accept(int sockfd, struct sockaddr *addr,
   //                      socklen_t *addrlen);

    struct sockaddr_in  perraddr;
	socklen_t perrlen=sizeof(perraddr);
	 int connfd=accept(sockfd,(struct sockaddr*)&perraddr,&perrlen);
     if(connfd < 0)
	{
		ERR_EXIT("accept");
	}
	//char *inet_ntoa(struct in_addr in);
	printf("perraddr IP:%s port:%d\n",inet_ntoa(perraddr.sin_addr),ntohs(perraddr.sin_port));

	 
	  char recv_buf[BUFSIZE]={0};
      while(1)
	  {
           ssize_t ret = read(connfd,recv_buf,sizeof(recv_buf)-1);
		   if(ret> 0)
		   {
           recv_buf[ret]='\0';
           fputs(recv_buf,stdout);
		   write(connfd,recv_buf,strlen(recv_buf));
		   }else if(ret == 0)
		   {
	printf("perraddr IP:%s port:%d",inet_ntoa(perraddr.sin_addr),ntohs(perraddr.sin_port));
               printf("  client is close\n");
			   break;
		   }else
		   {
			   ERR_EXIT("read");
		   }
		  memset(recv_buf,0,sizeof(recv_buf));	  
	  }
      close(connfd);
	  close(sockfd);

return  0;
}

