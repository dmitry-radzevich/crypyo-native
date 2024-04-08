#pragma once

#include <argparse/argparse.hpp>
#include <memory>
#include <string>

#include "util_cc.hh"

namespace cryptn::term {

class TermCli;

/**
 * @brief Abstract subcommand.
 */
class TermCliCmd {
  friend class TermCli;

protected:
  TermCli *termCli_{nullptr};     ///< Root CLI handler
  argparse::ArgumentParser args_; ///< Subcommand's args

  TermCliCmd(std::string name) : args_{name} {}

  virtual auto exec() -> int = 0;

  const auto &args() const noexcept { return args_; }
  auto &args() noexcept { return args_; }

public:
  UTIL_CC_NOCPMV(TermCliCmd)
  UTIL_CC_DEFDTR_VIRT(TermCliCmd)

};

} // namespace cryptn::term
