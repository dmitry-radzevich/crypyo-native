#pragma once

#include <argparse/argparse.hpp>
#include <memory>
#include <string>
#include <vector>

#include "util_cc.hh"

namespace cryptn::term {

class TermCliCmd;
using TermCliCmdVec = std::vector<std::unique_ptr<TermCliCmd>>;

/**
 * @brief Command-Line Interface
 *
 */
class TermCli {

  argparse::ArgumentParser args_; ///< Args parser.
  TermCliCmdVec cliCmds_{};          ///< Subcommands.

  int verbosity_{0}; ///< Verbosity level option.

public:
  TermCli();

  UTIL_CC_NOCPMV(TermCli)
  UTIL_CC_DEFDTR(TermCli)

  constexpr auto verbosity() const noexcept -> int { return verbosity_; }

  void registerCmd(std::unique_ptr<TermCliCmd> cmd);
  auto parseAndExec(int argc, const char **argv) -> int;
};

} // namespace cryptn::term
