#pragma once

#include "breakpoint.hpp"

#include <cstdint>
#include <filesystem>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unordered_map>

class debugger {
public:
  debugger(const std::filesystem::path &program, const pid_t pid);
  void run();
  void handle_command(const std::string &line);
  void continue_execution();

  void set_breakpoint_at_addr(const std::uintptr_t &addr);

  // memory functions
  uint64_t read_memory(uint64_t address);
  void write_memory(uint64_t address, uint64_t value);

  // register functions
  void dump_register();
  void read_register(const std::string &register_name);
  void write_register(const std::string &register_name,
                      const std::string &value);

  uint64_t get_program_counter();
  void set_program_counter(uint64_t value);

  //stepover functionality
  void step_over_breakpoint();
  void wait_for_signal();

private:
  std::filesystem::path m_program;
  pid_t m_pid;
  bool is_running;
  std::unordered_map<std::uintptr_t, breakpoint> m_breakpoints;
};