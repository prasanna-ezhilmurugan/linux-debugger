#include "debugger.hpp"
#include "linenoise.h"

#include <iostream>
#include <sstream>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <vector>

namespace {
std::vector<std::string> tokenize(const std::string &line, char delimiter) {
  std::vector<std::string> args{};
  std::stringstream ss{line};
  std::string item{};
  while (std::getline(ss, item, delimiter)) {
    args.push_back(item);
  }
  return args;
}
}; // namespace

debugger::debugger(const std::filesystem::path &program, const pid_t pid)
    : m_program{program}, m_pid{pid} {}

void debugger::run() {
  int wait_status{};
  int options{0};
  waitpid(m_pid, &wait_status, options);

  std::string line{};
  const std::string prompt{"mini-db> $ "};
  while (is_running && !(line = linenoise(prompt.c_str())).empty()) {
    handle_command(line);
    linenoiseHistoryAdd(line.c_str());
  }
}

void debugger::handle_command(const std::string &line) {
  std::vector<std::string> args{tokenize(line, ' ')};
  // implement a hash function and switch statement for handline command
  if (args.at(0) == "exit") {
    is_running = false;
  } else if (args.at(0) == "continue") {
    continue_execution();
  } else {
    std::cout << "Unknown Command" << std::endl;
  }
}

void debugger::continue_execution(){
  ptrace(PTRACE_CONT, m_pid, nullptr, nullptr);

  int wait_status{};
  int options {0};
  waitpid(m_pid, &wait_status, options);
}