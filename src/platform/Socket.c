#include "Socket.h"
#include "Select.h"


etool_socket* etool_socket_create(etool_socketType type)
{
	etool_socket *sockfd = malloc(sizeof(etool_socket));
	if (sockfd == 0) { return 0; }
#if defined(_windows)
	WSADATA  wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		return 0;
	}
#endif
	//windows:A socket created by the socket function will have the overlapped attribute as the default
	switch (type) {
	case ETOOL_SOCKET_TCP   :
		sockfd->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		break;
	case ETOOL_SOCKET_UDP   :
		sockfd->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		break;
	case ETOOL_SOCKET_IP    :
		sockfd->fd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
		break;
	case ETOOL_SOCKET_ETHER :
		{ sockfd->fd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
		const int on;
		//开启IP_HDRINCL特性
		if (sockfd->fd == INVALID_SOCKET || setsockopt(sockfd->fd, IPPROTO_IP, IP_HDRINCL, (const char*)&on, sizeof(on)) == SOCKET_ERROR) {
			free(sockfd);
			return 0;
		}
		break; }
	default :
		return 0;
	}
	if (sockfd->fd == INVALID_SOCKET) {
		free(sockfd);
		return 0;
	}
	sockfd->selectfd = 0;
	return sockfd;
}

int etool_socket_load(etool_socket *sockfd, etool_socketType type)
{
#if defined(_windows)
	WSADATA  wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		return -1;
	}
#endif
	//windows:A socket created by the socket function will have the overlapped attribute as the default
	switch (type) {
	case ETOOL_SOCKET_TCP   :
		sockfd->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		break;
	case ETOOL_SOCKET_UDP   :
		sockfd->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		break;
	case ETOOL_SOCKET_IP    :
		sockfd->fd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
		break;
	case ETOOL_SOCKET_ETHER :
		{ sockfd->fd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
		const int on;
		//开启IP_HDRINCL特性
		if (sockfd->fd == INVALID_SOCKET || setsockopt(sockfd->fd, IPPROTO_IP, IP_HDRINCL, (const char*)&on, sizeof(on)) == SOCKET_ERROR) {
			return -1;
		}
		break; }
	default :
		return -1;
	}
	if (sockfd->fd == INVALID_SOCKET) {
		return -1;
	}
	sockfd->selectfd = 0;
	return 0;
}

void etool_socket_unload(etool_socket *sockfd)
{
#if defined(_windows)
	closesocket(sockfd->fd);
	WSACleanup();
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	close(sockfd->fd);
#endif	
}

void etool_socket_destroy(etool_socket *sockfd)
{
#if defined(_windows)
	closesocket(sockfd->fd);
	WSACleanup();
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	close(sockfd->fd);
#endif
	free(sockfd);
}

