@echo off

if "x%1" == "x" (
   set _CPRESET=conan-debug
) else (
   set _CPRESET=%1
)

cmake --build --preset %_CPRESET%
