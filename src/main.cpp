#include "Debugger.hpp"
#include "utilities.hpp"

#include <filesystem>
#include <iostream>
#include <optional>
#include <sys/personality.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <vector>

std::optional<std::string> is_prefixed_with(const std::string &prefix,
                                            const std::string &str) {
  if (str.substr(0, prefix.size()) == prefix) {
    return str.substr(prefix.size());
  }
  return std::nullopt;
}

std::vector<std::string> shift_args(int32_t argc, char **argv) {
  std::vector<std::string> args{};
  argc--;
  argv++;

  for (int i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  return args;
}

int main(int argc, char **argv) {
  std::vector<std::string> args = shift_args(argc, argv);

  std::filesystem::path input_file{};
  std::filesystem::path output_file{};

  for (std::size_t i{}; i < args.size(); i++) {
    auto current_arg{args.at(i)};

    std::cout << current_arg << std::endl;
    if ((is_prefixed_with("--", current_arg) == "help") ||
        (is_prefixed_with("-", current_arg) == "h")) {

      std::cout << utilities::help_message;
      return EXIT_SUCCESS;

    } else {

      if (input_file.empty()) {
        input_file = current_arg;
      } else {
        std::cerr << "Cannot specify two input files." << std::endl;
        return EXIT_FAILURE;
      }
    }
  }

  if (input_file.empty()) {
    std::cerr << "No input file specified" << std::endl;
    return EXIT_FAILURE;
  }

  pid_t pid = fork();

  if (pid == 0) {
    std::cout << "Child process" << std::endl;
    personality(ADDR_NO_RANDOMIZE);
    ptrace(PTRACE_TRACEME, pid, nullptr, nullptr);
    execl(input_file.c_str(), input_file.c_str(), nullptr);
  } else if (pid > 0) {
    Debugger dbg{input_file, pid};
    dbg.run();
  }
}