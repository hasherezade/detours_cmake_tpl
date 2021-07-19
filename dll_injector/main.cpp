#include <windows.h>
#include <iostream>
#include <sstream>

#include "dll_injection.h"
#include "process_privilege.h"

int loadInt(const std::wstring &str)
{
    int intVal = 0;

    std::wstringstream ss;
    ss << std::dec << str;
    ss >> intVal;

    return intVal;
}

int wmain(int argc, wchar_t* argv[])
{
    if (argc < 3) {
        std::cout << "Inject DLL into the process with the given PID (using classig DLL injection)\n"
            << "Args: <PID> <DLL Path>"
            << std::endl;
        system("pause");
        return 0;
    }

    int pid = loadInt(argv[1]);
    wchar_t *dll_path = argv[2];

    if (set_debug_privilege()) {
        std::cout << "[*] Debug privilege set!\n";
    }

    std::wcout << "PID: " << pid << "\n"
        << "DLL: " << dll_path << "\n";

    bool isLoaded = inject_into_process(pid, dll_path);
    if (isLoaded) {
        std::cout << "Done!\n";
        return 0;
    }
    std::cerr << "[ERROR] Creating remote thread failed!\n";
    return (-1);
}
