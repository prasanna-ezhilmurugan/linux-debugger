#include "../include/Debugger.hpp"
#include <iostream>
#include <stdexcept>
#include <sys/personality.h>
#include <sys/ptrace.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "program not specified" << std::endl;
    return -1;
  }

  // getting the program name
  auto program_name = argv[1];

  // fork create new process creating a duplicate of parent process
  auto pid = fork();

  if (pid == 0) {
    // child process
    //  debugee is executed here
    std::cout << "child process " << std::endl;

    personality(ADDR_NO_RANDOMIZE);
    ptrace(PTRACE_TRACEME, pid, nullptr, nullptr);
    execl(program_name, program_name, nullptr);

  } else if (pid >= 1) {
    // parent process
    //  debugger is executed here
    std::cout << "parent process " << std::endl;
    Debugger dbg{program_name, pid};
    dbg.run();
  }
}