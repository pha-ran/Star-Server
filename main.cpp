#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

#include "tcp.h"
#include "output.h"
#include "player.h"
#include "message.h"

void AddPlayer(int id)
{
	wprintf(L"AddPlayer %d\n", id);
}

void Receive(int id)
{
	wprintf(L"Receive %d\n", id);
}

void run(void) noexcept
{
	TCP tcp;
	OutputManager output;

	tcp.SetAccept(AddPlayer);
	tcp.SetReceive(Receive);
	tcp.Listen(L"0.0.0.0", 3000);

	for (;;)
	{
		tcp.Receive();
		break;

		output.ClearBuffer();
		output.DrawUI(0, L"0.0.0.0:3000");
		output.PrintBuffer();
	}
}

int wmain(void)
{
	run();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
