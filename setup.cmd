@REM Usage: .\setup.cmd 1496_PathCrossing
@REM Will create:
@REM 1496_PathCrossing directory
@REM 1496_PathCrossing\1496.cpp
@REM 
@REM 
@REM 
@REM 
@REM 
@REM 

@ECHO OFF

SETLOCAL ENABLEEXTENSIONS
SETLOCAL ENABLEDELAYEDEXPANSION

SET DIR=%1

SET FILENAME=%DIR%\%DIR:~0,4%.cpp

MKDIR %DIR%
COPY /y NUL %FILENAME% >NUL





