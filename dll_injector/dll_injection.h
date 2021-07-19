#pragma once

#include <windows.h>

bool inject_with_loadlibrary(HANDLE hProcess, const wchar_t *inject_path);

bool inject_into_process(DWORD pid, const wchar_t *dll_path);
