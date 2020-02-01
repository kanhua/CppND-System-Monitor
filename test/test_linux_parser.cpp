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

using std::cout;
TEST(t1,ShowKernel)
{
    std::cout<<LinuxParser::Kernel();
   EXPECT_FLOAT_EQ(1.0,1.0);
}

TEST(t1,ShowOperatingSystem)
{
    std::cout<<LinuxParser::OperatingSystem();
}

TEST(t1,uptime)
{
    std::cout << UpTime();
}

TEST(t1, memutil)
{
    std::cout << MemoryUtilization();
}

TEST(t1,total_processes)
{
    std::cout << TotalProcesses();
}
TEST(t1,running_proceeses)
{
    std::cout<<RunningProcesses();
}