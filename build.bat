@echo off

set compiler_and_entry=cl ..\src\main.c

REM Enable warnings with: /W4 /wd4201
REM /wd4201 Ignores the compiler warning C4201 about nameless structs/unions
set cl_default_flags=/Isrc /nologo /FC /Zi 

set external_include= /I"..\src\fz_std" ^
                      /I"..\src\fz_std\extra" ^
                      /I"..\src\fz_std\win32" ^
                      /I"..\src\fz_std\external\opengl" 

set linker_flags= user32.lib ^
                  gdi32.lib ^
                  Shell32.lib ^
                  winmm.lib ^
                  opengl32.lib

if not exist build mkdir build
pushd build
%compiler_and_entry% %cl_default_flags% %external_include% %linker_flags% /Fe"text_rendering.exe"
popd