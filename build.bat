@echo off
set MINGW_BIN=C:\Users\hp\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin
set PATH=%MINGW_BIN%;%PATH%

echo Setting up build directory...
cmake -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER="%MINGW_BIN%\g++.exe" -DCMAKE_C_COMPILER="%MINGW_BIN%\gcc.exe" -DCMAKE_MAKE_PROGRAM="%MINGW_BIN%\mingw32-make.exe"
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed!
    exit /b %ERRORLEVEL%
)

echo Building project target executables...
cmake --build build --parallel
if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed!
    exit /b %ERRORLEVEL%
)

echo Build completed successfully!
