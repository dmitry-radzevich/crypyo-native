@echo off

if "x%1" == "x" (
   set _CPROF=msvc-dbg
) else (
   set _CPROF=%1
)

conan install . --profile %_CPROF% --build=missing --deployer=conan_bindeps
