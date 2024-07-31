#include "../include/debugger.hpp"

Debugger::Debugger(std::string program_name, pid_t pid)
    : m_program_name{program_name}, m_pid{pid} {}

void Debugger::run(){
}