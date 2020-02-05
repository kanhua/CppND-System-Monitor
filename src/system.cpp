#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

#include "linux_parser.h"

using LinuxParser::Kernel;
using LinuxParser::MemoryUtilization;
using LinuxParser::OperatingSystem;
using LinuxParser::RunningProcesses;
using LinuxParser::TotalProcesses;
using LinuxParser::UpTime;

Processor &System::Cpu() { return cpu_; }

bool compare_process_ram(Process &p1, Process &p2) {
  if (stoi(p1.Ram()) > stoi(p2.Ram())) {
    return true;
  } else {
    return false;
  }
}

vector<Process> &System::Processes() {
  vector<int> all_pids = LinuxParser::Pids();
  processes_ = {};
  for (size_t i = 0; i < all_pids.size(); i++) {
    Process prc(all_pids[i]);
    processes_.push_back(prc);
  }
  std::sort(processes_.begin(), processes_.end(), compare_process_ram);
  return processes_;
}

std::string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { return LinuxParser::UpTime(); }