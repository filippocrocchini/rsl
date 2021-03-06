@echo off

set BUILD_TYPE=Debug

set ROOT_DIR=%~dp0
set OUTPUT_DIR=%ROOT_DIR%build\
set SOURCE_FILES=%ROOT_DIR%tests.cpp

set OUTPUT_NAME=tests
set PDB_NAME=%OUTPUT_NAME%.pdb

set INCLUDE_DIRS=/I%ROOT_DIR%..\
set REMOVED_WARNINGS=
set LINK_OPTIONS=

set REMOVED_WARNINGS=

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

pushd %OUTPUT_DIR%

cl /nologo /W4 /std:c++latest %REMOVED_WARNINGS% /MT /O2 /Oi /Z7 /DRELEASE %INCLUDE_DIRS% %LINK_OPTIONS% %SOURCE_FILES% /link /OUT:%OUTPUT_NAME%.exe /PDB:%PDB_NAME% /SUBSYSTEM:CONSOLE 

popd