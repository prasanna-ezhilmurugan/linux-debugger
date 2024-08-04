#pragma once

#include "../include/Breakpoint.hpp"
#include <string>
#include <unordered_map>
#include <cstdint>

class Debugger {
public:
  Debugger(const std::string &program, const pid_t pid);

  void run();
  void handle_command(const std::string &line);
  void continue_execution();

  // Breakpoint
  void set_breakpoint_at_addr(std::uintptr_t addr);

private:
  std::string m_program{};
  pid_t m_pid{};

  std::unordered_map<std::uintptr_t, Breakpoint> m_breakpoints{};
};