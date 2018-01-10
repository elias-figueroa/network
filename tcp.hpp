#ifndef _TCP_HPP_
#define _TCP_HPP_

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define NET_FAIL   -1
#define NET_SUCCESS 0

#ifdef _WIN32
typedef SOCKET sock_t;
#else
typedef int sock_t;
#define INVALID_SOCKET -1
#endif



namespace tcp {

	sock_t socket();

	class stream {
		struct sockaddr_in	m_addr;
		sock_t 				m_sock;
	public:
		stream(sock_t sock, struct sockaddr_in addr);
		stream(tcp::stream * s);
		~stream();

		int send(const void * buf, size_t buflen);
		int recv(void * buf, size_t buflen);
		void close();
	}

	// tcp::stream * connect(const char * ipv4, uint16_t port);
	int connect(const char * ipv4, uint16_t port, tcp::stream * s);
}




#endif