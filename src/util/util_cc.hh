/**
 * @file
 * @author DR
 * @brief Generic C++ helpers
 *
 */

#pragma once

#define UTIL_CC_NOCP(Type)                                                     \
  Type(const Type &) = delete;                                                 \
  Type &operator=(const Type &) = delete;

#define UTIL_CC_NOMV(Type)                                                     \
  Type(Type &&) = delete;                                                      \
  Type &operator=(Type &&) = delete;

#define UTIL_CC_NOCPMV(Type)                                                   \
  UTIL_CC_NOCP(Type)                                                           \
  UTIL_CC_NOMV(Type)

#define UTIL_CC_DEFCP(Type)                                                    \
  Type(const Type &) = default;                                                \
  Type &operator=(const Type &) = default;

#define UTIL_CC_DEFMV(Type)                                                    \
  Type(Type &&) = default;                                                     \
  Type &operator=(Type &&) = default;

#define UTIL_CC_DEFCPMV(Type)                                                  \
  UTIL_CC_DEFCP(Type)                                                          \
  UTIL_CC_DEFMV(Type)

#define UTIL_CC_DEFDTR(Type) ~Type() = default;
#define UTIL_CC_DEFDTR_VIRT(Type) virtual ~Type() = default;
