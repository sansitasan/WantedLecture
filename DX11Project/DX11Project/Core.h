#pragma once

#define RESULT(result, message)\
if (FAILED(result))\
{\
	MessageBoxA(nullptr, message, "Error", MB_OK);\
	DebugBreak();\
}