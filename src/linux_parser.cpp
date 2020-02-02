#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using LinuxParser::kProcDirectory;
using LinuxParser::kStatFilename;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
    string line;
    string key;
    string value;
    std::ifstream filestream(kOSPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ' ', '_');
            std::replace(line.begin(), line.end(), '=', ' ');
            std::replace(line.begin(), line.end(), '"', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "PRETTY_NAME") {
                    std::replace(value.begin(), value.end(), '_', ' ');
                    return value;
                }
            }
        }
    }
    return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
    string os, version, kernel;
    string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> version >> kernel;
    }
    return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
    vector<int> pids;
    DIR *directory = opendir(kProcDirectory.c_str());
    struct dirent *file;
    while ((file = readdir(directory)) != nullptr) {
        // Is this a directory?
        if (file->d_type == DT_DIR) {
            // Is every character of the name a digit?
            string filename(file->d_name);
            if (std::all_of(filename.begin(), filename.end(), isdigit)) {
                int pid = stoi(filename);
                pids.push_back(pid);
            }
        }
    }
    closedir(directory);
    return pids;
}

float LinuxParser::MemoryUtilization() {
    string line;
    string key;
    string value;

    float memtotal = 0.0;
    float memfree = 0.0;
    std::ifstream filestream(kProcDirectory + kMeminfoFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "MemTotal") {
                    memtotal = stof(value);
                } else if (key == "MemFree") {
                    memfree = stof(value);
                }
            }
        }
    }
    return 1.0 - memfree / memtotal;

}

long LinuxParser::UpTime() {
    string line, uptime;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> uptime;
    }
    return stol(uptime);

}

class ProcStatParser {
public:
    ProcStatParser() {
        string line;
        string key;
        string value;

        cpu_usage = vector<int>(cpu_col_num, 0);

        std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
        if (filestream.is_open()) {
            while (std::getline(filestream, line)) {
                std::replace(line.begin(), line.end(), ':', ' ');
                std::istringstream linestream(line);
                while (linestream >> key) {
                    if (key == "processes") {
                        linestream >> value;
                        total_processes = stoi(value);
                        break;
                    } else if (key == "procs_running") {
                        linestream >> value;
                        running_processes = stoi(value);
                        break;
                    } else if (key == "cpu") {
                        for (int i = 0; i < cpu_col_num; i++) {
                            linestream >> value;
                            cpu_usage[i] = stoi(value);
                        }
                        calculate_cpu_usage();
                        break;
                    }
                }
            }
        }


    }

    int total_processes = 0;
    int running_processes = 0;
    int Idle = 0;
    int NonIdle = 0;
    int Total = 0;


    void calculate_cpu_usage() {
        int user = cpu_usage[0];
        int nice = cpu_usage[1];
        int system = cpu_usage[2];
        int idle = cpu_usage[3];
        int iowait = cpu_usage[4];
        int irq = cpu_usage[5];
        int softirq = cpu_usage[6];
        int steal = cpu_usage[7];
        int guest = cpu_usage[8];
        int guest_nice = cpu_usage[9];

        Idle = idle + iowait;
        NonIdle = user + nice + system + irq + softirq + steal;
        Total = Idle + NonIdle;
    }

private:
    const size_t cpu_col_num = 10;
    std::vector<int> cpu_usage;


};


// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
//vector<string> LinuxParser::CpuUtilization() { return {}; }

#include <chrono>
#include <thread>

float LinuxParser::CpuUtilization() {
    ProcStatParser prev_prc;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ProcStatParser current_prc;

    int totald = current_prc.Total - prev_prc.Total;
    int idled = current_prc.Idle - prev_prc.Idle;

    return float(totald - idled) / float(totald);
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    ProcStatParser prc;
    return prc.total_processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    ProcStatParser prc;
    return prc.running_processes;
}

/// Read UserName associated with a UID
/// \param uid
/// \return
std::string LinuxParser::UserofUid(int uid) {

    string line;
    const int cols = 7;
    std::ifstream filestream(LinuxParser::kPasswordPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            vector<string> tokens(cols, "");
            string temp_token;
            std::istringstream linestream(line);
            int index = 0;
            while (std::getline(linestream, temp_token, ':')) {
                tokens[index] = temp_token;
                index++;
            }
            if (stoi(tokens[2]) == uid) {
                return tokens[0];
            }

        }
    }

    return "UserNotFound";
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {

    string filename = LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatusFilename;
    std::ifstream filestream(filename);
    if (filestream.is_open()) {
        string line;
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            string token;
            linestream >> token;
            if (token == "Uid:") {
                string uid;
                linestream >> uid;
                return uid;

            } else {
                continue;
            }
        }
    }


    return "UidNotFound";
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {

    string uid=Uid(pid);
    string username=UserofUid(stoi(uid));

    return username; }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }