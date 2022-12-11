@echo off
setlocal enableextensions enabledelayedexpansion

set INPUT_FILE=./input.txt
set OUTPUT_FOLDER=./
set SOURCE_FOLDER=%~dp0
set PROJECT_NAME=day6
set C_FILE_NAME="!SOURCE_FOLDER!day6.c"

call ../win32/build_util.bat