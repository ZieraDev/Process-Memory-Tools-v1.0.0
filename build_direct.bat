@echo off
REM Direct build script without CMake
REM Author: ZieraDev
REM Project: Process Memory Tools

echo ========================================
echo Process Memory Tools - Direct Build
echo ========================================
echo.

REM Create output directory
if not exist "bin" mkdir bin

REM Detect compiler
where cl >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo [*] Using MSVC compiler
    goto :build_msvc
)

where g++ >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo [*] Using MinGW compiler
    goto :build_mingw
)

echo [ERROR] No compiler found!
echo Please install MSVC or MinGW-w64
pause
exit /b 1

:build_msvc
echo.
echo [*] Building ProcessModifier.exe...
cl /EHsc /O2 /I.\include /Fe:bin\ProcessModifier.exe src\process_modifier.cpp src\process_utils.cpp psapi.lib /link /MANIFESTUAC:"level='requireAdministrator'"
if %ERRORLEVEL% NEQ 0 goto :error

echo [*] Building WindowController.exe...
cl /EHsc /O2 /I.\include /Fe:bin\WindowController.exe src\window_controller.cpp src\process_utils.cpp user32.lib psapi.lib /link /MANIFESTUAC:"level='requireAdministrator'"
if %ERRORLEVEL% NEQ 0 goto :error

REM Clean up intermediate files
del *.obj 2>nul

goto :success

:build_mingw
echo.
echo [*] Building ProcessModifier.exe...
g++ -O2 -o bin\ProcessModifier.exe src\process_modifier.cpp src\process_utils.cpp -I./include -lpsapi -static
if %ERRORLEVEL% NEQ 0 goto :error

echo [*] Building WindowController.exe...
g++ -O2 -o bin\WindowController.exe src\window_controller.cpp src\process_utils.cpp -I./include -luser32 -lpsapi -static
if %ERRORLEVEL% NEQ 0 goto :error

goto :success

:error
echo.
echo [ERROR] Build failed!
pause
exit /b 1

:success
echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Executables are in: bin\
echo - ProcessModifier.exe
echo - WindowController.exe
echo.
echo Run as Administrator to use the tools.
echo.
pause
