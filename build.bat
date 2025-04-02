@echo off
set CC=gcc
set CFLAGS=-Iinclude -Wall -Wextra -Werror
set SRC_DIR=src
set OBJ_DIR=obj
set BIN_DIR=bin
set TARGET=%BIN_DIR%\snake.exe

:: Create necessary directories
if not exist %OBJ_DIR% mkdir %OBJ_DIR%
if not exist %BIN_DIR% mkdir %BIN_DIR%

:: Compile source files
for %%f in (%SRC_DIR%\*.c) do (
    set filename=%%~nf
    %CC% %CFLAGS% -c %%f -o %OBJ_DIR%\%%~nf.o
)

:: Link object files
%CC% %OBJ_DIR%\*.o -o %TARGET%

echo Build complete. Run "%TARGET%" to start the game.