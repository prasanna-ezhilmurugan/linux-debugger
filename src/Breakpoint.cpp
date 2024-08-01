#include "../include/Breakpoint.hpp"
#include <sys/ptrace.h>
#include <iostream>

Breakpoint::Breakpoint(pid_t pid, std::intptr_t addr)
    : m_pid{pid}, m_addr{addr}, m_enabled{false}, m_saved_data{} {
        std::cerr << "breakpoint hello";
}

void Breakpoint::enable() {
  auto data = ptrace(PTRACE_PEEKDATA, m_pid, m_addr, nullptr);
  m_saved_data = static_cast<uint8_t>(data & 0xFF); // saving the last byte
  uint64_t int3 = 0xcc;

  uint64_t data_with_int3 = ((data & ~0xff) | int3); // set bottom byte as int3
  ptrace(PTRACE_POKEDATA, m_pid, m_addr, data_with_int3);

  m_enabled = true;
}

void Breakpoint::disable() {
  auto data = ptrace(PTRACE_PEEKDATA, m_pid, m_addr, nullptr);
  auto restore_data = ((data & ~0xFF) | m_saved_data);

  ptrace(PTRACE_POKEDATA, m_pid, m_addr, restore_data);

  m_enabled = false;
}