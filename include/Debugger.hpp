#pragma once

#include "Breakpoint.hpp"
#include <cstdint>
#include <string>
#include <unordered_map>

class Debugger {
public:
  Debugger(std::string &program_name, pid_t pid);

  void run();
  void handle_command(const std::string &line);
  void continue_execution();

  // Breakpoints
  void set_breakpoint_at_addr(std::intptr_t addr);

private:
  std::string m_program_name{};
  pid_t m_pid{};

  // std::unordered_map<std::intptr_t, Breakpoint> m_breakpoints{};
};