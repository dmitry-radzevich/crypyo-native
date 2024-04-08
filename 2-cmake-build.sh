#!/bin/bash

_CPRESET=$1
if [ -z  "${_CPRESET}" ]; then
   _CPRESET=conan-debug
fi

cmake --build --preset ${_CPRESET}
