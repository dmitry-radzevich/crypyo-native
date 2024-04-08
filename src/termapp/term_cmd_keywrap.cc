#include <botan/cipher_mode.h>
#include <botan/hex.h>
#include <botan/nist_keywrap.h>
#include <fmt/format.h>

#include "term_cli.hh"
#include "term_cmd_keywrap.hh"

namespace {} // namespace

namespace cryptn::term {

KeyWrapCliCmd::KeyWrapCliCmd() : TermCliCmd(kName) {
  args_.add_argument("-c", "--cipher")
      .help("cipher spec")
      .default_value("AES-128");

  args_.add_argument("--wrap-mode")
      .help("key wrapping mode")
      .default_value("KWP");

  args_.add_argument("-m", "--mode")
      .help("crypto operation selector")
      //      .choices("wrap", "w", "unwrap", "u")
      //      .nargs(1)
      .default_value("wrap");

  args_.add_argument("-k", "--key").help("key to use (HEX)").required();

  args_.add_argument("INPUTS").remaining().required();
}

auto KeyWrapCliCmd::exec() -> int {

  const auto verbosity = termCli_->verbosity();
  const auto key = Botan::hex_decode(args_.get<std::string>("--key"));
  const auto wrapMode = args_.get<std::string>("--wrap-mode");
  const auto mode = args_.get<std::string>("--mode");
  const auto cipherSpec = args_.get<std::string>("--cipher");

  if (verbosity > 0) {
    if (mode == "w" || mode == "wrap") {
      fmt::println("Wrapping key material...");
    } else {
      fmt::println("Unwrapping key material...");
    }
  }

  if (verbosity > 2) {
    fmt::println(FMT_STRING(R"(
Cipher     : {}
Wrap. mode : {}
Key        : {} 
      )"),
                 cipherSpec, wrapMode, args_.get<std::string>("--key"));
  }

  const auto inputs = args_.get<std::vector<std::string>>("INPUTS");
  std::for_each(begin(inputs), end(inputs), [&](const auto inputHex) {
    if (verbosity > 1) {
      fmt::print(FMT_STRING("{} -> "), inputHex);
    }

    const auto input = Botan::hex_decode(inputHex);

    const auto cipher = Botan::BlockCipher::create_or_throw(cipherSpec);
    cipher->set_key(key);

    std::string outputHex;
    if (mode == "w" || mode == "wrap") {
      auto result =
          wrapMode == "KWP"
              ? Botan::nist_key_wrap_padded(input.data(), input.size(), *cipher)
              : Botan::nist_key_wrap(input.data(), input.size(), *cipher);
      outputHex = Botan::hex_encode(result);
    } else {
      auto result =
          wrapMode == "KWP"
              ? Botan::nist_key_unwrap_padded(input.data(), input.size(),
                                              *cipher)
              : Botan::nist_key_unwrap(input.data(), input.size(), *cipher);
      outputHex = Botan::hex_encode(result);
    }

    fmt::println(FMT_STRING("{}"), outputHex);
  });

  return EXIT_SUCCESS;
}

} // namespace cryptn::term
