# Process Memory Tools - Project Overview

**Author**: ZieraDev
**Version**: 1.0.0
**License**: MIT
**GitHub**: https://github.com/ZieraDev/ProcessMemoryTools

---

## Project Summary

Process Memory Tools is a collection of educational Windows utilities for process manipulation, designed for security research, reverse engineering, and authorized penetration testing. The project demonstrates advanced Windows API usage including process enumeration, memory manipulation, and window management.

## Project Structure

```
ProcessMemoryTools/
├── src/                          # Source code
│   ├── process_modifier.cpp      # Memory modification tool
│   ├── window_controller.cpp     # Window manipulation tool
│   └── process_utils.cpp         # Shared utility functions
│
├── include/                      # Header files
│   └── process_utils.h           # Utility function declarations
│
├── docs/                         # Documentation
│   └── USAGE.md                  # Detailed usage guide
│
├── examples/                     # Examples and templates
│   └── config_example.txt        # Configuration examples
│
├── build/                        # Build output (generated)
│
├── build_msvc.bat               # MSVC build script
├── build_mingw.bat              # MinGW build script
├── build_direct.bat             # Direct build without CMake
├── CMakeLists.txt               # CMake configuration
├── .gitignore                   # Git ignore rules
├── LICENSE                      # MIT License
├── README.md                    # Main documentation
├── CONTRIBUTING.md              # Contribution guidelines
└── PROJECT_OVERVIEW.md          # This file
```

## Components

### 1. Process Memory Modifier (`process_modifier.cpp`)

**Purpose**: Read and write memory in remote processes at the function level.

**Features**:
- Process discovery by name
- Remote module enumeration
- Function address resolution
- Safe memory read/write operations
- Memory protection handling
- Detailed logging and verification

**Use Cases**:
- Security research on your own applications
- CTF challenges
- Memory corruption testing
- Understanding process memory layout

**Example**:
```bash
ProcessModifier.exe notepad.exe GetProcAddress 0x12345678
```

### 2. Window Controller (`window_controller.cpp`)

**Purpose**: Programmatic control of window positions and states.

**Features**:
- Process to window mapping
- Window positioning
- Window centering
- Continuous tracking mode
- Window information display

**Use Cases**:
- Window management automation
- Testing window behavior
- Multi-monitor setup automation
- Debugging window message handling

**Example**:
```bash
WindowController.exe notepad.exe 100 100
WindowController.exe chrome.exe 0 0 center
WindowController.exe app.exe 500 300 track
```

### 3. Process Utilities Library (`process_utils.cpp/h`)

**Purpose**: Shared functionality for process and memory manipulation.

**Functions**:
- `GetProcessIdByName()` - Find process by executable name
- `GetWindowByProcessId()` - Map process to window handle
- `GetRemoteModuleHandle()` - Find module in remote process
- `GetRemoteProcAddress()` - Resolve function address in remote process
- `ReadProcessMemorySafe()` - Safe memory reading
- `WriteProcessMemorySafe()` - Safe memory writing with protection handling
- Colored console output functions
- Error handling and reporting

## Technical Implementation

### Key Technologies

- **Language**: C++17
- **Platform**: Windows 10/11
- **APIs Used**:
  - Windows Process API (CreateToolhelp32Snapshot, Process32First/Next)
  - Memory Management API (ReadProcessMemory, WriteProcessMemory, VirtualProtectEx)
  - Module Management API (EnumProcessModules, GetModuleBaseName)
  - Window Management API (EnumWindows, SetWindowPos, GetWindowRect)
  - Console API (SetConsoleTextAttribute for colored output)

### Architecture

```
┌─────────────────────────────────────────┐
│         User Interface (CLI)            │
├─────────────────────────────────────────┤
│   ProcessModifier   │ WindowController  │
├─────────────────────┴───────────────────┤
│         ProcessUtils Library            │
│  ┌────────────┬──────────┬────────────┐ │
│  │  Process   │  Memory  │   Window   │ │
│  │    Mgmt    │   Mgmt   │    Mgmt    │ │
│  └────────────┴──────────┴────────────┘ │
├─────────────────────────────────────────┤
│           Windows API Layer             │
└─────────────────────────────────────────┘
```

### Memory Safety

The project implements multiple safety mechanisms:

1. **Error Handling**: All API calls are checked and errors are reported
2. **Memory Protection**: VirtualProtectEx is used to safely modify protected memory
3. **Verification**: Write operations are verified by reading back
4. **Safe Wrappers**: All dangerous operations are wrapped in safe functions
5. **Resource Management**: Handles are properly closed after use

