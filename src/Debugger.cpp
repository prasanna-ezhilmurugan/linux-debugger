#include "../include/Debugger.hpp"
#include "../include/linenoise.h"
#include <sstream>
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
  auto options = 0;
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
}