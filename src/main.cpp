#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

std::optional<std::string> is_prefixed_with(const std::string &prefix,
                                            const std::string &str) {
  if (str.substr(0, prefix.size()) == prefix) {
    return str.substr(prefix.size());
  }
  return std::nullopt;
}

std::vector<std::string> shift_args(int argc, const char *argv[]) {
  std::vector<std::string> args{};
  argc--;
  argv++;

  for (int i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }
  return args;
}

int main(int argc, const char *argv[]) {
  std::vector<std::string> args{shift_args(argc, argv)};

  std::filesystem::path input_file{};
  for (std::size_t i{}; i < args.size(); i++) {
    auto current_arg{args.at(i)};
    if (is_prefixed_with("--", current_arg) == "help" ||
        is_prefixed_with("-", current_arg) == "h") {
      std::cout << "called for help" << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
