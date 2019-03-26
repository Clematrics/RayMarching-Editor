@echo off
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
) else (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

rem dependencies setup
set enum_to_string_include= /I dependencies/enumToString
set enum_to_string_sources= dependencies/enumToString/*.cpp
set imgui_include= /I dependencies/imgui
set imgui_sources= dependencies/imgui/*.cpp
set node_editor_include= /I dependencies/NodeEditor/Include /I dependencies/NodeEditor/Include/ax /I dependencies/NodeEditor/Source
set node_editor_sources= dependencies/NodeEditor/Source/*.cpp dependencies/NodeEditor/Source/ax/*.cpp
set picojson_include= /I dependencies/picojson
set sfml_include= /I dependencies

rem includes
set includes= /I include %enum_to_string_include% %imgui_include% %node_editor_include% %picojson_include% %sfml_include% 

rem libraries
set lib_opengl= /LIBPATH lib/OpenGL32.lib
set lib_sfml= /LIBPATH lib/sfml-graphics.lib /LIBPATH lib/sfml-system.lib /LIBPATH lib/sfml-window.lib
set libraries= %lib_opengl% %lib_sfml%

rem defines
set %defines%= /DDEBUG

set compilerflags=/Od /Zi /EHsc /std:c++latest %defines%
set sources= src/*.cpp %enum_to_string_sources% %imgui_sources% %node_editor_sources%
set linkerflags=/OUT:bin\main.exe
cl.exe %compilerflags% %sources% %includes% /link %linkerflags% %libraries%
del bin\*.ilk *.obj *.pdb