#include <windows.h>
#include <detours.h>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        std::cout << "Run the process with the hooking DLL injected\n"
            << "Args: <hooking_lib*> <exe_to_be_hooked> [cmdline]\n"
            << "* warning: in order for this injection type to work, the DLL must have at least one export\n";
        system("pause");
        return 0;
    }

    char *dll_path = argv[1];
    char *exe_path = argv[2];
    char *cmdline = NULL;
    if (argc > 3) {
        cmdline = argv[3];
    }
    std::cout << "Running the process: " << exe_path << "\n";
    std::cout << "With the DLL: " << dll_path << "\n";

    STARTUPINFOA si = { 0 };
    si.cb = sizeof(STARTUPINFOA);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;
    PROCESS_INFORMATION pi = { 0 };

    BOOL is_ok = DetourCreateProcessWithDllA(
        exe_path, 
        cmdline,
        NULL, NULL, TRUE, 
        CREATE_DEFAULT_ERROR_MODE,
        NULL, NULL, &si, &pi,
        dll_path,
        NULL);

    if (!is_ok) {
        std::cerr << "[ERROR] Failed to create a process with DLL injected!\n";
        return -1;
    }
    std::cout << "The process is running...\n";
    WaitForSingleObject(pi.hProcess, INFINITE);
    return 0;
}