## Build System

The project supports multiple build methods:

### Method 1: CMake (Recommended)
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Method 2: MSVC (Visual Studio)
```bash
build_msvc.bat
```

### Method 3: MinGW
```bash
build_mingw.bat
```

### Method 4: Direct Compilation
```bash
build_direct.bat
```

## Documentation

| Document | Description |
|----------|-------------|
| `README.md` | Main project documentation, quick start guide |
| `USAGE.md` | Detailed usage guide with examples |
| `CONTRIBUTING.md` | Guidelines for contributors |
| `LICENSE` | MIT License with legal disclaimer |
| `PROJECT_OVERVIEW.md` | This file - technical overview |
| `config_example.txt` | Configuration and usage examples |

## Security Considerations

### Permitted Uses
✅ Authorized penetration testing
✅ CTF competitions
✅ Security research in controlled environments
✅ Debugging your own applications
✅ Educational purposes in sandboxed environments

### Prohibited Uses
❌ Unauthorized access to computer systems
❌ Game cheating or ToS violations
❌ Malware development
❌ Any illegal activities

### Technical Security

- **Least Privilege**: Tools request only necessary permissions
- **Input Validation**: All user inputs are validated
- **Error Reporting**: Detailed error messages for debugging
- **Safe Defaults**: Conservative default behavior
- **Administrator Requirement**: Explicit admin privilege requirement

## Code Quality

### Features

- ✅ **Modular Design**: Separation of concerns
- ✅ **Error Handling**: Comprehensive error checking
- ✅ **Documentation**: Inline comments and external docs
- ✅ **Logging**: Colored console output for clarity
- ✅ **Portability**: Works with multiple compilers
- ✅ **Safety**: Memory-safe operations
- ✅ **Verification**: Operations are verified

### Code Statistics

```
Language: C++17
Total Lines: ~1000+
Files: 6 source files
Headers: 1
Build Scripts: 3
Documentation: 5 files
```

## Dependencies

**Required**:
- Windows SDK (included with Visual Studio or MinGW)
- Standard C++ Library
- Windows API Libraries: `psapi.lib`, `user32.lib`

**Build Tools**:
- CMake 3.15+ (optional)
- MSVC 2019+ or MinGW-w64
- Git (for version control)

**No External Libraries**: The project uses only Windows API and standard library.

## Future Enhancements

Potential areas for expansion:

1. **Module Selection**: Support for modules beyond kernel32.dll
2. **Pattern Scanning**: Memory pattern search functionality
3. **Hook Detection**: Identify hooks in target processes
4. **DLL Injection**: Educational DLL injection capabilities
5. **GUI Version**: Graphical interface for easier use
6. **Multi-Process**: Batch operations on multiple processes
7. **Configuration Files**: Load settings from config files
8. **Logging**: File-based logging for operations

## Contributing

Contributions are welcome! See `CONTRIBUTING.md` for guidelines.

Areas we'd love help with:
- Bug fixes and testing
- Documentation improvements
- New features (aligned with project goals)
- Performance optimizations
- Better error messages

## Version History

### v1.0.0 (2025-01-27)
- Initial release
- Process Memory Modifier tool
- Window Controller tool
- Comprehensive documentation
- Multiple build system support
- Educational examples

## License

MIT License - See `LICENSE` file for full text.

**TL;DR**: Free to use, modify, and distribute with attribution. No warranty provided.

## Acknowledgments

- **Windows API Documentation** - Microsoft
- **Process Hacker** - Inspiration for process manipulation
- **Cheat Engine Community** - Educational reversing techniques
- **Security Research Community** - Best practices and methodologies

## Contact & Support

- **GitHub**: [github.com/ZieraDev/ProcessMemoryTools](https://github.com/ZieraDev/ProcessMemoryTools)
- **Issues**: Report bugs or request features via GitHub Issues
- **Author**: ZieraDev

---

## Quick Start Checklist

Ready to use Process Memory Tools? Follow these steps:

- [ ] Clone the repository
- [ ] Install build tools (MSVC or MinGW)
- [ ] Run appropriate build script
- [ ] Open terminal as Administrator
- [ ] Navigate to executable directory
- [ ] Run tools with proper arguments
- [ ] Read USAGE.md for detailed examples

## Legal Disclaimer

This software is provided for **educational and authorized security research purposes only**. Users are solely responsible for ensuring their use complies with all applicable laws and regulations. The authors assume no liability for misuse or damages.

---

**Built with ❤️ by ZieraDev for the security research community.**

Last Updated: 2025-01-27
