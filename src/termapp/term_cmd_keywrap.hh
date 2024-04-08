#pragma once

#include "term_cli_cmd.hh"

namespace cryptn::term {

class KeyWrapCliCmd : public TermCliCmd {
  auto exec() -> int override;

public:
  static constexpr auto kName = "keywrap";
  KeyWrapCliCmd();
};

} // namespace cryptn::term
