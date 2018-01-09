#ifndef _TCP_HPP_
#define _TCP_HPP_

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifdef _win32
typedef SOCKET sock_t;
#else
typedef int sock_t;
#endif



namespace tcp {

	class stream;

	sock_t socket() {
		return (sock_t)::socket(AF_INET, SOCK_STREAM, 0);
	}

	class stream {
		struct sockaddr_in	m_addr;
		sock_t 				m_sock;
	public:
		stream(sock_t sock, struct sockaddr_in addr);
		stream(tcp::stream * s);
		~stream() { close(); }

		int send(char * buf, size_t buflen) {
			if (m_sock != -1)
				return ::send(m_sock, buf, buflen, 0);
			return m_sock;
		}
		int recv(char * buf, size_t buflen) {
			if (m_sock != -1)
				return ::recv(m_sock, buf, buflen, 0);
			return m_sock;
		}

		void close() {
			if (m_sock != -1)
				::close(m_sock);
		}
	}

	class smart_stream: private tcp::stream {
	public:
		int send_string(char * buf, size_t buflen) {
			return this->send(buf, buflen);
		}
		int recv_string(char * buf, size_t buflen) {
			int n = this->recv(buf, buflen);
			buf[(n != -1) ? n : 0] = '\0';
			return n;
		}

		int send_int(int value) {
			char buf[sizeof(int) + 1];

			// get endiannes
			return -1;
		}
		int recv_int(int * p) {
			return -1;
		}

		
	}

}




#endif