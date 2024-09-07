#pragma once

#include "breakpoint.hpp"

#include <filesystem>
#include <unordered_map>

class debugger {
public:
  debugger(const std::filesystem::path &program, const pid_t pid);
  void run();
  void handle_command(const std::string& line);
  void continue_execution();

  void set_breakpoint_at_addr(const std::uintptr_t& addr);

private:
  std::filesystem::path m_program;
  pid_t m_pid;
  bool is_running;
  std::unordered_map<std::uintptr_t, breakpoint> m_breakpoints;
};