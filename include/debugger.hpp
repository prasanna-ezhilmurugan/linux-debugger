#pragma once

#include <string>

class Debugger {
public:
  Debugger(std::string program_name, pid_t pid);

  void run();
  void handle_command(const std::string &line);
  void continue_execution();

private:
  std::string m_program_name{};
  pid_t m_pid{};
};