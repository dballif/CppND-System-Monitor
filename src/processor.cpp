#include <string>
#include <vector>

#include "processor.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string> cpuVals,cpuVals2;
    long Idle,PIdle,PNIdle,NIdle,PTotal,Total,totald,idled;
    float cpu;
    //Get all the values from the LinuxParser
    cpuVals = LinuxParser::CpuUtilization();

    //Read in the important values (convert them to a useful type)
    long user = std::stol(cpuVals.at(0));
    long nice = std::stol(cpuVals.at(1));
    long system = std::stol(cpuVals.at(2));
    long idle = std::stol(cpuVals.at(3));
    long iowait = std::stol(cpuVals.at(4));
    long irq = std::stol(cpuVals.at(5));
    long softirq = std::stol(cpuVals.at(6));
    long steal = std::stol(cpuVals.at(7));
    //Calculations don't use these
    //long guest = std::stol(cpuVals.at(8));
    //long guestnice = std::stol(cpuVals.at(9));

    PIdle = idle +iowait;
    PNIdle = user + nice + system + irq + softirq + steal;
    PTotal = PIdle + PNIdle;

    

    //Grab New values
    cpuVals2 = LinuxParser::CpuUtilization();

    //Read in the important values (convert them to a useful type)
    user = std::stol(cpuVals2.at(0));
    nice = std::stol(cpuVals2.at(1));
    system = std::stol(cpuVals2.at(2));
    idle = std::stol(cpuVals2.at(3));
    iowait = std::stol(cpuVals2.at(4));
    irq = std::stol(cpuVals2.at(5));
    softirq = std::stol(cpuVals2.at(6));
    steal = std::stol(cpuVals2.at(7));
    //Calculations don't use these
    //guest = std::stol(cpuVals2.at(8));
    //guestnice = std::stol(cpuVals2.at(9));

    Idle = idle +iowait;
    NIdle = user + nice + system + irq + softirq + steal;
    Total = Idle + NIdle;

    //Now do the calculations found on stack overflow (https://bit.ly/3xbfYMT)

    totald = Total - PTotal;
    idled = Idle - PIdle;
    if (totald != 0){
        cpu = (totald - idled)/totald;
    }
    else{cpu = 0.0;}
    return cpu;
 }