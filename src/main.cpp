#include<iostream>
#include<unistd.h>
#include <sys/ptrace.h>

int main(int argc, char* argv[]){
  if(argc < 2){
    std::cerr << "Program not specified";
    return -1;
  }
  auto program_name = argv[1];
  auto pid = fork();
  if(pid == 0){
    std::cout<< "this is from the child process" << std::endl;
    //child process
    // execute debugee
    ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
    execl(program_name, program_name, nullptr);

  } else if(pid > 1) {
    std::cout<< "this is from the parent process" << std::endl;
    //we are in the parent process
    //execute debugger
    std::cout << "Started debugging process : " << pid << std::endl;

  }
  return 0;
}