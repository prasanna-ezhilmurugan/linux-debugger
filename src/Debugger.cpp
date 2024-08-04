#include "../include/Debugger.hpp"
#include "../include/linenoise.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <vector>

namespace Loader {
std::vector<std::string> split(const std::string &line) {
  std::vector<std::string> out{};
  std::stringstream ss{line};

  std::string item{};
  while (ss >> item) {
    out.push_back(item);
  }

  return out;
}
} // namespace Loader

Debugger::Debugger(const std::string &program, const pid_t pid)
    : m_program{program}, m_pid{pid} {}

void Debugger::run() {
  int wait_status;
  int options{};
  waitpid(m_pid, &wait_status, options);

  char *line = nullptr;
  while ((line = linenoise("\nlinux-debugger> ")) != nullptr) {
    handle_command(line);
    linenoiseHistoryAdd(line);
    linenoiseFree(line);
  }
}

void Debugger::handle_command(const std::string &line) {
  std::vector<std::string> args{Loader::split(line)};

  // check whether the arguement is provided or not
  std::string command = args.at(0);

  if (command == "continue") {

    continue_execution();

  } else if (command == "break") {

    try {
      std::string addr{args.at(1)};
      set_breakpoint_at_addr(std::stol(addr, 0, 16));
    } catch (exception e) {
      std::cout << "exception occured in args" << std::endl;
    }

  } else {

    std::cerr << "Unknown Command" << std::endl;
    
  }
}

void Debugger::continue_execution() {
  ptrace(PTRACE_CONT, m_pid, nullptr, nullptr);

  int wait_status;
  int options{};
  waitpid(m_pid, &wait_status, options);
}

void Debugger::set_breakpoint_at_addr(std::uintptr_t addr) {
  std::cout << "Setting Breakpoint at addr : " << std::hex << addr << std::endl;

  Breakpoint bp{m_pid, addr};
  bp.enable();
  m_breakpoints.insert_or_assign(addr, bp);
}
