




#ifndef _SCK_CLINT_H_
#define _SCK_CLINT_H_



#ifdef __cplusplus
extern 'C'
{
#endif



//错误码定义  

#define Sck_Ok             	0
#define Sck_BaseErr   		3000

#define Sck_ErrParam                	(Sck_BaseErr+1)
#define Sck_ErrTimeOut                	(Sck_BaseErr+2)
#define Sck_ErrPeerClosed               (Sck_BaseErr+3)
#define Sck_ErrMalloc			   		(Sck_BaseErr+4)

//函数声明
//客户端环境初始化
int sckCliet_init(void **handle);
int sckCliet_getconn(void *handle, char *ip, int port, int *connfd,int contime);
int sckCliet_closeconn(int connfd);
//客户端发送报文
int sckClient_send(void *handle, int  connfd,  unsigned char *data, int datalen,int sendtime);
//客户端端接受报文
int sckClient_rev(void *handle, int  connfd, unsigned char *out, int *outlen,int recvtime); //1

// 客户端环境释放 
int sckClient_destroy(void *handle);



//函数声明
//服务器端初始化
int sckServer_init(const char* ip,short port, int *listenfd);

int sckServer_accept(int listenfd, int *connfd,  int timeout);
//服务器端发送报文
int sckServer_send(int connfd,  unsigned char *data, int datalen, int timeout);
//服务器端端接受报文
int sckServer_rev(int  connfd, unsigned char *out, int *outlen,  int timeout); //1

//服务器端环境释放 
int sckServer_destroy(void *handle);



#ifdef __cpluspluse
}
#endif


#endif
