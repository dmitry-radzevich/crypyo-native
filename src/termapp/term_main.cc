#include <cstdlib>
#include <fmt/printf.h>
#include <iostream>

#include "build_info.hh"
#include "term_cli.hh"

#include "term_cmd_keywrap.hh"

namespace cb = cryptn::build;
namespace ct = cryptn::term;

int main(int argc, const char **argv) {
  fmt::println(FMT_STRING("{} (Terminal Edition) v{}"),
               cb::kProjectName, cb::kProjectFullVersion);
  try {
    auto cli = ct::TermCli{};
    cli.registerCmd(std::make_unique<ct::KeyWrapCliCmd>());
    return cli.parseAndExec(argc, argv);
  } catch (const std::exception &e) {
    std::cerr << fmt::format(FMT_STRING("ERROR: {}"), e.what()) << std::endl;
    std::cerr << "Aborting..." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}