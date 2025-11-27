#ifndef PROCESS_UTILS_H
#define PROCESS_UTILS_H

#include <windows.h>
#include <string>

namespace ProcessUtils {

/**
 * @brief Find process ID by executable name
 * @param processName Name of the executable (e.g., "notepad.exe")
 * @return Process ID or 0 if not found
 */
DWORD GetProcessIdByName(const char* processName);

/**
 * @brief Find window handle by process ID
 * @param processId The process ID to search for
 * @return Window handle or nullptr if not found
 */
HWND GetWindowByProcessId(DWORD processId);

/**
 * @brief Get module handle in remote process
 * @param hProcess Handle to the target process
 * @param moduleName Name of the module (e.g., "kernel32.dll")
 * @return Module handle or nullptr if not found
 */
HMODULE GetRemoteModuleHandle(HANDLE hProcess, const char* moduleName);

/**
 * @brief Get function address in remote process
 * @param hProcess Handle to the target process
 * @param hRemoteModule Remote module handle
 * @param functionName Name of the function
 * @return Function address or nullptr if not found
 */
FARPROC GetRemoteProcAddress(HANDLE hProcess, HMODULE hRemoteModule, const char* functionName);

/**
 * @brief Safely read memory from remote process
 * @param hProcess Handle to the target process
 * @param address Address to read from
 * @param buffer Buffer to store read data
 * @param size Number of bytes to read
 * @return true if successful, false otherwise
 */
bool ReadProcessMemorySafe(HANDLE hProcess, LPCVOID address, LPVOID buffer, SIZE_T size);

/**
 * @brief Safely write memory to remote process
 * @param hProcess Handle to the target process
 * @param address Address to write to
 * @param buffer Data to write
 * @param size Number of bytes to write
 * @return true if successful, false otherwise
 */
bool WriteProcessMemorySafe(HANDLE hProcess, LPVOID address, LPCVOID buffer, SIZE_T size);

/**
 * @brief Print detailed error message
 * @param context Error context description
 */
void PrintError(const char* context);

/**
 * @brief Print colored console message
 * @param message The message to print
 * @param color Console color attribute
 */
void PrintColored(const std::string& message, WORD color);

/**
 * @brief Print success message in green
 */
void PrintSuccess(const std::string& message);

/**
 * @brief Print error message in red
 */
void PrintErrorMsg(const std::string& message);

/**
 * @brief Print info message in cyan
 */
void PrintInfo(const std::string& message);

/**
 * @brief Print warning message in yellow
 */
void PrintWarning(const std::string& message);

/**
 * @brief Enable or disable console colors
 * @param enable true to enable colors, false to disable
 */
void EnableConsoleColors(bool enable = true);

} // namespace ProcessUtils

#endif // PROCESS_UTILS_H
