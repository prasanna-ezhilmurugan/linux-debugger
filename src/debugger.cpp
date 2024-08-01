#include "../include/Debugger.hpp"
#include "../include/linenoise.h"
#include <iostream>
#include <sstream>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <vector>

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> out{};
  std::stringstream string_stream{s};
  std::string item;

  while (std::getline(string_stream, item, delimiter)) {
    out.push_back(item);
  }

  return out;
}

// function checks whether s1 starts with string s2
bool is_prefix(const std::string &s1, const std::string &s2) {
  if (s1.size() > s2.size())
    return false;

  // returns true when s1 equal to s2
  return std::equal(s1.begin(), s1.end(), s2.begin());
}

Debugger::Debugger(std::string &program_name, pid_t pid)
    : m_program_name{program_name}, m_pid{pid} {}

void Debugger::handle_command(const std::string &line) {
  auto args = split(line, ' ');
  auto command = args[0];

  if (is_prefix(command, "continue")) {
    continue_execution();
  } else if (is_prefix(command, "break")) {
    std::string addr{args[1], 2};

    set_breakpoint_at_addr(std::stol(addr, 0, 16));
  } else {
    std::cerr << "Unknown command";
  }
}

void Debugger::run() {
  int wait_status;
  auto options = 0;
  waitpid(m_pid, &wait_status, options);

  char *line = nullptr;
  while ((line = linenoise("linux-debugger >")) != nullptr) {
    handle_command(line);
    linenoiseHistoryAdd(line);
    linenoiseFree(line);
  }
}

void Debugger::continue_execution() {
  ptrace(PTRACE_CONT, m_pid, nullptr, nullptr);

  int wait_status;
  auto options = 0;
  waitpid(m_pid, &wait_status, options);
}

void Debugger::set_breakpoint_at_addr(std::intptr_t addr) {
  std::cout << "setting breakpoint at addr" << std::hex << addr << std::endl;

  Breakpoint bp{m_pid, addr};
  bp.enable();
  // m_breakpoints[addr] = bp;
}