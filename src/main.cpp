#include "../include/Debugger.hpp"
#include <filesystem>
#include <iostream>
#include <optional>
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

  for(std::size_t i{}; i < args.size(); i++){
    
    // check arguments and handle error
  }

  return EXIT_SUCCESS;
}

// int main(int argc, char *argv[]) {
//   if (argc < 2) {
//     std::cerr << "program not specified" << std::endl;
//     return -1;
//   }

//   // getting the program name
//   auto program_name = argv[1];

//   // fork create new process creating a duplicate of parent process
//   auto pid = fork();

//   if (pid == 0) {
//     // child process
//     //  debugee is executed here
//     std::cout << "child process " << std::endl;

//     personality(ADDR_NO_RANDOMIZE);
//     ptrace(PTRACE_TRACEME, pid, nullptr, nullptr);
//     execl(program_name, program_name, nullptr);

//   } else if (pid >= 1) {
//     // parent process
//     //  debugger is executed here
//     std::cout << "parent process " << std::endl;
//     Debugger dbg{program_name, pid};
//     dbg.run();
//   }
// }