#pragma once

#include <string>

class Debugger {
public:
  Debugger(const std::string &program, const pid_t pid);

  void run();
  void handle_command(const std::string &line);
  void continue_execution();

private:
  std::string m_program{};
  pid_t m_pid{};
};