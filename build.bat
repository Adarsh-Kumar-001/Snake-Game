@echo off
setlocal enabledelayedexpansion

:: Compiler and flags
set CC=gcc
set CFLAGS=-Iinclude -Wall -Wextra -Werror

:: Directories
set SRC_DIR=src
set OBJ_DIR=obj
set BIN_DIR=bin
set TARGET=%BIN_DIR%\snake.exe

:: Check for "clean" argument
if /i "%1"=="clean" (
    echo Cleaning build artifacts...
    del /q "%OBJ_DIR%\*.o" 2>nul
    del /q "%TARGET%" 2>nul
    echo Clean complete.
    exit /b
)

:: Create necessary directories
if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"

:: Compile source files
echo Compiling...
for %%f in (%SRC_DIR%\*.c) do (
    echo Compiling %%f...
    %CC% %CFLAGS% -c "%%f" -o "%OBJ_DIR%\%%~nf.o"
    if errorlevel 1 (
        echo Error compiling %%f
        exit /b 1
    )
)

:: Link object files
echo Linking...
%CC% "%OBJ_DIR%\*.o" -o "%TARGET%"
if errorlevel 1 (
    echo Linking failed.
    exit /b 1
)

echo Build complete. Run "%TARGET%" to start the game.
