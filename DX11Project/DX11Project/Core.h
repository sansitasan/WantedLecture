#pragma once
#define WIN_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <comdef.h>

#define ShowErrorMessage(message, reason)\
wchar_t buffer[512] = {};\
swprintf_s(buffer, 512, TEXT("[File: %s]\n[Line: %d]\n[Function: %s]\n[Message: %s]\n[Reason: %s]"), TEXT(__FILE__), __LINE__, TEXT(__FUNCTION__), message, reason);\
MessageBox(nullptr, buffer, TEXT("Error"), MB_OK);

#define RESULT(result, message)\
if (FAILED(result))\
{\
	_com_error error(result);\
	ShowErrorMessage(message, error.ErrorMessage());\
	DebugBreak();\
}