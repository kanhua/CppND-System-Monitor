#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
    const std::string kProcDirectory{"/proc/"};
    const std::string kCmdlineFilename{"/cmdline"};
    const std::string kCpuinfoFilename{"/cpuinfo"};
    const std::string kStatusFilename{"/status"};
    const std::string kStatFilename{"/stat"};
    const std::string kUptimeFilename{"/uptime"};
    const std::string kMeminfoFilename{"/meminfo"};
    const std::string kVersionFilename{"/version"};
    const std::string kOSPath{"/etc/os-release"};
    const std::string kPasswordPath{"/etc/passwd"};

// System
    float MemoryUtilization();

    long UpTime();

    std::vector<int> Pids();

    int TotalProcesses();

    int RunningProcesses();

    std::string OperatingSystem();

    std::string Kernel();

// CPU
    enum CPUStates {
        kUser_ = 0,
        kNice_,
        kSystem_,
        kIdle_,
        kIOwait_,
        kIRQ_,
        kSoftIRQ_,
        kSteal_,
        kGuest_,
        kGuestNice_
    };

//std::vector<std::string> CpuUtilization(); //TODO delete this when refactoring
    float CpuUtilization();

    long Jiffies();

    long ActiveJiffies();

    long ActiveJiffies(int pid);

    long IdleJiffies();

// Processes
    std::string Command(int pid);

    std::string Ram(int pid);

    std::string Uid(int pid);

    std::string User(int pid);

    long int UpTime(int pid);

    std::string UserofUid(int uid);

    std::string
    ReadColValueFromFile(const std::string &filename, std::string &column_name, const std::string &default_output);

    class ProcPIDStatParser {
    public:
        ProcPIDStatParser(int pid);


        int pid;            // %d
        char comm[256];        // %s
        char state;            // %c
        int ppid;            // %d
        int pgrp;            // %d
        int session;        // %d
        int tty_nr;            // %d
        int tpgid;            // %d
        unsigned long flags;    // %lu
        unsigned long minflt;    // %lu
        unsigned long cminflt;    // %lu
        unsigned long majflt;    // %lu
        unsigned long cmajflt;    // %lu
        unsigned long utime;    // %lu
        unsigned long stime;    // %lu
        long cutime;        // %ld
        long cstime;        // %ld
        long priority;        // %ld
        long nice;            // %ld
        long num_threads;        // %ld
        long itrealvalue;        // %ld
        unsigned long starttime;    // %lu
        unsigned long vsize;    // %lu
        long rss;            // %ld
        unsigned long rlim;        // %lu
        unsigned long startcode;    // %lu
        unsigned long endcode;    // %lu
        unsigned long startstack;    // %lu
        unsigned long kstkesp;    // %lu
        unsigned long kstkeip;    // %lu
        unsigned long signal;    // %lu
        unsigned long blocked;    // %lu
        unsigned long sigignore;    // %lu
        unsigned long sigcatch;    // %lu
        unsigned long wchan;    // %lu
        unsigned long nswap;    // %lu
        unsigned long cnswap;    // %lu
        int exit_signal;        // %d
        int processor;        // %d
        unsigned long rt_priority;    // %lu
        unsigned long policy;    // %lu
        unsigned long long delayacct_blkio_ticks;    // %llu
    };


};  // namespace LinuxParser

#endif