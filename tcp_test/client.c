/*************************************************************************
    > File Name: client.c
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

#define MAX_CONNECT 5
#define BUFSIZE 1024

void handle(int sig)
{
	printf("recv a sig: %d\n",sig);
}
int main(int argc,char* argv[])
{
	int sock[1024*2];
	signal(SIGPIPE,handle);
	int i=0;
for(;i<1024*2;++i)
{
   sock[i] = socket(AF_INET,SOCK_STREAM,0);
      if(sock[i] == -1)
	  {
		  ERR_EXIT("socket");
	  }
    struct sockaddr_in srvaddr;
	memset(&srvaddr,0,sizeof(srvaddr));
   srvaddr.sin_family = AF_INET;
   srvaddr.sin_port = htons(8001);
   srvaddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  if(connect( sock[i],(struct sockaddr*)&srvaddr,sizeof(srvaddr)) < 0)
  {
	  printf("connect fail\n");
	  sleep(3);
	  ERR_EXIT("connect");
  }
   printf("i= %d \n",i);
}
 char recv_buf[BUFSIZE] = {0};
 char send_buf[BUFSIZE] = {0};

  while(fgets(send_buf,sizeof(send_buf),stdin))
  {
	  write(sock[0],send_buf,strlen(send_buf));
	  ssize_t ret = read(sock[0],recv_buf,sizeof(recv_buf)-1);
	  if(ret > 0)
	  {
		  recv_buf[ret] = '\0';
                  printf("return message: \n");
		  fputs(recv_buf,stdout);
                  printf("\n");
	  }else if(ret==0)
	  {
		  printf("service is close\n");
		  break;
	  }
	  else
	  {
		  close(sock[0]);
		  ERR_EXIT("read");
	  }
	  memset(recv_buf,0,sizeof(recv_buf));
	  memset(send_buf,0,sizeof(send_buf));
  }

close(sock[0]);
return  0;
}

