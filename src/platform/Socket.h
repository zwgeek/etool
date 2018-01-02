/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 标准的socket封装
 */

#ifndef ETOOL_PLATFORM_SOCKET
#define ETOOL_PLATFORM_SOCKET

#include <stdlib.h>
#include <string.h>
#if defined(_windows)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "../type/CircQueue.h"
#endif

typedef struct _etool_select etool_select;

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR   -1
	#define IO_RECV_SIZE   20
	#define IO_SEND_SIZE   20
#endif

#define ETOOL_SOCKET_MULTICAST_IP "224.0.1.0"
#if defined(_windows)
#define ETOOL_SOCKET_IO_INIT(io, operate, length, data) \
io->op = operate; \
io->buffer.len = length; \
io->buffer.buf = data
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#define ETOOL_SOCKET_IO_INIT(io, operate, length, useSize, data) \
io->op = operate; \
io->len = length; \
io->use = useSize; \
io->buf = data
#endif

/**
 * linux可以支持PF_PACKET协议地址族,对数链层以太网帧头进行维护(sockaddr_ll)
 * Windows Sockets无法支持数链层以太网帧头填充,只能使用winpcap或者ddk里的ndisprot驱动模版
 * 故此,本模块不提供二层数据帧头的封装api(物理层维度)
 * 注意:在使用ETOOL_SOCKET_ETHER类型时,需要获取管理员权限
 */
typedef enum {
	ETOOL_SOCKET_TCP = 0,
	ETOOL_SOCKET_UDP,
	ETOOL_SOCKET_IP,
	ETOOL_SOCKET_ETHER
} etool_socketType;

typedef enum _etool_socketOp {
	ETOOL_SOCKET_RECV = 0,
	ETOOL_SOCKET_RECVFROM,
	ETOOL_SOCKET_ACCEPT,
	ETOOL_SOCKET_SEND,
	ETOOL_SOCKET_SENDTO
} etool_socketOp;

typedef struct _etool_socketIo {
#if defined(_windows)
	OVERLAPPED overlapped;
	etool_socketOp op;
	WSABUF buffer;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	etool_socketOp op;
	unsigned long len;
	unsigned long use;
	char *buf;
	struct sockaddr_in addr;
#endif
} etool_socketIo;

typedef struct _etool_socket {
#if defined(_windows)
	SOCKET fd;
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	int fd;
#endif
	void *ptr;
	void *state;
	etool_select *selectfd;
} etool_socket;

typedef struct {
#if defined(_windows)
	char addr[(sizeof(struct sockaddr_in) + 16) * 2];
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
#endif
	void *_addr[2];
} etool_socketSingle;

typedef struct {
#if defined(_windows)
#endif
#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	etool_circQueue recvQueue;
	unsigned char recvBuffer[sizeof(etool_socketIo*) * IO_RECV_SIZE];
	etool_circQueue sendQueue;
	unsigned char sendBuffer[sizeof(etool_socketIo*) * IO_SEND_SIZE];
#endif
} etool_socketConnect;

/**
 * 创建socket
 * @param  type [description]
 * @return      [description]
 */
etool_socket* etool_socket_create(const etool_socketType type);

/**
 * 装载
 * @param  sockfd [description]
 * @param  type   [description]
 * @return        [description]
 */
int etool_socket_load(etool_socket *sockfd, const etool_socketType type);

/**
 * 卸载
 * @param  sockfd [description]
 */
void etool_socket_unload(etool_socket *sockfd);

/**
 * 销毁socket
 * @param  sockfd   [description]
 * @return         [description]
 */
void etool_socket_destroy(etool_socket *sockfd);

/**
 * 绑定(udp)
 * @param  sockfd   [description]
 * @param  ip   [description]
 * @param  port [description]
 * @return      [description]
 */
int etool_socket_bind(etool_socket *sockfd, const char *ip, const short port);

/**
 * 链接目的ip和端口(udp,tcp)
 * @param  sockfd   [description]
 * @param  host   [description]
 * @param  port   [description]
 * @return      [description]
 */
int etool_socket_connect(etool_socket *sockfd, const char *host, const short port);

/**
 * 监听(tcp,必须先bind)
 * @param  sockfd   [description]
 * @return      [description]
 */
int etool_socket_listen(etool_socket *sockfd);

/**
 * 接收连接,返回新的socket(tcp|阻塞)
 * @param  sockfd   [description]
 * @param  ip       [description]
 * @param  port     [description]
 * @param  io       [description]
 * @return          [description]
 */
etool_socket* etool_socket_accept(etool_socket *sockfd, char **ip, short *port, etool_socketIo *io);

/**
 * 发送数据(socket必须绑定了源地址和目标地址)
 * @param  sockfd [description]
 * @param  data   [description]
 * @param  length [description]
 * @param  io     [0:走阻塞函数]
 * @return        [description]
 */
int etool_socket_send(etool_socket *sockfd, char *data, int length, etool_socketIo *io);

