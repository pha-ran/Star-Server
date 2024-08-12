#include "output.h"
#include <windows.h>
#include <stdio.h>

#pragma warning(disable:26495)

OutputManager::OutputManager(void) noexcept
{
	CONSOLE_CURSOR_INFO cursor;

	_console = GetStdHandle(STD_OUTPUT_HANDLE);

	cursor.bVisible = FALSE;
	cursor.dwSize = 1;

	SetConsoleCursorInfo(_console, &cursor);

	ClearBuffer();
	ClearUIBuffer();
}

void OutputManager::MoveCursor(short x, short y) const noexcept
{
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(_console, coord);
}

void OutputManager::ClearBuffer(void) noexcept
{
	for (SHORT row = 0; row < CONSOLE_HEIGHT; ++row)
	{
		for (SHORT col = 0; col < CONSOLE_WIDTH; ++col)
			_buffer[row][col] = L' ';

		_buffer[row][CONSOLE_WIDTH] = L'\0';
	}
}

void OutputManager::ClearUIBuffer(void) noexcept
{
	for (SHORT index = 0; index < CONSOLE_WIDTH; ++index)
		_UIBuffer[index] = L' ';

	_UIBuffer[CONSOLE_WIDTH - 2] = L'\0';
}

void OutputManager::PrintBuffer(void) noexcept
{
	for (SHORT row = 0; row < CONSOLE_HEIGHT; ++row)
	{
		MoveCursor(0, row);
		wprintf(_buffer[row]);
	}

	wprintf(_UIBuffer);
}

void OutputManager::DrawSprite(short x, short y, wchar_t sprite) noexcept
{
	if (x < 0 || y < 0 || x >= CONSOLE_WIDTH || y >= CONSOLE_HEIGHT)
		return;

	_buffer[y][x] = sprite;
}

void OutputManager::DrawString(short x, short y, const wchar_t* string) noexcept
{
	if (x < 0 || y < 0 || x >= CONSOLE_WIDTH || y >= CONSOLE_HEIGHT)
		return;

	for (SHORT index = 0; string[index] != L'\0'; ++index)
	{
		if (x + index >= CONSOLE_WIDTH)
			break;

		_buffer[y][x + index] = string[index];
	}
}

void OutputManager::DrawUI(short x, const wchar_t* string) noexcept
{
	if (x < 0 || x >= CONSOLE_WIDTH - 2)
		return;

	for (SHORT index = 0; string[index] != L'\0'; ++index)
	{
		if (x + index >= CONSOLE_WIDTH - 2)
			break;

		_UIBuffer[x + index] = string[index];
	}
}
