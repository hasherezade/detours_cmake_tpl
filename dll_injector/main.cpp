#include <windows.h>
#include <iostream>

LPVOID write_into_process(HANDLE hProcess, LPBYTE buffer, SIZE_T buffer_size, DWORD protect)
{
    LPVOID remoteAddress = VirtualAllocEx(hProcess, NULL, buffer_size, MEM_COMMIT | MEM_RESERVE, protect);
    if (remoteAddress == NULL) {
        std::cerr << "Could not allocate memory in the remote process\n";
        return NULL;
    }
    if (!WriteProcessMemory(hProcess, remoteAddress, buffer, buffer_size, NULL)) {
        VirtualFreeEx(hProcess, remoteAddress, buffer_size, MEM_FREE);
        return NULL;
    }
    return remoteAddress;
}

bool inject_with_loadlibrary(HANDLE hProcess, char *inject_path)
{
    if (!inject_path) {
        return false;
    }

    //calculate size along with the terminating '\0'
    SIZE_T inject_path_size = strlen(inject_path) + sizeof(inject_path[0]);

    // write the full path of the DLL into the remote process:
    PVOID remote_ptr = write_into_process(hProcess, (BYTE*)inject_path, inject_path_size, PAGE_READWRITE);
    if (!remote_ptr) {
        std::cerr << "Writing to process failed: " << std::hex << GetLastError() << "\n";
        return false;
    }
    std::cout << "Path writen to: " << remote_ptr << "\n";

    HMODULE hModule = GetModuleHandleW(L"kernel32.dll");
    if (!hModule) return false;

    FARPROC hLoadLib = GetProcAddress(hModule, "LoadLibraryA");
    if (!hLoadLib) return false;

    // Inject to the remote process:
    HANDLE hndl = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)hLoadLib, remote_ptr, NULL, NULL);
    WaitForSingleObject(hndl, INFINITE);

    // cleanup:
    VirtualFreeEx(hProcess, remote_ptr, 0, MEM_RELEASE);
    return true;
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Inject DLL into the process with the given PID (using classig DLL injection)\n"
            << "Args: <PID> <DLL Path>"
            << std::endl;
        system("pause");
        return 0;
    }

    int pid = atoi(argv[1]);
    char *dll_path = argv[2];

    std::cout << "PID: " << pid << "\n"
        << "DLL: " << dll_path << "\n";
    
    HANDLE hProcess = OpenProcess(
        PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, 
        FALSE, 
        pid
    );

    if (!hProcess || hProcess == INVALID_HANDLE_VALUE) {
        std::cerr << "[ERROR] Opening the process failed: " << std::hex << GetLastError() << std::endl;
        return (-1);
    }

    bool isLoaded = inject_with_loadlibrary(hProcess, dll_path);
    if (isLoaded) {
        std::cout << "Injection OK!\n";
        return 0;
    }
    std::cerr << "[ERROR] Creating remote thread failed!\n";
    return -1;
}
