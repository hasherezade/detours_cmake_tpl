#include <windows.h>
#include <detours.h>
#include <iostream>
#include <sstream>

int (WINAPI *pMessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) = ::MessageBoxA;

int WINAPI my_MessageBoxA(
    _In_opt_ HWND hWnd,
    _In_opt_ LPCSTR lpText,
    _In_opt_ LPCSTR lpCaption,
    _In_ UINT uType)
{
    //Log Debug String:
    {
        std::stringstream ss;
        ss << "Intercepted: " << __FUNCTION__ << " : " << lpCaption << " : " << lpText;
        OutputDebugStringA(ss.str().c_str());
    }

    std::stringstream ss;
    ss << "Intercepted: " << lpCaption;

    // Execute the normal function:
    return pMessageBoxA(hWnd, lpText, ss.str().c_str(), uType);
}

void hook_api(bool enable)
{
    LONG(WINAPI *_DetourAction)(_Inout_ PVOID *ppPointer, _In_ PVOID pDetour) = NULL;
    if (enable) {
        _DetourAction = DetourAttach;
    }
    else {
        _DetourAction = DetourDetach;
    }

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    // perform the action (hooking/unhooking):
    _DetourAction(&(PVOID&)pMessageBoxA, my_MessageBoxA);

    DetourTransactionCommit();
}

BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        OutputDebugStringA("Hooking the process");
        hook_api(true);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        OutputDebugStringA("Unhooking the process");
        hook_api(false);
        break;
    }
    return TRUE;
}
