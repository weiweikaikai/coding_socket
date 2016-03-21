#include <unistd.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
//#include "sckutil.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "commsocket.h"

void handle(int signum)
{
	int pid = 0;
	printf("recv signum:%d \n", signum);
	
	//���⽩ʬ����
	while ((pid = waitpid(-1, NULL, WNOHANG) ) > 0)
	{
		printf("�˳��ӽ���pid%d \n", pid);
		fflush(stdout);
	} 
}

/*
int main(void)
{
	int pronum = 0;
	int loop = 0;
	int i =0;
	//signal(SIGCHLD, handle);
	
	printf("\nplease enter process num: ");
	scanf("%d", &pronum);
	
	printf("\nplease enter loop num:");
	scanf("%d", &loop);
	
	for (i=0; i<pronum; i++)
	{
		int j = 0;
		int pid = 0;
		pid = fork();
		if (pid == 0)
		//if (1)
		{
			int sock;
			if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
				ERR_EXIT("socket");
		
			struct sockaddr_in servaddr;
			memset(&servaddr, 0, sizeof(servaddr));
			servaddr.sin_family = AF_INET;
			servaddr.sin_port = htons(8001);
			servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		
		
			int ret = connect_timeout(sock, &servaddr, 5);
			if (ret == -1 && errno == ETIMEDOUT)
			{
				printf("timeout...\n");
				return 1;
			}
			else if (ret == -1)
				ERR_EXIT("connect_timeout");
		
			struct sockaddr_in localaddr;
			socklen_t addrlen = sizeof(localaddr);
			if (getsockname(sock, (struct sockaddr*)&localaddr, &addrlen) < 0)
				ERR_EXIT("getsockname");
		
			printf("ip=%s port=%d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));
			
			char sendbuf[1024] = {0};
			char recvbuf[1024] = {0};
			printf("loop:%d\n", loop);
			for (j=0; j<loop; j++)
			{
				sprintf(sendbuf, "sendbufdata process:%d loop:%d\n", i, j);
				//printf("aaaaaaaaaa\n");
				writen(sock, sendbuf, strlen(sendbuf));
				//printf("bbbbbbbbbbbbb\n");
				int ret = readline(sock, recvbuf, sizeof(recvbuf));
				//printf("ccccccccccccc\n");
		        if (ret == -1)
		                ERR_EXIT("readline");
		        else if (ret == 0)
		        {
	                printf("�Է��ѹرգ�����client close\n");
	                close(sock);
	                break;
		        }
				//printf("dddddddddddddddd\n");
				fputs(recvbuf, stdout);
				fflush(stdout);
				memset(sendbuf, 0, sizeof(sendbuf));
				memset(recvbuf, 0, sizeof(recvbuf));
			}
			printf("process:%d ��������˳�\n", i);
			close(sock);
			exit(0);
		}
		else if (pid > 0)
		{
			printf("������\n");
		}
		else
		{
			printf("ʧ��\n");
		}
	}
	while(1)
	sleep(11);
	//���⽩ʬ����
	int mypid;
	
	//while ((mypid = waitpid(-1, NULL, WNOHANG) ) > 0)
	//{
	//	printf("�˳��ӽ��� mypid %d \n", mypid);
	//	fflush(stdout);
	//} 
	
	return 0;
}
*/

int main()
{	
	int 		ret = 0;
	void 		*handle = NULL;
	//void 		handle = NULL;
	int 		connfd;
	
		
	 unsigned char send_data[1024];
	 int send_datalen = 0;
	 
	 unsigned char recv_data[1024];
	 int recv_datalen = 0;
	//�ͻ��˻�����ʼ��
	//int sckCliet_init(void **handle, char *ip, int port, int contime, int sendtime, int revtime);
	ret = sckCliet_init(&handle);
	
	ret = sckCliet_getconn(handle, "127.0.0.1", 8002, &connfd,15);

     if(fgets((char*)send_data,sizeof(send_data),stdin) == NULL)
	 {
         printf("fgets error\n");
		 //......
	 }
		send_datalen = strlen((const char*)send_data);
	//�ͻ��˷��ͱ���
	ret = sckClient_send(handle,  connfd, send_data, send_datalen,5);
	if (ret == Sck_ErrTimeOut)
	{
          printf("sckClinet_send timeout err:%d\n",ret);
	}
	//�ͻ��˶˽��ܱ���
	ret = sckClient_rev(handle, connfd, recv_data, &recv_datalen,5);
   if(ret != 0)
   {
        
   }
	recv_data[recv_datalen] = '\0';
	printf("data: %s \n", recv_data);
	// �ͻ��˻����ͷ� 
	ret = sckClient_destroy(handle);

	return 0;
}

