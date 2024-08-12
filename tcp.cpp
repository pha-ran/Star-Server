#include "tcp.h"
#include <stdio.h>

TCP::TCP(void) noexcept
	: _id(1)
{
	WSADATA wsadata;
	if (WSAStartup(0x0202, &wsadata) != 0) __debugbreak();
}

TCP::~TCP(void) noexcept
{
	WSACleanup();
}

void TCP::Listen(SOCKET* sock, const wchar_t* ip, unsigned short port) noexcept
{
	// socket
	*sock = socket(AF_INET, SOCK_STREAM, 0);

	if (*sock == INVALID_SOCKET)
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
	int b = bind(*sock, (SOCKADDR*)&addr, sizeof(addr));

	if (b == SOCKET_ERROR)
	{
		wprintf(L"bind(%d)", WSAGetLastError());
		__debugbreak();
	}

	// ioctlsocket
	u_long arg = 1;
	int nb = ioctlsocket(*sock, FIONBIO, &arg);

	if (nb == SOCKET_ERROR)
	{
		wprintf(L"ioctlsocket(%d)", WSAGetLastError());
		__debugbreak();
	}

	// setsockopt
	LINGER linger;
	linger.l_onoff = 1;
	linger.l_linger = 0;

	int opt = setsockopt(*sock, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger));

	if (opt == SOCKET_ERROR)
	{
		wprintf(L"setsockopt(%d)", WSAGetLastError());
		__debugbreak();
	}

	// listen
	int l = listen(*sock, SOMAXCONN_HINT(USHRT_MAX));

	if (l == SOCKET_ERROR)
	{
		wprintf(L"listen(%d)", WSAGetLastError());
		__debugbreak();
	}
}
