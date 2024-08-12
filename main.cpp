#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

#include "tcp.h"
#include "message.h"
#include "user.h"

int wmain(void)
{
	TCP tcp;
	tcp.Listen(L"0.0.0.0", 3000);



#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
