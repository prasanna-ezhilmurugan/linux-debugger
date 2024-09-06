#include "debugger.hpp"

debugger::debugger(const std::filesystem::path &program, const pid_t pid)
    : m_program{program}, m_pid{pid} {}

void debugger::run(){
  
}