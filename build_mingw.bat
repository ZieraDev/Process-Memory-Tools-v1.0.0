@echo off
REM Build script for MinGW compiler
REM Author: ZieraDev
REM Project: Process Memory Tools

echo ========================================
echo Process Memory Tools - MinGW Build
echo ========================================
echo.

REM Check for MinGW
where g++ >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] MinGW g++ compiler not found!
    echo Please install MinGW-w64 and add it to PATH.
    pause
    exit /b 1
)

echo [*] MinGW compiler found
g++ --version | findstr "g++"
echo.

REM Create build directory
if not exist "build" mkdir build
cd build

echo [*] Configuring with CMake...
cmake .. -G "MinGW Makefiles"
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake configuration failed!
    cd ..
    pause
    exit /b 1
)

echo [*] Building...
cmake --build .
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
echo Executables are in: build\bin\
echo - ProcessModifier.exe
echo - WindowController.exe
echo.
echo Run as Administrator to use the tools.
echo.
pause
