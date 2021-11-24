#include <string>
#include <vector>
#include <iostream>
#include <fstream>


#include "processor.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Return the aggregate CPU utilization
float Processor::Utilization() { 
    float cpu;
    //Get all the values from the LinuxParser
    cpuVals = LinuxParser::CpuUtilization();

    //Read in the important values (convert them to a useful type)
    long user = std::stol(cpuVals[0]);
    long nice = std::stol(cpuVals[1]);
    long system = std::stol(cpuVals[2]);
    long idle = std::stol(cpuVals[3]);
    long iowait = std::stol(cpuVals[4]);
    long irq = std::stol(cpuVals[5]);
    long softirq = std::stol(cpuVals[6]);
    long steal = std::stol(cpuVals[7]);
    //Calculations don't use these
    //long guest = std::stol(cpuVals.at(8));
    //long guestnice = std::stol(cpuVals.at(9));

    //Intermediate Calculations just make the final calculation cleaner
    Idle = idle +iowait;
    NIdle = user + nice + system + irq + softirq + steal;
    Total = Idle + NIdle;

    //Now do the calculations found on stack overflow (https://bit.ly/3xbfYMT)
    totald = Total - PTotal;
    idled = Idle - PIdle;

    cpu = 100 * ((totald - idled)/totald);

    //Have to reset the values to the current values for the next calculation
    PIdle = Idle;
    PTotal = Total;

    return cpu;
 }