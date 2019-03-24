@echo off
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
) else (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

rem dependencies setup
set sfml_include= /I dependencies
set picojson_include= /I dependencies/picojson
set imgui_include= /I dependencies/imgui
set imgui_sources= dependencies/imgui/*.cpp
set node_editor_include= /I dependencies/NodeEditor/Include /I dependencies/NodeEditor/Include/ax /I dependencies/NodeEditor/Source
set node_editor_sources= dependencies/NodeEditor/Source/*.cpp dependencies/NodeEditor/Source/ax/*.cpp

rem includes
set includes= /I include %sfml_include% %picojson_include% %imgui_include% %node_editor_include%

rem libraries
set lib_opengl= /LIBPATH lib/OpenGL32.lib
set lib_sfml= /LIBPATH lib/sfml-graphics.lib /LIBPATH lib/sfml-system.lib /LIBPATH lib/sfml-window.lib
set libraries= %lib_opengl% %lib_sfml%

set compilerflags=/Od /Zi /EHsc /std:c++latest
set sources= src/*.cpp %imgui_sources% %node_editor_sources%
set linkerflags=/OUT:bin\main.exe
cl.exe %compilerflags% %sources% %includes% /link %linkerflags% %libraries%
del bin\*.ilk *.obj *.pdb