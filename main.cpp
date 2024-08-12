﻿#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

#include "tcp.h"
#include "message.h"
#include "user.h"
#include "output.h"

void run(void) noexcept
{
	TCP tcp;
	OutputManager output;

	tcp.Listen(L"0.0.0.0", 3000);

	for (;;)
	{
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
