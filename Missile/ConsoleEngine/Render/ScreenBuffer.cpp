#include "PreCompiledHeader.h"
#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer(const COORD& size, CONSOLE_FONT_INFOEX& fontInfo)
	: size(size)
{
	buffer = CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (buffer == INVALID_HANDLE_VALUE)
	{
		__debugbreak();
	}

	SetConsoleScreenBufferSize(buffer, size);
	SMALL_RECT rect = { 0, 0, size.X - 1, size.Y - 1 };
	SetConsoleWindowInfo(buffer, true, &rect);

	CONSOLE_CURSOR_INFO info{ 1, false };
	SetConsoleCursorInfo(buffer, &info);
	SetCurrentConsoleFontEx(buffer, FALSE, &fontInfo);

	SetConsoleMode(buffer, ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_WINDOW_INPUT);
}

ScreenBuffer::ScreenBuffer(HANDLE console, const COORD& size)
	: size(size), buffer(console)
{
	SetConsoleScreenBufferSize(buffer, size);
	SMALL_RECT rect = { 0, 0, size.X - 1, size.Y - 1 };
	SetConsoleWindowInfo(buffer, true, &rect);

	CONSOLE_CURSOR_INFO cursorInfo{ 1, false };
	SetConsoleCursorInfo(buffer, &cursorInfo);

	SetConsoleMode(buffer, ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_WINDOW_INPUT);
}

ScreenBuffer::~ScreenBuffer()
{
	CloseHandle(buffer);
}

void ScreenBuffer::SetCursorType(ECursorType cursorType)
{
	// 1. 커서 속성 구조체 설정.
	CONSOLE_CURSOR_INFO info = { };

	// 타입 별로 구조체 값 설정.
	switch (cursorType)
	{
	case ECursorType::NoCursor:
		info.dwSize = 1;
		info.bVisible = FALSE;
		break;

	case ECursorType::SolidCursor:
		info.dwSize = 100;
		info.bVisible = TRUE;
		break;

	case ECursorType::NormalCursor:
		info.dwSize = 20;
		info.bVisible = TRUE;
		break;
	}

	// 2. 설정.
	SetConsoleCursorInfo(buffer, &info);
}

void ScreenBuffer::Clear()
{
	COORD position = { 0, 0 };
	DWORD writtenCount = 0;
	FillConsoleOutputCharacter(buffer, ' ', (size.X + 1) * size.Y + 1, position, &writtenCount);
}

void ScreenBuffer::Draw(CHAR_INFO* charInfo)
{
	COORD bufferPosition = { 0, 0 };
	COORD bufferSize = { size.X, size.Y };
	SMALL_RECT writeRegion = { 0, 0, bufferSize.X - 1, bufferSize.Y - 1 };

	WriteConsoleOutputW(buffer, charInfo, bufferSize, bufferPosition, &writeRegion);
}