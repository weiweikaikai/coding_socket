/*************************************************************************
    > File Name: demo_client.c
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


#define BUFSIZE 1024

int main(int argc,char* argv[])
{
	int i=0;
	for(;i<10;++i)
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

    //int connect(int sockfd, const struct sockaddr *addr,
	//		                   socklen_t addrlen); 
       if (connect(sockfd,(struct sockaddr*)&srvaddr,sizeof(srvaddr)) < 0)
	   {
		   ERR_EXIT("connect");
	   }

		  char recv_buf[BUFSIZE]={0};
		  char send_buf[BUFSIZE]="haha\n";
     	//fgets(send_buf,sizeof(send_buf),stdin);
	       
		   write(sockfd,send_buf,strlen(send_buf));
           ssize_t ret = read(sockfd,recv_buf,sizeof(recv_buf)-1);
		   if(ret>0)
		   {
		   recv_buf[ret]='\0';
           fputs(recv_buf,stdout);  				 
		   }else if(ret == 0)
		   {
       printf("service is close\n");
		   }else
		   {
			   close(sockfd);
			   ERR_EXIT("read");
		   }
		  memset(recv_buf,'0',sizeof(recv_buf));
		  memset(send_buf,'0',sizeof(send_buf));
          close(sockfd);
   }
return  0;
}

