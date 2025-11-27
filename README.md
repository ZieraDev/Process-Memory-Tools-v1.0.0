# Process Memory Tools

A collection of educational Windows process manipulation tools for security research, reverse engineering, and authorized penetration testing.

## Overview

This project provides utilities for:
- **Process Memory Modification**: Read and write memory in remote processes
- **Window Interaction**: Programmatic control of window positions and states
- **Process Discovery**: Find and interact with running processes

## Features

- ✅ Cross-process memory reading/writing with proper protection handling
- ✅ Remote function address resolution
- ✅ Process enumeration and searching
- ✅ Safe memory operations with error handling
- ✅ Detailed logging and diagnostics
- ✅ Modular architecture

## Project Structure

```
ProcessMemoryTools/
├── src/
│   ├── process_modifier.cpp    # Memory modification tool
│   ├── window_controller.cpp   # Window interaction tool
│   └── process_utils.cpp       # Shared utility functions
├── include/
│   └── process_utils.h         # Header file for utilities
├── examples/
│   └── config_example.txt      # Configuration examples
├── docs/
│   └── USAGE.md               # Detailed usage guide
├── CMakeLists.txt             # Build configuration
├── README.md                  # This file
└── LICENSE                    # MIT License
```

## Requirements

- **OS**: Windows 10/11
- **Compiler**: MSVC 2019+ or MinGW-w64
- **Build System**: CMake 3.15+
- **Permissions**: Administrator privileges required

## Building

### Using CMake (Recommended)

```bash
# Clone the repository
git clone https://github.com/ZieraDev/ProcessMemoryTools.git
cd ProcessMemoryTools

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build . --config Release
```

### Using MSVC directly

```bash
cl /EHsc /I..\include /Fe:process_modifier.exe ..\src\process_modifier.cpp ..\src\process_utils.cpp psapi.lib
cl /EHsc /I..\include /Fe:window_controller.exe ..\src\window_controller.cpp ..\src\process_utils.cpp user32.lib
```

### Using MinGW

```bash
g++ -o process_modifier.exe src/process_modifier.cpp src/process_utils.cpp -I./include -lpsapi -static
g++ -o window_controller.exe src/window_controller.cpp src/process_utils.cpp -I./include -luser32 -static
```

## Usage

### Process Memory Modifier

Modify memory in a running process:

```bash
# Run as Administrator
.\process_modifier.exe <process_name> <target_function> <new_value>

# Example
.\process_modifier.exe notepad.exe GetProcAddress 0x12345678
```

### Window Controller

Control window positions and states:

```bash
.\window_controller.exe <process_name> <x> <y>

# Example
.\window_controller.exe notepad.exe 100 100
```

## Legal and Ethical Use

⚠️ **IMPORTANT**: This software is provided for **educational and authorized security research purposes only**.

### Permitted Uses:
- ✅ Authorized penetration testing engagements
- ✅ CTF (Capture The Flag) competitions
- ✅ Security research in controlled environments
- ✅ Debugging your own applications
- ✅ Educational purposes in sandboxed environments

### Prohibited Uses:
- ❌ Unauthorized access to computer systems
- ❌ Game cheating or ToS violations
- ❌ Malware development
- ❌ Any illegal activities

**You are solely responsible for ensuring your use complies with all applicable laws and regulations.**

## Security Considerations

- Always run with minimum required privileges
- Validate all inputs and target processes
- Use in isolated/sandboxed environments for testing
- Be aware of anti-cheat and security software
- Respect intellectual property and terms of service

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

## Disclaimer

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED. THE AUTHORS ARE NOT RESPONSIBLE FOR ANY MISUSE OR DAMAGE CAUSED BY THIS SOFTWARE.

## License

MIT License - see [LICENSE](LICENSE) file for details.

## Author

Created by **ZieraDev** for educational purposes and security research.

GitHub: [github.com/ZieraDev](https://github.com/ZieraDev)

## Acknowledgments

- Windows API Documentation
- Process Hacker Project
- Cheat Engine Community (for educational reversing techniques)

---

**Remember**: With great power comes great responsibility. Use these tools ethically and legally.
