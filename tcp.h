#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <list>

#pragma comment(lib, "ws2_32")

class TCP
{
public:
	TCP(void) noexcept;
	~TCP(void) noexcept;

public:
	void SetAccept(void (*func)(int id));
	void SetReceive(void (*func)(int id));
	void Listen(const wchar_t* ip, unsigned short port) noexcept;
	void Receive(void) noexcept;

private:
	struct SESSION
	{
		int _id;
		SOCKET _socket;
		wchar_t _ip[16];
		unsigned int _port;
	};

private:
	SOCKET _listen;

	int _id;
	std::list<SESSION> _sessions;

	void (*_accept)(int id);
	void (*_receive)(int id);
};
