#include "process_utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

using namespace ProcessUtils;

void PrintUsage(const char* programName) {
    std::cout << "\n=== Window Controller ===" << std::endl;
    std::cout << "Educational tool for window manipulation\n" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  " << programName << " <process_name> <x> <y> [mode]" << std::endl;
    std::cout << "\nModes:" << std::endl;
    std::cout << "  move     - Move window once (default)" << std::endl;
    std::cout << "  track    - Continuously track and move window" << std::endl;
    std::cout << "  center   - Center window on screen" << std::endl;
    std::cout << "\nExamples:" << std::endl;
    std::cout << "  " << programName << " notepad.exe 100 100" << std::endl;
    std::cout << "  " << programName << " calc.exe 0 0 move" << std::endl;
    std::cout << "  " << programName << " chrome.exe 0 0 center" << std::endl;
    std::cout << "  " << programName << " notepad.exe 50 50 track" << std::endl;
    std::cout << "\nNotes:" << std::endl;
    std::cout << "  - Process name must include .exe extension" << std::endl;
    std::cout << "  - Coordinates are in pixels from top-left corner" << std::endl;
    std::cout << "  - Press Ctrl+C to stop tracking mode" << std::endl;
    std::cout << std::endl;
}

void CenterWindow(HWND hwnd) {
    // Get screen dimensions
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Get window dimensions
    RECT rect;
    GetWindowRect(hwnd, &rect);
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    // Calculate centered position
    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    // Move window
    SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    std::stringstream ss;
    ss << "Window centered at (" << x << ", " << y << ")";
    PrintSuccess(ss.str());
}

void MoveWindow(HWND hwnd, int x, int y) {
    if (SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)) {
        std::stringstream ss;
        ss << "Window moved to (" << x << ", " << y << ")";
        PrintSuccess(ss.str());
    } else {
        PrintErrorMsg("Failed to move window");
        PrintError("SetWindowPos");
    }
}

void TrackWindow(HWND hwnd, int x, int y) {
    PrintInfo("Tracking mode enabled - Press Ctrl+C to stop");
    PrintWarning("Window will be moved to specified position every 100ms");

    int moveCount = 0;

    while (true) {
        // Check if window still exists
        if (!IsWindow(hwnd)) {
            PrintErrorMsg("Window no longer exists");
            break;
        }

        // Move window
        if (SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)) {
            moveCount++;

            // Print status every 10 moves (1 second)
            if (moveCount % 10 == 0) {
                std::stringstream ss;
                ss << "Moved window " << moveCount << " times";
                PrintInfo(ss.str());
            }
        } else {
            PrintErrorMsg("Failed to move window");
            break;
        }

        // Sleep for 100ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::stringstream ss;
    ss << "Tracking stopped after " << moveCount << " moves";
    PrintSuccess(ss.str());
}

void ShowWindowInfo(HWND hwnd) {
    // Get window title
    char title[256];
    GetWindowTextA(hwnd, title, sizeof(title));

    // Get window position and size
    RECT rect;
    GetWindowRect(hwnd, &rect);

    std::cout << "\n";
    PrintInfo("Window Information:");
    std::cout << "  Title: " << title << std::endl;

    std::stringstream ss;
    ss << "  Position: (" << rect.left << ", " << rect.top << ")";
    std::cout << "  " << ss.str() << std::endl;

    ss.str("");
    ss << "  Size: " << (rect.right - rect.left) << "x" << (rect.bottom - rect.top);
    std::cout << "  " << ss.str() << std::endl;

    ss.str("");
    ss << "  Handle: 0x" << std::hex << std::uppercase << (DWORD_PTR)hwnd;
    std::cout << "  " << ss.str() << std::endl;
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    EnableConsoleColors(true);

    std::cout << "\n";
    PrintInfo("Window Controller v1.0");
    PrintInfo("Educational Window Manipulation Tool");
    std::cout << "\n";

    // Check arguments
    if (argc < 4) {
        PrintErrorMsg("Invalid number of arguments");
        PrintUsage(argv[0]);
        return 1;
    }

    const char* processName = argv[1];
    int x = std::atoi(argv[2]);
    int y = std::atoi(argv[3]);
    std::string mode = (argc >= 5) ? argv[4] : "move";

    PrintInfo(std::string("Target Process: ") + processName);

    std::stringstream ss;
    ss << "Target Position: (" << x << ", " << y << ")";
    PrintInfo(ss.str());
    PrintInfo(std::string("Mode: ") + mode);
    std::cout << "\n";

    // Step 1: Find process
    PrintInfo("Searching for process...");
    DWORD procId = GetProcessIdByName(processName);
    if (procId == 0) {
        PrintErrorMsg("Process not found. Is it running?");
        return 2;
    }

    ss.str("");
    ss << "Process found - PID: " << procId;
    PrintSuccess(ss.str());

    // Step 2: Find window
    PrintInfo("Searching for window...");
    HWND hwnd = GetWindowByProcessId(procId);
    if (!hwnd) {
        PrintErrorMsg("No visible window found for this process");
        PrintWarning("The process may not have a GUI window");
        return 3;
    }

    ss.str("");
    ss << "Window found - Handle: 0x" << std::hex << std::uppercase << (DWORD_PTR)hwnd;
    PrintSuccess(ss.str());

    // Show window info
    ShowWindowInfo(hwnd);

    // Execute based on mode
    if (mode == "center") {
        PrintInfo("Centering window on screen...");
        CenterWindow(hwnd);
    } else if (mode == "track") {
        TrackWindow(hwnd, x, y);
    } else if (mode == "move") {
        PrintInfo("Moving window...");
        MoveWindow(hwnd, x, y);
    } else {
        PrintErrorMsg("Unknown mode: " + mode);
        PrintUsage(argv[0]);
        return 4;
    }

    std::cout << "\n";
    PrintSuccess("Operation completed successfully!");
    std::cout << "\n";

    return 0;
}
