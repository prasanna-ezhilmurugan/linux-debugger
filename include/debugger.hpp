#include <string>

class Debugger {
public:
  Debugger(std::string program_name, pid_t pid);

  void run();

private:
  std::string m_program_name{};
  pid_t m_pid{};
};