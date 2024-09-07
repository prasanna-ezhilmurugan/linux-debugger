#pragma once

#include <filesystem>

class debugger {
public:
  debugger(const std::filesystem::path &program, const pid_t pid);
  void run();
  void handle_command(const std::string& line);
  void continue_execution();

private:
  std::filesystem::path m_program{};
  pid_t m_pid{};
  bool is_running{true};
};