@echo off
setlocal enableextensions enabledelayedexpansion

set INPUT_FILE=./input.txt
set OUTPUT_FOLDER=./
set SOURCE_FOLDER=%~dp0
set PROJECT_NAME=day4
set C_FILE_NAME="!SOURCE_FOLDER!day4.c"

call ../win32/build_util.bat