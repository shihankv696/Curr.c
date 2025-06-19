@echo off
echo Installing Curr.s Data Structures Library...

REM Create install directory
mkdir C:\currc\include
mkdir C:\currc\Library

REM Copy header files
xcopy /Y /E include\* C:\currc\include\

REM Copy DLL (Adjust if you`re using .lib or .dll)
xcopy /Y lib\currc.dll C:\curr\lib\

echo ✅ Installed successfully!
echo 👉 Usage:
echo Include headers from C:\currc\include
echo Link with currc.dll from C:\currc\lib
pause