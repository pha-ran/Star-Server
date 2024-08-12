#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

class TCP
{
public:
	TCP(void) noexcept;
	~TCP(void) noexcept;

public:
	void Listen(const wchar_t* ip, unsigned short port) noexcept;

private:
	SOCKET _listen;
};
