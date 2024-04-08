cmake_minimum_required(VERSION 3.22)

project(crypto_native VERSION 0.1)
set(CMAKE_PROJECT_VERSION_SUFFIX "DEV")
if(NOT CMAKE_PROJECT_VERSION_PATCH)
  set(CMAKE_PROJECT_VERSION_PATCH 0)
endif()
if(NOT CMAKE_PROJECT_VERSION_TWEAK)
  set(CMAKE_PROJECT_VERSION_TWEAK 0)
endif()
message(STATUS "Building ${CMAKE_PROJECT_NAME} v${CMAKE_PROJECT_VERSION}-${CMAKE_PROJECT_VERSION_SUFFIX}")
message(STATUS "Build variant: ${CMAKE_BUILD_TYPE}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ARTIFACTS_DIR "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ARTIFACTS_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ARTIFACTS_DIR}")

find_package(Microsoft.GSL)
set(VS_ADD_NATIVE_VISUALIZERS True)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(argparse REQUIRED)
find_package(ryml REQUIRED)
find_package(botan REQUIRED)
#find_package(wxwidgets)

set(PROJECT_DEPS Microsoft.GSL::GSL fmt::fmt spdlog::spdlog ryml::ryml)

set(PROJECT_PCH
  <cstdlib> <string> <string_view> <filesystem> <stdexcept> <array>
  <iostream> <fstream> <sstream>
  
  <fmt/printf.h> <fmt/format.h>
  <spdlog/spdlog.h>
  <ryml.hpp>
  <botan/block_cipher.h> <botan/nist_keywrap.h>
)

configure_file(src/build_info.hh.in "${PROJECT_BINARY_DIR}/build_info.hh")

add_subdirectory(src/util)
add_subdirectory(src/termapp)

#enable_testing()
#add_subdirectory(src/test)
