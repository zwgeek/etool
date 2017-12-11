/**
 * Copyright 2017, PaPa.  All rights reserved.
 * 标准的多路复用(epoll,iocp)封装
 */

#ifndef ETOOL_SELECT
#define ETOOL_SELECT

typedef struct _etool_socket etool_socket;
//一个socket对应多个io,每次进行select操作前,都需要传一个能用的io
typedef struct _etool_socketIo etool_socketIo;
//socket当前操作
typedef enum _etool_socketOp etool_socketOp;

typedef struct _etool_select etool_select;
typedef void etool_selectCallback(etool_socket *sockfd, etool_socketIo *io, char *data, int length, etool_socketOp op);
namespace etool {

class CSelect {
	CSelect(const CSelect *select) { this->m_select = select.m_select; }
	CSelect& operator=(const CSelect *select) { this->m_select = select.m_select; return *this; }

public:
	CSelect(const int size = 20) : m_select(etool_select_create(size)) {}
	~CSelect() { etool_select_destroy(m_select); }

	inline int bind(etool_socket *sockfd, const etool_socketOp op) { etool_select_bind(m_select, sockfd, op); }
	inline int unbind(etool_socket *sockfd, const etool_socketOp op) { etool_select_unbind(m_select, sockfd, op); }
	inline int wait(const int timeout = 10) { etool_select_wait(m_select, this->callback, timeout); }
	virtual void callback(etool_socket *sockfd, etool_socketIo *io, char *data, int length, etool_socketOp op) = 0;
private:
	etool_select *m_select;
};
} //etool
#endif //ETOOL_SELECT