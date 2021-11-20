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

// TODO: Return this process's ID
int Process::Pid() { return 0; }

// Return this process's CPU utilization
float Process::CpuUtilization() { 
    string pidNum = to_string(Process::Pid());
    vector<int> processStats;
    int num,utime,stime,cutime,cstime,starttime,totaltime;
    long int uptime = Process::UpTime();
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

    //According to Man page processStats[13],[14],[15],[16],[21] = utime,stime,cutime,cstime,starttime respectively
    utime  = processStats[13];
    stime  = processStats[14];
    cutime = processStats[15];
    cstime = processStats[16];
    starttime = processStats[21];
    //Actually use these values to calculate what we need to know (According to StackOverflow)
    totaltime = utime + stime + cutime + cstime; //I chose to include children processes becuase it sounded fun
    seconds = uptime - (starttime/(hz));
    cpuUse = (totaltime/hz)/seconds * 100; 

    return cpuUse;
 }

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Process::Pid()); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Command(Process::Pid()); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Process::Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return true; }