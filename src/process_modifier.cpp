#include "process_utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace ProcessUtils;

void PrintUsage(const char* programName) {
    std::cout << "\n=== Process Memory Modifier ===" << std::endl;
    std::cout << "Educational tool for process memory manipulation\n" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  " << programName << " <process_name> <function_name> <hex_value>" << std::endl;
    std::cout << "\nExamples:" << std::endl;
    std::cout << "  " << programName << " notepad.exe GetProcAddress 0x12345678" << std::endl;
    std::cout << "  " << programName << " calc.exe LoadLibraryA 0xDEADBEEF" << std::endl;
    std::cout << "\nNotes:" << std::endl;
    std::cout << "  - Requires Administrator privileges" << std::endl;
    std::cout << "  - Use only for authorized security research" << std::endl;
    std::cout << "  - Process name must include .exe extension" << std::endl;
    std::cout << "  - Hex value must start with 0x" << std::endl;
    std::cout << std::endl;
}

unsigned long long ParseHexValue(const char* hexStr) {
    unsigned long long value = 0;
    std::stringstream ss;

    // Remove 0x prefix if present
    if (hexStr[0] == '0' && (hexStr[1] == 'x' || hexStr[1] == 'X')) {
        hexStr += 2;
    }

    ss << std::hex << hexStr;
    ss >> value;

    return value;
}

int main(int argc, char* argv[]) {
    EnableConsoleColors(true);

    std::cout << "\n";
    PrintInfo("Process Memory Modifier v1.0");
    PrintInfo("Educational Security Research Tool");
    std::cout << "\n";

    // Check arguments
    if (argc < 4) {
        PrintErrorMsg("Invalid number of arguments");
        PrintUsage(argv[0]);
        return 1;
    }

    const char* processName = argv[1];
    const char* functionName = argv[2];
    const char* hexValueStr = argv[3];

    // Parse hex value
    unsigned long long newValue = ParseHexValue(hexValueStr);

    PrintInfo(std::string("Target Process: ") + processName);
    PrintInfo(std::string("Target Function: ") + functionName);

    std::stringstream ss;
    ss << "New Value: 0x" << std::hex << std::uppercase << newValue;
    PrintInfo(ss.str());
    std::cout << "\n";

    // Step 1: Find process
    PrintInfo("Searching for process...");
    DWORD procId = GetProcessIdByName(processName);
    if (procId == 0) {
        PrintErrorMsg("Process not found. Is it running?");
        return 2;
    }

    ss.str("");
    ss << "Process found - PID: " << std::dec << procId;
    PrintSuccess(ss.str());

    // Step 2: Open process
    PrintInfo("Opening process...");
    HANDLE hProcess = OpenProcess(
        PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION,
        FALSE,
        procId
    );

    if (!hProcess) {
        PrintErrorMsg("Failed to open process");
        PrintWarning("Try running as Administrator!");
        return 3;
    }

    PrintSuccess("Process opened successfully");

    // Step 3: Find kernel32.dll
    PrintInfo("Locating kernel32.dll in target process...");
    HMODULE hRemoteKernel32 = GetRemoteModuleHandle(hProcess, "kernel32.dll");
    if (!hRemoteKernel32) {
        PrintErrorMsg("Failed to locate kernel32.dll");
        CloseHandle(hProcess);
        return 4;
    }

    ss.str("");
    ss << "kernel32.dll found at: 0x" << std::hex << std::uppercase << (DWORD_PTR)hRemoteKernel32;
    PrintSuccess(ss.str());

    // Step 4: Find target function
    PrintInfo(std::string("Locating function: ") + functionName);
    FARPROC pTargetFunction = GetRemoteProcAddress(hProcess, hRemoteKernel32, functionName);
    if (!pTargetFunction) {
        PrintErrorMsg("Failed to locate target function");
        PrintWarning("Function may not exist in kernel32.dll");
        CloseHandle(hProcess);
        return 5;
    }

    ss.str("");
    ss << "Function found at: 0x" << std::hex << std::uppercase << (DWORD_PTR)pTargetFunction;
    PrintSuccess(ss.str());

    // Step 5: Read old value
    PrintInfo("Reading current value...");
    unsigned long long oldValue = 0;
    void* pTargetAddress = (void*)pTargetFunction;

    if (ReadProcessMemorySafe(hProcess, pTargetAddress, &oldValue, sizeof(oldValue))) {
        ss.str("");
        ss << "Current value: 0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << oldValue;
        PrintSuccess(ss.str());
    } else {
        PrintWarning("Could not read current value (continuing anyway)");
    }

    // Step 6: Write new value
    std::cout << "\n";
    PrintInfo("Writing new value to memory...");

    if (WriteProcessMemorySafe(hProcess, pTargetAddress, &newValue, sizeof(newValue))) {
        PrintSuccess("Memory write successful!");

        // Step 7: Verify
        PrintInfo("Verifying write operation...");
        unsigned long long verifyValue = 0;

        if (ReadProcessMemorySafe(hProcess, pTargetAddress, &verifyValue, sizeof(verifyValue))) {
            if (verifyValue == newValue) {
                ss.str("");
                ss << "Verification successful! Value is now: 0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << verifyValue;
                PrintSuccess(ss.str());
            } else {
                ss.str("");
                ss << "Verification failed! Read back: 0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << verifyValue;
                PrintErrorMsg(ss.str());
            }
        }
    } else {
        PrintErrorMsg("Memory write failed");
        PrintWarning("The target memory may be protected or the process may have anti-tampering measures");
        CloseHandle(hProcess);
        return 6;
    }

    // Cleanup
    CloseHandle(hProcess);

    std::cout << "\n";
    PrintSuccess("Operation completed successfully!");
    std::cout << "\n";

    return 0;
}
