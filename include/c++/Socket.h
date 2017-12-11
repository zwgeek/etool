/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 标准的socket封装
 */

#ifndef ETOOL_SOCKET
#define ETOOL_SOCKET

typedef struct _etool_select etool_select;

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

typedef struct _etool_socketIo etool_socketIo;

typedef struct _etool_socket etool_socket;
namespace etool {

class CSocket {
	CSocket(const CSocket &socket) { this->m_socket = socket.m_socket; }
	CSocket& operator=(const CSocket &socket) { this->m_socket = socket.m_socket; return *this; }

public:
	CSocket(const etool_socketType type = ETOOL_SOCKET_TCP) : m_socket(etool_socket_create(type)) {}
	~CSocket() { etool_socket_destroy(m_socket); }

	inline int bind(const char *ip, const short port) { return etool_socket_bind(m_socket, ip, port); }
	inline int connect(const char *host, const short port) { return etool_socket_connect(m_socket, host, port); }
	inline int listen() { return etool_socket_listen(m_socket); }
	inline etool_socket* accept(char **ip, short *port, etool_socketIo *io) { return etool_socket_accept(m_socket, ip, port, io); }
	inline int send(char *data, int length, etool_socketIo *io) { return etool_socket_send(m_socket, data, length, io); }
	inline int recv(char *data, int length, etool_socketIo *io) { return etool_socket_recv(m_socket, data, length, io); }
	inline int sendto(char *data, int length, const char *host, const short port, etool_socketIo *io) { return etool_socket_sendto(m_socket, data, length, host, port, io); }
	inline int recvfrom(char *data, int length, const char *host, const short port, etool_socketIo *io) { return etool_socket_recvfrom(m_socket, data, length, host, port, io); }
	inline int sockname(char **ip, short *port) { return etool_socket_sockname(m_socket, ip, port); }
	inline int peername(char **ip, short *port) { return etool_socket_peername(m_socket, ip, port); }
	inline int multiCast(const char *ip, const char isLoop) { return etool_socket_multiCast(m_socket, ip, isLoop); }
	inline int broadCast() { return etool_socket_broadCast(m_socket); }
	inline int timeout(const int sendTimeout, const int recvTimeout) { return etool_socket_timeout(m_socket, sendTimeout, recvTimeout); }
	inline int setsockopt(int level, int optname, const char* optval, int optlen) { return etool_socket_setsockopt(m_socket, level, optname, optval, optlen); }
	inline int shutdown(const int how) { return etool_socket_shutdown(m_socket, how); }
	inline int errno() { return etool_socket_errno(m_socket); }
	inline static etool_socketIo* createIo() { return etool_socketIo_create(); }
	inline static void destroyIo(etool_socketIo *io) { return etool_socketIo_destroy(io); }

private:
	etool_socket *m_socket;
};
} //etool
#endif //ETOOL_SOCKET