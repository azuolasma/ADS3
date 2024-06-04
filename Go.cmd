@echo off
rem Check if the script is running on a faculty machine or a personal PC.
if .%USERDOMAIN% == .LINA goto savasPC

echo Setting up environment for MIF computer...
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto toliau

:savasPC
echo Setting up environment for personal PC...
path C:\Program Files\CodeBlocks\MinGW\bin\;%path%
mingw32-make.exe

:toliau
echo Running Typical Case Test
loan_manager.exe 10000 5 1 12
echo.

echo Running Edge Case Test
loan_manager.exe 500 100 5 1
echo.

echo Running Boundary Condition Test
loan_manager.exe 0 5 1 12
echo.

pause
