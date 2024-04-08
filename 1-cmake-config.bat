@echo off

if "x%1" == "x" (
   set _CPRESET=conan-default
) else (
   set _CPRESET=%1
)

cmake --preset %_CPRESET%
