#include "tcp.hpp"



sock_t tcp::socket() {
	return (sock_t)::socket(AF_INET, SOCK_STREAM, 0);
}

tcp::stream(sock_t sock, struct sockaddr_in addr):
	m_sock(sock), m_addr(addr) {}
tcp::stream(tcp::stream * s):
	m_sock(s->m_sock), m_addr(s->m_addr) {}
tcp::~stream() { close(); }

int tcp::send(const void * buf, size_t buflen) {
	if (m_sock != INVALID_SOCKET)
		return ::send(m_sock, buf, buflen, 0);
	return NET_FAIL;
}
int tcp::recv(void * buf, size_t buflen) {
	if (m_sock != INVALID_SOCKET)
		return ::recv(m_sock, buf, buflen, 0);
	return NET_FAIL;
}

void tcp::close() {
	if (m_sock != INVALID_SOCKET)
		::close(m_sock);
}

tcp::stream * tcp::connect(const char * ipv4, uint16_t port) {
	sock_t sock = tcp::socket();

	if (sock == INVALID_SOCKET)
		return nullptr;

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ipv4, &addr.sin_addr);

	if (::connect(sock, (struct sockaddr *) &addr, sizeof(addr)) != INVALID_SOCKET) {
		return new tcp::stream(sock, addr);
	}

	::close(sock);
	return nullptr;
}

int tcp::connect(const char * ipv4, uint16_t port, tcp::stream * s) {
	sock_t sock = tcp::socket();

	if (sock == INVALID_SOCKET)
		return NET_FAIL;

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ipv4, &addr.sin_addr);

	if (::connect(sock, (struct sockaddr *) &addr, sizeof(addr)) != INVALID_SOCKET) {
		*s = tcp::stream(sock, addr);
		return NET_SUCCESS;
	}

	::close(sock);
	return NET_FAIL;
}


































