#pragma once

#include <filesystem>

class debugger {
public:
  debugger(const std::filesystem::path &program, const pid_t pid);
  void run();

private:
  std::filesystem::path m_program{};
  pid_t m_pid{};
};