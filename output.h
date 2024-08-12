#pragma once

class OutputManager
{
public:
	static constexpr int CONSOLE_WIDTH = 120;
	static constexpr int CONSOLE_HEIGHT = 29;

public:
	OutputManager(void) noexcept;

public:
	void MoveCursor(short x, short y) const noexcept;
	void ClearBuffer(void) noexcept;
	void ClearUIBuffer(void) noexcept;
	void PrintBuffer(void) noexcept;
	void DrawSprite(short x, short y, wchar_t sprite) noexcept;
	void DrawString(short x, short y, const wchar_t* string) noexcept;
	void DrawUI(short x, const wchar_t* string) noexcept;

private:
	void* _console;
	wchar_t _buffer[CONSOLE_HEIGHT][CONSOLE_WIDTH + 1];
	wchar_t _UIBuffer[CONSOLE_WIDTH + 1];
};
