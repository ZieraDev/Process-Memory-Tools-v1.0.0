# Contributing to Process Memory Tools

Thank you for your interest in contributing to Process Memory Tools! This document provides guidelines for contributing to the project.

## Code of Conduct

By participating in this project, you agree to:

- Use the tools only for legal and ethical purposes
- Respect intellectual property and terms of service
- Contribute code that follows security best practices
- Be respectful and constructive in all interactions

## How to Contribute

### Reporting Bugs

If you find a bug, please open an issue with:

1. **Clear title**: Describe the bug concisely
2. **Environment**: OS version, compiler version, build method
3. **Steps to reproduce**: Detailed steps to reproduce the issue
4. **Expected behavior**: What should happen
5. **Actual behavior**: What actually happens
6. **Logs/Screenshots**: Any relevant output or error messages

### Suggesting Features

For feature requests:

1. Check existing issues to avoid duplicates
2. Describe the feature and its use case
3. Explain why it would be useful
4. Provide examples if possible

### Pull Requests

#### Before Submitting

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/my-feature`
3. **Test your changes**: Ensure everything compiles and works
4. **Follow code style**: Match the existing code style
5. **Update documentation**: Update README.md or USAGE.md if needed

#### Code Style Guidelines

**C++ Style:**
```cpp
// Use descriptive variable names
DWORD processId = GetProcessIdByName(processName);

// Add comments for complex logic
// Calculate function offset using local module as reference
DWORD_PTR offset = (DWORD_PTR)localFunction - (DWORD_PTR)hLocalModule;

// Use namespace consistently
namespace ProcessUtils {
    void MyFunction() {
        // Implementation
    }
}

// Proper error handling
if (!ReadProcessMemory(hProcess, address, buffer, size, &bytesRead)) {
    PrintError("ReadProcessMemory");
    return false;
}
```

**Documentation Style:**
```markdown
## Clear Headings

Concise descriptions with examples.

### Examples

\```bash
# Comment explaining the command
ProcessModifier.exe target.exe Function 0x12345678
\```
```

#### Commit Messages

Use clear, descriptive commit messages:

```
Good:
✅ Add support for custom module targeting
✅ Fix memory leak in process enumeration
✅ Update documentation with new examples

Bad:
❌ update
❌ fix stuff
❌ changes
```

#### Pull Request Process

1. Update the README.md with details of changes if applicable
2. Update the USAGE.md with new features or commands
3. The PR will be reviewed by maintainers
4. Address any feedback or requested changes
5. Once approved, it will be merged

### Areas for Contribution

We welcome contributions in:

#### Code Improvements
- Bug fixes
- Performance optimizations
- New features (that align with project goals)
- Better error handling
- Cross-platform compatibility (if feasible)

#### Documentation
- Improved explanations
- More examples
- Better troubleshooting guides
- Translations (if appropriate)

#### Testing
- Test cases
- Edge case handling
- Security testing
- Compatibility testing

#### Tools and Scripts
- Build automation improvements
- Installation scripts
- Configuration templates

## Development Setup

### Prerequisites

- Windows 10/11
- Visual Studio 2019+ or MinGW-w64
- CMake 3.15+
- Git

### Building from Source

```bash
# Clone your fork
git clone https://github.com/YOUR_USERNAME/ProcessMemoryTools.git
cd ProcessMemoryTools

# Create feature branch
git checkout -b feature/my-feature

# Build
mkdir build && cd build
cmake ..
cmake --build . --config Release

# Test your changes
cd bin/Release
# Run tests here
```

### Testing Checklist

Before submitting a PR, verify:

- [ ] Code compiles without warnings
- [ ] Existing functionality still works
- [ ] New features are documented
- [ ] Code follows project style
- [ ] No security vulnerabilities introduced
- [ ] Changes work on Windows 10 and 11
- [ ] Administrator privileges are properly handled

## Security Considerations

When contributing, keep in mind:

### Do's ✅
- Validate all user inputs
- Handle errors gracefully
- Use minimal required privileges
- Document security implications
- Follow secure coding practices

### Don'ts ❌
- Don't add features that encourage malicious use
- Don't bypass security without documentation
- Don't ignore memory safety
- Don't add unnecessary privileges
- Don't hardcode sensitive information

## Legal and Ethical Guidelines

All contributions must:

1. **Be original work** or properly attributed
2. **Not violate** any laws or regulations
3. **Not enable** illegal activities
4. **Include proper** legal disclaimers if needed
5. **Respect** intellectual property rights

## Questions?

If you have questions about contributing:

1. Check existing documentation
2. Search existing issues
3. Open a new issue with the "question" label
4. Contact the maintainer: ZieraDev

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

Thank you for helping make Process Memory Tools better!

**Author**: ZieraDev
**Project**: Process Memory Tools
**GitHub**: [github.com/ZieraDev/ProcessMemoryTools](https://github.com/ZieraDev/ProcessMemoryTools)
