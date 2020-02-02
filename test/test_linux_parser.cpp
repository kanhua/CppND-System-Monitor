#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>
#include "../include/linux_parser.h"

using LinuxParser::Kernel;
using LinuxParser::OperatingSystem;
using LinuxParser::UpTime;
using LinuxParser::MemoryUtilization;
using LinuxParser::TotalProcesses;
using LinuxParser::RunningProcesses;
using LinuxParser::CpuUtilization;

using std::cout;

TEST(t1, ShowKernel) {
    std::cout << LinuxParser::Kernel();
    EXPECT_FLOAT_EQ(1.0, 1.0);
}

TEST(t1, ShowOperatingSystem) {
    std::cout << LinuxParser::OperatingSystem();
}

TEST(t1, uptime) {
    std::cout << UpTime();
}

TEST(t1, memutil) {
    std::cout << MemoryUtilization();
}

TEST(t1, total_processes) {
    std::cout << TotalProcesses();
}

TEST(t1, running_proceeses) {
    std::cout << RunningProcesses();
}

TEST(t1, get_cpu_utilization) {
    std::cout << CpuUtilization();
}

TEST(t1, show_pids) {
    std::vector<int> pids = LinuxParser::Pids();
    std::cout << "pids:";
    for (int i = 0; i < pids.size(); i++) {
        std::cout << " " << pids[i];

    }
    std::cout << std::endl;
}

TEST(t1,show_user){

    std::cout <<"User with UID 1000: "<<LinuxParser::UserofUid(1000)<<std::endl;

}

TEST(t1,show_uid)
{
    std::vector<int> pids = LinuxParser::Pids();
    std::string uid=LinuxParser::Uid(pids[0]);
    std::cout << "Show UID:" << stoi(uid) << std::endl;
}

TEST(t1,get_username_of_process)
{
    std::vector<int> pids = LinuxParser::Pids();
    std::string username=LinuxParser::User(pids[0]);
    std::cout << "User of Process " << pids[0] << " is " << username << std::endl;

}