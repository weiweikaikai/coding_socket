#include <unistd.h>
#include<arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)

int main(void)
{
	int sock;
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8003);
//	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	if (bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");

	
	sendto(sock, "ABCD", 4, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
	
	//数据报方式。。。。不是字节流
	//如果接受数据时，指定的缓冲区的大小，较小；
	//剩余部分将要截断，扔掉
	char recvbuf[1];
	int n;
	int i;
	for (i=0; i<4; i++)
	{
		n = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
		if (n == -1)
		{
			if (errno == EINTR)
				continue;
			ERR_EXIT("recvfrom");
		}
		else if(n > 0)
			printf("n=%d %c\n", n, recvbuf[0]);
	}
	return 0;
}
