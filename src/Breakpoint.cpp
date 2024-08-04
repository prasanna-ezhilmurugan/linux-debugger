#include "../include/Breakpoint.hpp"
#include <sys/ptrace.h>
#include <iostream>

Breakpoint::Breakpoint(pid_t pid, std::uintptr_t addr)
    : m_pid{pid}, m_addr{addr}, m_enabled{false}, m_saved_data{} {}

void Breakpoint::enable() {
  auto data = ptrace(PTRACE_PEEKDATA, m_pid, m_addr, nullptr);
  // save the last byte of data which will be restored in disable function
  m_saved_data = static_cast<std::uint8_t>(data & 0xFF);
  uint64_t int3 = 0xCC;

  // set the bottom byte of the peeked data into int3 for setting breakpoint
  uint64_t modified_data = ((data & ~0xFF) | int3);
  ptrace(PTRACE_POKEDATA, m_pid, m_addr, modified_data);

  m_enabled = true;
}

void Breakpoint::disable() {
  auto data = ptrace(PTRACE_PEEKDATA, m_pid, m_addr, nullptr);

  uint64_t restored_data = ((data & ~0xFF) | m_saved_data);
  ptrace(PTRACE_POKEDATA, m_pid, m_addr, restored_data);

  m_enabled = false;
}

