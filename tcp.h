#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <list>

#pragma comment(lib, "ws2_32")

class TCP
{
private:
	struct SESSION
	{
		int _id;
		SOCKET _socket;
		wchar_t _ip[16];
		unsigned int _port;
	};

public:
	TCP(void) noexcept;
	~TCP(void) noexcept;

public:
	void Listen(const wchar_t* ip, unsigned short port) noexcept;

private:
	SOCKET _listen;

	int _id;
	std::list<SESSION> _sessions;

};
