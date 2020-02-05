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

int Process::Pid() { return pid; }

float Process::CpuUtilization() {
    LinuxParser::ProcPIDStatParser ppsp(Pid());

    unsigned long total_time = ppsp.utime + ppsp.stime + ppsp.cstime;
    unsigned long seconds =
        LinuxParser::UpTime() - ppsp.starttime / sysconf(_SC_CLK_TCK);

    float cpu_usage =
        (((float)total_time / (float)sysconf(_SC_CLK_TCK)) / (float)seconds);

    return cpu_usage;
}

string Process::Command() {
    return LinuxParser::Command(Pid());
}

string Process::Ram() {
  string ram_str = LinuxParser::Ram(pid);
  int ram_mb = stoi(ram_str) / 1024;

  return to_string(ram_mb);
}

string Process::User() {
    string user = LinuxParser::User(Pid());

    return user;
}

long int Process::UpTime() {
    return LinuxParser::UpTime(Pid()) / sysconf(_SC_CLK_TCK);
}

bool Process::operator<(const Process &a) const { return true; }