int etool_socket_bind(etool_socket *sockfd, const char *ip, const short port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
#if defined(_windows)
	addr.sin_addr.S_un.S_addr = ip == 0 ? htonl(INADDR_ANY) : inet_addr(ip);
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	addr.sin_addr.s_addr = ip == 0 ? htonl(INADDR_ANY) : inet_addr(ip);
#endif
	if (bind(sockfd->fd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == SOCKET_ERROR) {
		return -1;
	}
	return 0;
}

int etool_socket_connect(etool_socket *sockfd, const char *host, const short port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
#if defined(_windows)
	addr.sin_addr.S_un.S_addr = host == 0 ? htonl(INADDR_ANY) : inet_addr(host);
	if (addr.sin_addr.S_un.S_addr != INADDR_NONE) {
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	addr.sin_addr.s_addr = host == 0 ? htonl(INADDR_ANY) : inet_addr(host);
	if (addr.sin_addr.s_addr == INADDR_NONE) {
#endif
		struct hostent *ent = gethostbyname(host);
		if (!ent) {
			return -1;
		}
		addr.sin_addr = *(struct in_addr*)(ent->h_addr_list[0]);
	}
	if (connect(sockfd->fd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == SOCKET_ERROR) {
		return -1;
	}
	return 0;
}

int etool_socket_listen(etool_socket *sockfd)
{
	//20,进入队列中允许的连接数目
	if (listen(sockfd->fd, 20) == SOCKET_ERROR) {
		return -1;
	}
	return 0;
}

etool_socket* etool_socket_accept(etool_socket *sockfd, char **ip, short *port)
{
	struct sockaddr_in addr;
	etool_socket *client = malloc(sizeof(etool_socket));
	size_t addrlen = sizeof(struct sockaddr);
	client->fd = accept(sockfd->fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen);
	if (client->fd == INVALID_SOCKET) {
		free(client);
		return 0;
	}
	*ip = inet_ntoa(addr.sin_addr);
	*port = ntohs(addr.sin_port);
	return client;
}

int etool_socket_send(etool_socket *sockfd, char *data, int length, etool_socketIo *io)
{
#if defined(_windows)
	if (io != 0) {
		DWORD sendBytes;
		ETOOL_SOCKET_IO_INIT(io, ETOOL_SELECT_SEND, length, data);
		if (WSASend(sockfd->fd, &(io->buffer), 1, &sendBytes, 0, &(io->overlapped), 0) == SOCKET_ERROR) {
			if (WSAGetLastError() != ERROR_IO_PENDING) {
				return -1;
			}
			return 0;
		}
		return sendBytes;
	}
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	if (io != 0) {
		if (etool_circQueue_empty(sockfd->sendBuffer) == 0) {
			ETOOL_SOCKET_IO_INIT(io, ETOOL_SELECT_SEND, length, 0, data);
			etool_circQueue_enter(sockfd->sendBuffer, (void*)&io);
			return 0;
		}
		int sendBytes = send(sockfd->fd, data, length, 0);
		if (sendBytes == SOCKET_ERROR) {
			if (errno == EAGAIN) {
				ETOOL_SOCKET_IO_INIT(io, ETOOL_SELECT_SEND, length, 0, data);
				etool_circQueue_enter(sockfd->sendBuffer, (void*)&io);
				ETOOL_SELECT_MOD(sockfd->selectfd, sockfd, ETOOL_SELECT_SEND);
				return 0;
			}
		} else if (sendBytes < length) {
			ETOOL_SOCKET_IO_INIT(io, ETOOL_SELECT_SEND, length, sendBytes, data);
			etool_circQueue_enter(sockfd->sendBuffer, (void*)&io);
			ETOOL_SELECT_MOD(sockfd->selectfd, sockfd, ETOOL_SELECT_SEND);
			return 0;
		}
		return sendBytes;
	}
#endif
	return send(sockfd->fd, data, length, 0);
}

int etool_socket_recv(etool_socket *sockfd, char *data, int length, etool_socketIo *io)
{
#if defined(_windows)
	if (io != 0) {
		DWORD recvBytes;
		ETOOL_SOCKET_IO_INIT(io, ETOOL_SELECT_RECV, length, data);
		if (WSARecv(sockfd->fd, &(io->buffer), 1, &recvBytes, 0, &(io->overlapped), 0) == SOCKET_ERROR) {
			if (WSAGetLastError() != ERROR_IO_PENDING) {
				return -1;
			}
			return 0;
		}
		return recvBytes;
	}
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	if (io != 0) {
		io->type = ETOOL_SELECT_RECV;
		io->len = length;
		io->buf = data;
		etool_circQueue_enter(sockfd->recvBuffer, (void*)&io);
		return 0;
	}
#endif
	return recv(sockfd->fd, data, length, 0);
}

int etool_socket_sendto(etool_socket *sockfd, char *data, int length, const char *host, const short port, etool_socketIo *io)
{
	struct sockaddr_in *addr, _addr;
#if defined(_windows)
	addr = &_addr;
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	if (io != 0) { addr = &(io->addr); } else { addr = &_addr; }
#endif
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
#if defined(_windows)
	addr->sin_addr.S_un.S_addr = host == 0 ? htonl(INADDR_ANY) : inet_addr(host);
	if (addr->sin_addr.S_un.S_addr == INADDR_NONE && strcmp(host, "255.255.225.225") != 0) {
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	addr->sin_addr.s_addr = host == 0 ? htonl(INADDR_ANY) : inet_addr(host);
	if (addr->sin_addr.s_addr == INADDR_NONE && strcmp(host, "255.255.225.225") != 0) {
#endif
		struct hostent *ent = gethostbyname(host);
		if (!ent) {
			return -1;
		}
		addr->sin_addr = *(struct in_addr*)(ent->h_addr_list[0]);
	}
#if defined(_windows)
	if (io != 0) {
		DWORD sendBytes;
		ETOOL_SOCKET_IO_INIT(io, ETOOL_SELECT_SENDTO, length, data);
		if (WSASendTo(sockfd->fd, &(io->buffer), 1, &sendBytes, 0, (void*)addr, sizeof(struct sockaddr), &(io->overlapped), 0) == SOCKET_ERROR) {
			if (WSAGetLastError() != ERROR_IO_PENDING) {
				return -1;
			}
			return 0;
		}
		return sendBytes;
	}
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	if (io != 0) {
		if (etool_circQueue_empty(sockfd->sendBuffer) == 0) {
			ETOOL_SOCKET_IO_INIT(io, ETOOL_SELECT_SENDTO, length, 0, data);
			etool_circQueue_enter(sockfd->sendBuffer, (void*)&io);
			return 0;
		}
		int sendBytes = sendto(sockfd->fd, data, length, 0, (struct sockaddr*)addr, sizeof(struct sockaddr));
		if (sendBytes == SOCKET_ERROR) {
			if (errno == EAGAIN) {
				ETOOL_SOCKET_IO_INIT(io, ETOOL_SELECT_SENDTO, length, 0, data);
				etool_circQueue_enter(sockfd->sendBuffer, (void*)&io);
				ETOOL_SELECT_MOD(sockfd->selectfd, sockfd, ETOOL_SELECT_SEND);
				return 0;
			}
		} else if (sendBytes < length) {
			ETOOL_SOCKET_IO_INIT(io, ETOOL_SELECT_SENDTO, length, sendBytes, data);
			etool_circQueue_enter(sockfd->sendBuffer, (void*)&io);
			ETOOL_SELECT_MOD(sockfd->selectfd, sockfd, ETOOL_SELECT_SEND);
			return 0;
		}
		return sendBytes;
	}
#endif
	return sendto(sockfd->fd, data, length, 0, (struct sockaddr*)addr, sizeof(struct sockaddr));
}

int etool_socket_recvfrom(etool_socket *sockfd, char *data, int length, const char *host, const short port, etool_socketIo *io)
{
	struct sockaddr_in *addr, _addr;
#if defined(_windows)
	addr = &_addr;
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	if (io != 0) { addr = &(io->addr); } else { addr = &_addr; }
#endif
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
#if defined(_windows)
	addr->sin_addr.S_un.S_addr = host == 0 ? htonl(INADDR_ANY) : inet_addr(host);
	if (addr->sin_addr.S_un.S_addr == INADDR_NONE) {
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	addr->sin_addr.s_addr = host == 0 ? htonl(INADDR_ANY) : inet_addr(host);
	if (addr->sin_addr.s_addr == INADDR_NONE) {
#endif
		struct hostent *ent = gethostbyname(host);
		if (!ent) {
			return -1;
		}
		addr->sin_addr = *(struct in_addr*)(ent->h_addr_list[0]);
	}
	size_t addrlen = sizeof(struct sockaddr);
#if defined(_windows)
	if (io != 0) {
		DWORD recvBytes;
		ETOOL_SOCKET_IO_INIT(io, ETOOL_SELECT_RECVFROM, length, data);
		if (WSARecvFrom(sockfd->fd, &(io->buffer), 1, &recvBytes, 0, (struct sockaddr*)addr, (socklen_t*)&addrlen, &(io->overlapped), 0) == SOCKET_ERROR) {
			if (WSAGetLastError() != ERROR_IO_PENDING) {
				return -1;
			}
			return 0;
		}
		return recvBytes;
	}
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	if (io != 0) {
		io->type = ETOOL_SELECT_RECVFROM;
		io->len = length;
		io->buf = data;
		etool_circQueue_enter(sockfd->recvBuffer, (void*)&io);
		return 0;
	}
#endif
	return recvfrom(sockfd->fd, data, length, 0, (struct sockaddr*)addr, (socklen_t*)&addrlen);
}

int etool_socket_sockname(etool_socket *sockfd, char **ip, short *port)
{
	struct sockaddr_in addr;
	size_t addrlen = sizeof(struct sockaddr);
	if (getsockname(sockfd->fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen) != 0) {
		return -1;
	}
	*ip = inet_ntoa(addr.sin_addr);
	*port = ntohs(addr.sin_port);
	return 0;
}

int etool_socket_peername(etool_socket *sockfd, char **ip, short *port)
{
	struct sockaddr_in addr;
	size_t addrlen = sizeof(struct sockaddr);
	if (getpeername(sockfd->fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen) != 0) {
		return -1;
	}
	*ip = inet_ntoa(addr.sin_addr);
	*port = ntohs(addr.sin_port);
	return 0;
}

int etool_socket_multiCast(etool_socket *sockfd, const char *ip, const char isLoop)
{
	struct sockaddr_in addr;
	size_t addrlen = sizeof(struct sockaddr);
	if (getsockname(sockfd->fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen) != 0) {
		return -1;
	}
	struct ip_mreq group;
	group.imr_interface = addr.sin_addr;
	group.imr_multiaddr.s_addr = ip == 0 ? inet_addr(ETOOL_SOCKET_MULTICAST_IP) : inet_addr(ip);
	//加入组播
	if (setsockopt(sockfd->fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&group, sizeof(struct ip_mreq)) == SOCKET_ERROR) {
		return -1;
	}
	//发送接口设置
	if (setsockopt(sockfd->fd, IPPROTO_IP, IP_MULTICAST_IF, (const char*)&addr.sin_addr, sizeof(struct in_addr)) == SOCKET_ERROR) {
		return -1;
	}
	//是否回送到本地的回环接口
	if (setsockopt(sockfd->fd, IPPROTO_IP, IP_MULTICAST_LOOP, &isLoop, sizeof(const char)) == SOCKET_ERROR) {
		return -1;
	}
	return 0;
}

int etool_socket_broadCast(etool_socket *sockfd)
{
	const int on = 1;
	return setsockopt(sockfd->fd, SOL_SOCKET, SO_BROADCAST, (const char*)&on, sizeof(const char));
}

int etool_socket_timeout(etool_socket *sockfd, const int sendTimeout, const int recvTimeout)
{
#if defined(_windows)
	if (setsockopt(sockfd->fd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&sendTimeout, sizeof(const int)) == 0) {
		return -1;
	}
	return setsockopt(sockfd->fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&recvTimeout, sizeof(const int));
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	struct timeval _sendTimeout = {0, sendTimeout * 1000};
	if (setsockopt(sockfd->fd, SOL_SOCKET, SO_SNDTIMEO, &_sendTimeout, sizeof(struct timeval)) == 0) {
		return -1;
	}
	struct timeval _recvTimeout = {0, recvTimeout * 1000};
	return setsockopt(sockfd->fd, SOL_SOCKET, SO_RCVTIMEO, &_recvTimeout, sizeof(struct timeval));
#endif
}

int etool_socket_setsockopt(etool_socket *sockfd, int level, int optname, const char* optval, int optlen)
{
	return setsockopt(sockfd->fd, level, optname, optval, optlen);
}

int etool_socket_shutdown(etool_socket *sockfd, const int how)
{
	return shutdown(sockfd->fd, how);
}

int etool_socket_errno()
{
#if defined(_windows)
	return WSAGetLastError();
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	return errno;
#endif
}

int etool_socket_nonblock(etool_socket *sockfd, etool_select *selectfd)
{
#if defined(_windows)
	// 首先将这个sockfd设置为非阻塞(IOCP模型不需要非阻塞)
	// unsigned long mode = 1;
	// if (ioctlsocket(sockfd->fd, FIONBIO, &mode) != 0) {
	// 	return -1;
	// }
	// return 0;
#endif

#if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
	//首先将这个sockfd设置为非阻塞
	int opts = fcntl(sockfd->fd, F_GETFL);
	if (opts != 0) { return -1; }
	if (fcntl(sockfd->fd, F_SETFL, opts | O_NONBLOCK) != 0) {
		return -1;
	}
	sockfd->recvBuffer = etool_circQueue_create(sizeof(etool_socketIo*), IO_RECV_SIZE);
	sockfd->sendBuffer = etool_circQueue_create(sizeof(etool_socketIo*), IO_SEND_SIZE);
#endif
	sockfd->selectfd = selectfd;
	return 0;
}

inline etool_socketIo* etool_socketIo_create()
{
	return malloc(sizeof(etool_socketIo));
}

inline void etool_socketIo_destroy(etool_socketIo *io)
{
	free(io);
}

// #if defined(_linux) || defined(_mac) || defined(_android) || defined(_ios)
// 	switch (type) {
// 	case ETOOL_SOCKET_TCP :
// 		sockfd->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
// 		break;
// 	case ETOOL_SOCKET_UDP :
// 		sockfd->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
// 		break;
// 	case ETOOL_SOCKET_IP  :
// 		sockfd->fd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
// 	default :
// 		return 0;
// 	}
// #endif