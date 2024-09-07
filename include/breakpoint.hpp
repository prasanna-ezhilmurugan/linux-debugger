#pragma once

#include <cstdint>
#include <sys/types.h>

class breakpoint {
public:
  breakpoint(const pid_t &pid, const std::uintptr_t &addr);

  void enable();
  void disable();

  bool is_enabled() const { return m_enabled; }
  std::uintptr_t get_address() const { return m_addr; }

private:
  pid_t m_pid{};
  std::uintptr_t m_addr{};
  bool m_enabled{};
  uint8_t m_saved_data{};
};