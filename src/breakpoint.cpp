#include "breakpoint.hpp"

#include <sys/ptrace.h>

breakpoint::breakpoint(const pid_t &pid, const std::uintptr_t &addr)
    : m_pid{pid}, m_addr{addr}, m_enabled{false}, m_saved_data{} {}

void breakpoint::enable() {
  auto data = ptrace(PTRACE_PEEKDATA, m_pid, m_addr, nullptr);

  // save the bottom byte for restoration
  m_saved_data = static_cast<uint8_t>(data & 0xFF);
  // modifing the present data for setting a breakpoint
  std::uint64_t int3{0xCC};
  std::uint64_t data_with_int3{(data & ~0xFF) | int3};

  // setting the modified data into the location and setting flog true
  ptrace(PTRACE_POKEDATA, m_pid, m_addr, data_with_int3);
  m_enabled = true;
}

void breakpoint::disable() {
  auto data = ptrace(PTRACE_PEEKDATA, m_pid, m_addr, nullptr);

  // restoring the data which is prev saved
  auto restored_data{(data & ~0xFF) | m_saved_data};
  ptrace(PTRACE_POKEDATA, m_pid, m_addr, restored_data);

  // setting flag false
  m_enabled = false;
}
