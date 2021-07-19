#include <windows.h>
#include <iostream>
#include <sstream>



int wmain(int argc, char* argv[])
{
    std::cout << "TestApp, PID = " << std::dec << GetCurrentProcessId() << "\n";
    std::cout << "This app prints 20 MessageBoxes one after another..." << std::endl;

    for (size_t i = 0; i < 20; i++) {
        std::stringstream ss;
        ss << "Message Box #" << i;
        MessageBoxA(NULL, ss.str().c_str(), "OK", MB_OK);
    }
    system("pause");
    return 0;
}
