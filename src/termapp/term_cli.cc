#include <algorithm>
#include <argparse/argparse.hpp>

#include "build_info.hh"
#include "term_cli.hh"
#include "term_cli_cmd.hh"


namespace cryptn::term {

TermCli::TermCli()
    : args_{std::string{cryptn::build::kProjectName} + " (Terminal Edition)",
            std::string{cryptn::build::kProjectFullVersion}} {
  args_.add_argument("-V", "--verbose")
      .help("increase output verbosity")
      .append()
      .flag()
      .nargs(0)
      .action([&](const auto &) { ++verbosity_; });

  // args_.add_argument("-c", "--config")
  //     .help("configuration file")
  //     .default_value("")
  //     .action([&](const auto &val) { configFile_ = val; });
  // //.default_value(std::string{cryptn::build::kProjectName} + ".yaml");
}

void TermCli::registerCmd(std::unique_ptr<TermCliCmd> cmd) {
  cmd->termCli_ = this;
  args_.add_subparser(cmd->args());
  cliCmds_.emplace_back(std::move(cmd));
}

auto TermCli::parseAndExec(int argc, const char **argv) -> int {
  args_.parse_args(argc, argv);

  auto cmd = std::find_if(begin(cliCmds_), end(cliCmds_), [&](auto &e) {
    return e && args_.is_subcommand_used(e->args());
  });

  if (cmd != end(cliCmds_)) {
    return (*cmd)->exec();
  } else {
    return -1;
  }
}



} // namespace cryptn::term