/**
 * 接收数据(socket必须绑定了源地址和目标地址)
 * @param  sockfd [description]
 * @param  data   [description]
 * @param  length [description]
 * @param  io     [0:走阻塞函数]
 * @return        [description]
 */
int etool_socket_recv(etool_socket *sockfd, char *data, int length, etool_socketIo *io);

/**
 * 发送数据(空socket)
 * @param  sockfd [description]
 * @param  data   [description]
 * @param  length [description]
 * @param  host   [description]
 * @param  port   [description]
 * @param  io     [0:走阻塞函数]
 * @return        [description]
 */
int etool_socket_sendto(etool_socket *sockfd, char *data, int length, const char *host, const short port, etool_socketIo *io);

/**
 * 接收数据(空socket)
 * @param  sockfd [description]
 * @param  data   [description]
 * @param  length [description]
 * @param  host   [description]
 * @param  port   [description]
 * @param  io     [0:走阻塞函数]
 * @return        [description]
 */
int etool_socket_recvfrom(etool_socket *sockfd, char *data, int length, const char *host, const short port, etool_socketIo *io);

/**
 * 获取与套接口关联的本地协议地址
 * 在不调用bind的TCP客户,当connect成功返回后,getsockname返回分配给此连接的本地IP地址和本地端口号
 * 在以端口号为0调用bind后,使用getsockname返回内核分配的本地端口号
 * getsockname可用来获取某套接口的地址族
 * 在捆绑了通配IP地址的TCP服务器上，当连接建立后,可以使用getsockname获得分配给此连接的本地IP地址
 * @param  sockfd [description]
 * @param  ip     [description]
 * @param  port   [description]
 * @return        [description]
 */
int etool_socket_sockname(etool_socket *sockfd, char **ip, short *port);

/**
 * 获取与套接口关联的远程协议地址
 * 当一个服务器调用exec启动后,他获得客户身份的唯一途径是调用getpeername函数
 * @param  sockfd [description]
 * @param  ip     [description]
 * @param  port   [description]
 * @return        [description]
 */
int etool_socket_peername(etool_socket *sockfd, char **ip, short *port);

/**
 * 开启组播(可以加入不同的组播源)(不支持tcp,路由器必须支持源发现协议,如IGMP,MSDP,PIM_DM,PIM_SM)
 * 帧类型需要自己填充MAC地址,MAC的地址都以01:00:5e开头,第25位为0,低23位为IPv4组播地址的低23位
 * 224.0.0.0-239.255.255.255,TTL默认为1
 * @param sockfd [description]
 * @param ip     [要加入的组播源ip]
 * @param isLoop [用于控制数据是否回送到本地的回环接口,0 禁止回送,1 允许回送]
 * @return       [description]
 */
int etool_socket_multiCast(etool_socket *sockfd, const char *ip, const char isLoop);


/**
 * 开启广播(不支持tcp)
 * 帧类型需要自己填充MAC地址为ff:ff:ff:ff:ff:ff
 * 受限广播:255.255.255.255
 * 直接广播:[指向网络(主机号为全1的地址)\指向子网(主机号为全1且有特定子网号的地址)\指向所有子网(主机号及子网号为全1)]
 * @param sockfd [description]
 * @return       [description]
 */
int etool_socket_broadCast(etool_socket *sockfd);

/**
 * 设置超时机制
 * @param  sockfd      [description]
 * @param  sendTimeout [ms,发送超时]
 * @param  recvTimeout [ms,接收超时]
 * @return             [description]
 */
int etool_socket_timeout(etool_socket *sockfd, const int sendTimeout, const int recvTimeout);

/**
 * 原生socket选项封装,除非本模块不支持的功能,不推荐使用
 * @param sockfd  [description]
 * @param level   [description]
 * @param optname [description]
 * @param optval  [description]
 * @param optlen  [description]
 * @return        [description]
 */
int etool_socket_setsockopt(etool_socket *sockfd, int level, int optname, const char* optval, int optlen);

/**
 * socket连接单向关闭(能唤醒阻塞函数)
 * @param  sockfd [description]
 * @param  how    [0-不允许接受, 1-不允许发送, 2-不允许发送和接受]
 * @return        [description]
 */
int etool_socket_shutdown(etool_socket *sockfd, const int how);

/**
 * 获取错误码
 * @return [description]
 */
int etool_socket_errno();

/**
 * 设置socket为非阻塞
 * @param  sockfd   [description]
 * @param  selectfd [description]
 * @param  op       [description]
 * @return          [description]
 */
int etool_socket_nonblock(etool_socket *sockfd, etool_select *selectfd, etool_socketOp op);

/**
 * 创建socket的io,一个socket可以对应多个io
 * @return      [description]
 */
etool_socketIo* etool_socketIo_create();

/**
 * 销毁io
 * @param  io   [description]
 */
void etool_socketIo_destroy(etool_socketIo *io);

#endif //ETOOL_PLATFORM_SOCKET