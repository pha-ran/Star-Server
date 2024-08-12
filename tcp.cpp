#include "tcp.h"
#include <stdio.h>

#pragma warning(disable:26495)

TCP::TCP(void) noexcept
{
	WSADATA wsadata;
	if (WSAStartup(0x0202, &wsadata) != 0) __debugbreak();
}

TCP::~TCP(void) noexcept
{
	closesocket(_listen);
	WSACleanup();
}

void TCP::Listen(const wchar_t* ip, unsigned short port) noexcept
{
	// socket
	_listen = socket(AF_INET, SOCK_STREAM, 0);

	if (_listen == INVALID_SOCKET)
	{
		wprintf(L"socket(%d)", WSAGetLastError());
		__debugbreak();
	}

	// addr
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	int pton = InetPtonW(AF_INET, ip, &addr.sin_addr);
	addr.sin_port = htons(port);

	if (pton != 1)
	{
		wprintf(L"InetPtonW(%d)", WSAGetLastError());
		__debugbreak();
	}

	// bind
	int b = bind(_listen, (SOCKADDR*)&addr, sizeof(addr));

	if (b == SOCKET_ERROR)
	{
		wprintf(L"bind(%d)", WSAGetLastError());
		__debugbreak();
	}

	// ioctlsocket
	u_long arg = 1;
	int nb = ioctlsocket(_listen, FIONBIO, &arg);

	if (nb == SOCKET_ERROR)
	{
		wprintf(L"ioctlsocket(%d)", WSAGetLastError());
		__debugbreak();
	}

	// setsockopt
	LINGER linger;
	linger.l_onoff = 1;
	linger.l_linger = 0;

	int opt = setsockopt(_listen, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger));

	if (opt == SOCKET_ERROR)
	{
		wprintf(L"setsockopt(%d)", WSAGetLastError());
		__debugbreak();
	}

	// listen
	int l = listen(_listen, SOMAXCONN_HINT(USHRT_MAX));

	if (l == SOCKET_ERROR)
	{
		wprintf(L"listen(%d)", WSAGetLastError());
		__debugbreak();
	}
}
