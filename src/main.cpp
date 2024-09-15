#include "debugger.hpp"


#include <sys/personality.h>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
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

  // handling input file error and arguement passes
  if (args.size() == 0) {
    std::cerr << "No file specified for debugging" << std::endl;
    return EXIT_FAILURE;
  }
  for (std::size_t i{}; i < args.size(); i++) {
    auto current_arg{args.at(i)};
    if (is_prefixed_with("--", current_arg) == "help" ||
        is_prefixed_with("-", current_arg) == "h") {
      std::cout << "called for help"
                << std::endl; // replace it with the help message
      return EXIT_SUCCESS;
    } else {
      if (input_file.empty()) {
        input_file = current_arg;
      } else {
        std::cerr << "Cannot specify two input files" << std::endl;
        return EXIT_FAILURE;
      }
    }
  }

  pid_t pid = fork();
  if (pid == 0) {
    personality(ADDR_NO_RANDOMIZE);
    ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
    execl(input_file.c_str(), input_file.c_str(), nullptr);
  } else if (pid > 0) {
    std::cout << "Started debugging process :" << pid << std::endl;
    debugger db{input_file, pid};
    db.run();
  }

  return EXIT_SUCCESS;
}
