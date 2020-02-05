#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include "unistd.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) {
    this->pid = pid;
};

// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    LinuxParser::ProcPIDStatParser ppsp(Pid());

    unsigned long total_time = ppsp.utime + ppsp.stime + ppsp.cstime;
    unsigned long seconds =
        LinuxParser::UpTime() - ppsp.starttime / sysconf(_SC_CLK_TCK);

    float cpu_usage =
        (((float)total_time / (float)sysconf(_SC_CLK_TCK)) / (float)seconds);

    return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() {
    return LinuxParser::Command(Pid());
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  string ram_str = LinuxParser::Ram(pid);
  int ram_mb = stoi(ram_str) / 1024;

  return to_string(ram_mb);
}

// TODO: Return the user (name) that generated this process
string Process::User() {
    string user = LinuxParser::User(Pid());

    return user;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
    return LinuxParser::UpTime(Pid()) / sysconf(_SC_CLK_TCK);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(const Process &a) const { return true; }