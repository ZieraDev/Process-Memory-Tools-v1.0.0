@echo off
REM Build script for MSVC compiler
REM Author: ZieraDev
REM Project: Process Memory Tools

echo ========================================
echo Process Memory Tools - MSVC Build
echo ========================================
echo.

REM Check for Visual Studio
where cl >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] MSVC compiler not found!
    echo Please run this from a Visual Studio Developer Command Prompt
    echo or run vcvarsall.bat first.
    pause
    exit /b 1
)

echo [*] MSVC compiler found
echo.

REM Create build directory
if not exist "build" mkdir build
cd build

echo [*] Configuring with CMake...
cmake .. -G "Visual Studio 17 2022"
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake configuration failed!
    cd ..
    pause
    exit /b 1
)

echo [*] Building Release configuration...
cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Build failed!
    cd ..
    pause
    exit /b 1
)

cd ..

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Executables are in: build\bin\Release\
echo - ProcessModifier.exe
echo - WindowController.exe
echo.
echo Run as Administrator to use the tools.
echo.
pause
