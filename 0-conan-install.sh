#!/bin/bash

set _CPROF=$1
if [ -z "${_CPROF}" ]; then
   _CPROF=gcc-dbg
fi

conan install . --profile ${_CPROF} --build=missing --deployer=conan_bindeps -of build-nix
