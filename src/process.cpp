#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() { return pid; }

// Return this process's CPU utilization
float Process::CpuUtilization() { 
    string pidNum = to_string(Process::Pid());
    vector<string> processStats;
    string num;
    int utime,stime,starttime,totaltime;
    long int uptime = LinuxParser::UpTime();
    float seconds,cpuUse;
    int hz = sysconf(_SC_CLK_TCK);

    //This section grabs each number in the file and adds it to a vector
    std::ifstream filestream(LinuxParser::kProcDirectory + pidNum + LinuxParser::kStatFilename);
    if(filestream.is_open()){
        while (filestream >> num){
            processStats.push_back(num);
        }
    }
    else {return 0.0;}

    //TODO: Check these calculations - The Number I get is way too high
    //According to Man page processStats[13],[14],[15],[16],[21] = utime,stime,cutime,cstime,starttime respectively
    utime  = std::stoi(processStats[13]);
    stime  = std::stoi(processStats[14]);
    starttime = std::stoi(processStats[21]);
    
    //Actually use these values to calculate what we need to know (According to StackOverflow)
    totaltime = utime + stime; //I chose not to include children processes
    seconds = uptime - (starttime/hz);
    cpuUse = ((totaltime/hz)/seconds);
    
    return cpuUse;
 }

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime() - LinuxParser::UpTime(pid); }

//  Overload the "less than" comparison operator for Process objects based on ram
bool Process::operator<(Process a)  { 
    return Ram() < a.Ram();
 }