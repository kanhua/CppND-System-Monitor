#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>
#include "../include/linux_parser.h"
using LinuxParser::Kernel;
using std::cout;
TEST(t1,t1method)
{
    std::cout<<Kernel();
   EXPECT_FLOAT_EQ(1.0,1.0);
}

