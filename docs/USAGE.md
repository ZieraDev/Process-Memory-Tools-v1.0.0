# Usage Guide - Process Memory Tools

Detailed usage guide for Process Memory Tools by ZieraDev.

## Table of Contents

1. [Getting Started](#getting-started)
2. [Process Memory Modifier](#process-memory-modifier)
3. [Window Controller](#window-controller)
4. [Common Use Cases](#common-use-cases)
5. [Troubleshooting](#troubleshooting)

---

## Getting Started

### Prerequisites

Before using these tools, ensure:

1. **Administrator Privileges**: Run your terminal/command prompt as Administrator
2. **Target Process Running**: The process you want to manipulate must be running
3. **Proper Permissions**: Ensure you have authorization to manipulate the target process

### Quick Start

```bash
# 1. Build the project
cd ProcessMemoryTools
mkdir build && cd build
cmake ..
cmake --build . --config Release

# 2. Navigate to executables
cd bin\Release

# 3. Run tools (as Administrator)
.\ProcessModifier.exe notepad.exe GetProcAddress 0x12345678
.\WindowController.exe notepad.exe 100 100
```

---

## Process Memory Modifier

### Overview

The Process Memory Modifier allows you to read and write memory in remote processes at the function level.

### Syntax

```bash
ProcessModifier.exe <process_name> <function_name> <hex_value>
```

### Parameters

- **process_name**: Target process executable (e.g., `notepad.exe`)
- **function_name**: Target function in kernel32.dll (e.g., `GetProcAddress`)
- **hex_value**: New value to write (hex format, e.g., `0x12345678`)

### Examples

#### Example 1: Modify GetProcAddress

```bash
ProcessModifier.exe notepad.exe GetProcAddress 0xDEADBEEF
```

**Output:**
```
[*] Process Memory Modifier v1.0
[*] Educational Security Research Tool

[*] Target Process: notepad.exe
[*] Target Function: GetProcAddress
[*] New Value: 0xDEADBEEF

[*] Searching for process...
[+] Process found - PID: 12345
[*] Opening process...
[+] Process opened successfully
[*] Locating kernel32.dll in target process...
[+] kernel32.dll found at: 0x7FFE12340000
[*] Locating function: GetProcAddress
[+] Function found at: 0x7FFE12345678
[*] Reading current value...
[+] Current value: 0x8B4C24048B542408
[*] Writing new value to memory...
[+] Memory write successful!
[*] Verifying write operation...
[+] Verification successful! Value is now: 0x00000000DEADBEEF
[+] Operation completed successfully!
```

#### Example 2: Modify LoadLibraryA

```bash
ProcessModifier.exe calc.exe LoadLibraryA 0x90909090
```

### How It Works

1. **Process Discovery**: Locates the target process by name
2. **Module Enumeration**: Finds kernel32.dll in the target process
3. **Function Resolution**: Calculates the address of the target function
4. **Memory Read**: Reads the current value at that address
5. **Memory Write**: Writes the new value with proper memory protection handling
6. **Verification**: Reads back to confirm the write succeeded

### Advanced Usage

#### Writing 64-bit Values

```bash
# Write a full 64-bit value
ProcessModifier.exe target.exe GetProcAddress 0x123456789ABCDEF0
```

#### Targeting Different Functions

You can target any exported function from kernel32.dll:

- `GetProcAddress`
- `LoadLibraryA`
- `LoadLibraryW`
- `CreateFileA`
- `ReadFile`
- `WriteFile`
- And many more...

---

## Window Controller

### Overview

The Window Controller provides programmatic control over window positions and states.

### Syntax

```bash
WindowController.exe <process_name> <x> <y> [mode]
```

### Parameters

- **process_name**: Target process executable (e.g., `notepad.exe`)
- **x**: X-coordinate in pixels
- **y**: Y-coordinate in pixels
- **mode**: Operation mode (optional, default: `move`)

### Modes

| Mode | Description |
|------|-------------|
| `move` | Move window once to specified position (default) |
| `center` | Center window on screen (ignores x/y) |
| `track` | Continuously move window to position |

### Examples

#### Example 1: Move Window Once

```bash
WindowController.exe notepad.exe 100 100
```

**Output:**
```
[*] Window Controller v1.0
[*] Educational Window Manipulation Tool

[*] Target Process: notepad.exe
[*] Target Position: (100, 100)
[*] Mode: move

[*] Searching for process...
[+] Process found - PID: 12345
[*] Searching for window...
[+] Window found - Handle: 0x1234ABCD

[*] Window Information:
  Title: Untitled - Notepad
  Position: (200, 200)
  Size: 800x600
  Handle: 0x1234ABCD

[*] Moving window...
[+] Window moved to (100, 100)
[+] Operation completed successfully!
```

#### Example 2: Center Window

```bash
WindowController.exe chrome.exe 0 0 center
```

Coordinates are ignored in center mode. The window will be centered on the primary monitor.

#### Example 3: Track Window Position

```bash
WindowController.exe notepad.exe 500 300 track
```

**Output:**
```
[*] Window Controller v1.0
...
[*] Tracking mode enabled - Press Ctrl+C to stop
[!] Window will be moved to specified position every 100ms
[*] Moved window 10 times
[*] Moved window 20 times
[*] Moved window 30 times
^C
[+] Tracking stopped after 35 moves
[+] Operation completed successfully!
```

**Note**: In track mode, the window will continuously be reset to the specified position. This is useful for testing or keeping a window in a specific location.

---

## Common Use Cases

### Use Case 1: Security Research on Your Own Application

**Scenario**: You're testing how your application handles memory corruption.

```bash
# Start your application
start MyApp.exe

# Modify a function pointer to see how it handles corruption
ProcessModifier.exe MyApp.exe GetProcAddress 0x00000000
```

### Use Case 2: CTF Challenge

**Scenario**: A CTF challenge requires manipulating a process.

```bash
# The challenge binary is running
ProcessModifier.exe challenge.exe TargetFunction 0x41414141
```

### Use Case 3: Window Management Automation

**Scenario**: You want to automate window positioning for a specific workflow.

```bash
# Position multiple application windows
WindowController.exe vscode.exe 0 0
WindowController.exe chrome.exe 960 0
WindowController.exe terminal.exe 0 540
```

### Use Case 4: Debugging Window Behavior

**Scenario**: Test how an application handles rapid window movements.

```bash
# Track mode will continuously move the window
WindowController.exe TestApp.exe 100 100 track
```

---

## Troubleshooting

### Error: "Process not found"

**Cause**: The target process is not running or the name is incorrect.

**Solution**:
```bash
# Check process name in Task Manager
# Make sure to include .exe extension
ProcessModifier.exe notepad.exe ...  # Correct
ProcessModifier.exe notepad ...      # Incorrect
```

### Error: "Failed to open process"

**Cause**: Insufficient privileges.

**Solution**:
1. Run Command Prompt as Administrator
2. Right-click Command Prompt → "Run as administrator"

### Error: "VirtualProtectEx failed"

**Cause**: Target memory region is protected or the process has anti-tampering measures.

**Solution**:
- Some processes have protection mechanisms that prevent memory modification
- Try a different target process or function
- This is expected behavior for protected processes

### Error: "No visible window found"

**Cause**: The process doesn't have a visible window.

**Solution**:
- Some processes run in the background without windows (e.g., services)
- Try a different process with a GUI
- Use Task Manager to verify the process has a window

### Error: "Module not found: kernel32.dll"

**Cause**: Very rare - kernel32.dll is not loaded in the target process.

**Solution**:
- This should never happen with normal processes
- The target might be a minimal process or using unusual techniques
- Try a different target process

---

## Safety and Best Practices

### 1. Always Test in Isolated Environments

```bash
# Use virtual machines for testing
# Don't test on production systems
```

### 2. Verify Target Process

```bash
# Make sure you're targeting the correct process
# Double-check the process name before executing
```

### 3. Document Your Changes

```bash
# Keep notes of what you modified
# Record original values before modification
```

### 4. Handle Errors Gracefully

The tools provide detailed error messages. Always read them:

```
[-] Error message tells you what went wrong
[!] Warning message provides additional context
[*] Info message shows progress
[+] Success message confirms operation
```

### 5. Respect Legal Boundaries

- Only use on processes you own or have explicit permission to modify
- Never use for cheating in online games
- Never use to bypass security measures without authorization
- Use only for educational and authorized security research

---

## Advanced Topics

### Understanding Memory Protection

Windows protects memory pages with different flags:
- `PAGE_READONLY`: Can read, cannot write
- `PAGE_READWRITE`: Can read and write
- `PAGE_EXECUTE_READ`: Can read and execute
- `PAGE_EXECUTE_READWRITE`: Full access

The tools automatically handle protection changes using `VirtualProtectEx`.

### Function Address Resolution

The tools use offset calculation:

```
Local kernel32.dll base: 0x7FFE12340000
Function offset:         0x5678
Remote kernel32.dll base: 0x7FFE98760000
Remote function address: 0x7FFE98765678
```

This works because kernel32.dll has the same structure across processes.

---

## Getting Help

If you encounter issues:

1. Check the error messages - they're designed to be helpful
2. Review this documentation
3. Open an issue on GitHub: [github.com/ZieraDev/ProcessMemoryTools](https://github.com/ZieraDev/ProcessMemoryTools)
4. Ensure you're using the latest version

---

**Author**: ZieraDev
**License**: MIT
**Project**: Process Memory Tools
