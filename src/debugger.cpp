#include "debugger.hpp"
#include "breakpoint.hpp"
#include "linenoise.h"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
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
    : m_program{program}, m_pid{pid}, is_running{true} {}

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
  } else if (args.at(0) == "break") {

    if (args.size() <= 1) {
      std::cerr << "address is not passed to set breakpoint" << std::endl;
    } else {
      std::string addr{args.at(1)};
      set_breakpoint_at_addr(std::stol(addr, 0, 16));
    }

  } else {
    std::cout << "Unknown Command" << std::endl;
  }
}

void debugger::continue_execution() {
  ptrace(PTRACE_CONT, m_pid, nullptr, nullptr);

  int wait_status{};
  int options{0};
  waitpid(m_pid, &wait_status, options);
}

void debugger::set_breakpoint_at_addr(const std::uintptr_t &addr) {
  std::cout << "setting breakpoint at address 0x" << std::hex << addr
            << std::endl;

  breakpoint bp{m_pid, addr};
  bp.enable();

  m_breakpoints.insert_or_assign(addr, bp);
  std::cout << "breakpoint added in address " << std::hex << addr << std::endl;
}
