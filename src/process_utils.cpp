#include "process_utils.h"
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>
#include <iomanip>

namespace ProcessUtils {

// Enable console colors
void EnableConsoleColors(bool enable) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (enable) {
        DWORD mode = 0;
        GetConsoleMode(hConsole, &mode);
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
}

// Print colored message
void PrintColored(const std::string& message, WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD savedAttributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, color);
    std::cout << message << std::endl;
    SetConsoleTextAttribute(hConsole, savedAttributes);
}

void PrintSuccess(const std::string& message) {
    PrintColored("[+] " + message, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void PrintErrorMsg(const std::string& message) {
    PrintColored("[-] " + message, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void PrintInfo(const std::string& message) {
    PrintColored("[*] " + message, FOREGROUND_CYAN | FOREGROUND_INTENSITY);
}

void PrintWarning(const std::string& message) {
    PrintColored("[!] " + message, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

// Print detailed error
void PrintError(const char* context) {
    DWORD error = GetLastError();
    LPVOID lpMsgBuf;

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&lpMsgBuf,
        0,
        NULL
    );

    std::cerr << "[-] " << context << " failed with error " << error << ": " << (char*)lpMsgBuf;
    LocalFree(lpMsgBuf);
}

// Get process ID by name
DWORD GetProcessIdByName(const char* processName) {
    DWORD processId = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        PrintError("CreateToolhelp32Snapshot");
        return 0;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (_stricmp(pe32.szExeFile, processName) == 0) {
                processId = pe32.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);

    if (processId == 0) {
        PrintErrorMsg(std::string("Process not found: ") + processName);
    }

    return processId;
}

// Callback for window enumeration
struct EnumWindowsCallbackArgs {
    DWORD processId;
    HWND hwnd;
};

BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam) {
    auto* args = reinterpret_cast<EnumWindowsCallbackArgs*>(lParam);

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);

    if (pid == args->processId && IsWindowVisible(hwnd)) {
        args->hwnd = hwnd;
        return FALSE; // Stop enumeration
    }

    return TRUE; // Continue enumeration
}

// Get window by process ID
HWND GetWindowByProcessId(DWORD processId) {
    EnumWindowsCallbackArgs args = { processId, nullptr };
    EnumWindows(EnumWindowsCallback, reinterpret_cast<LPARAM>(&args));

    if (!args.hwnd) {
        PrintErrorMsg("No visible window found for process");
    }

    return args.hwnd;
}

// Get remote module handle
HMODULE GetRemoteModuleHandle(HANDLE hProcess, const char* moduleName) {
    HMODULE hModules[1024];
    DWORD cbNeeded;

    if (!EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded)) {
        PrintError("EnumProcessModules");
        return nullptr;
    }

    for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
        char szModName[MAX_PATH];

        if (GetModuleBaseNameA(hProcess, hModules[i], szModName, sizeof(szModName))) {
            if (_stricmp(szModName, moduleName) == 0) {
                return hModules[i];
            }
        }
    }

    PrintErrorMsg(std::string("Module not found: ") + moduleName);
    return nullptr;
}

// Get remote procedure address
FARPROC GetRemoteProcAddress(HANDLE hProcess, HMODULE hRemoteModule, const char* functionName) {
    // Load local module to calculate offset
    HMODULE hLocalModule = GetModuleHandleA("kernel32.dll");
    if (!hLocalModule) {
        PrintError("GetModuleHandleA");
        return nullptr;
    }

    // Get function address in local module
    FARPROC localFunction = GetProcAddress(hLocalModule, functionName);
    if (!localFunction) {
        PrintErrorMsg(std::string("Function not found: ") + functionName);
        return nullptr;
    }

    // Calculate offset and apply to remote module
    DWORD_PTR offset = (DWORD_PTR)localFunction - (DWORD_PTR)hLocalModule;
    return (FARPROC)((DWORD_PTR)hRemoteModule + offset);
}

// Safe read from remote process
bool ReadProcessMemorySafe(HANDLE hProcess, LPCVOID address, LPVOID buffer, SIZE_T size) {
    SIZE_T bytesRead;

    if (!ReadProcessMemory(hProcess, address, buffer, size, &bytesRead)) {
        PrintError("ReadProcessMemory");
        return false;
    }

    if (bytesRead != size) {
        PrintErrorMsg("Partial read occurred");
        return false;
    }

    return true;
}

// Safe write to remote process
bool WriteProcessMemorySafe(HANDLE hProcess, LPVOID address, LPCVOID buffer, SIZE_T size) {
    DWORD oldProtect;

    // Change memory protection
    if (!VirtualProtectEx(hProcess, address, size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        PrintError("VirtualProtectEx");
        return false;
    }

    // Write memory
    SIZE_T bytesWritten;
    bool success = WriteProcessMemory(hProcess, address, buffer, size, &bytesWritten);

    if (!success) {
        PrintError("WriteProcessMemory");
    } else if (bytesWritten != size) {
        PrintErrorMsg("Partial write occurred");
        success = false;
    }

    // Restore memory protection
    DWORD temp;
    VirtualProtectEx(hProcess, address, size, oldProtect, &temp);

    return success;
}

} // namespace ProcessUtils
