#pragma once

#include <cstdint>
#include <stdint.h>
#include <string>

class Breakpoint {
public:
  Breakpoint(pid_t pid, std::uintptr_t addr);

  void enable();
  void disable();

  bool is_enabled() const { return m_enabled; }
  std::uintptr_t get_address() const { return m_addr; }

private:
  pid_t m_pid{};
  std::uintptr_t m_addr{};
  bool m_enabled{};
  // data which used to be the breakpoint address
  std::uint8_t m_saved_data{};
};