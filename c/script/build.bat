@echo off

:: Variables
set project_directory=
set output_directory=
set common_compiler_flags=/MTd /nologo /Od /W4 /Z7 /wd4100 /wd4101 /wd4189
set common_linker_flags=/DEBUG:FASTLINK /INCREMENTAL:NO /OPT:REF
:: 
pushd %cd%
cd %~dp0
cd ..
set project_directory=%cd%
popd

set output_directory=%project_directory%\build

rmdir /s /q "%output_directory%"
mkdir "%output_directory%"

pushd "%output_directory%"
cls
cl %common_compiler_flags% "%project_directory%\source\chip8.c" /link %common_linker_flags%
popd