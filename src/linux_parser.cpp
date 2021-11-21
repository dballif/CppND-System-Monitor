#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

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
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// Grab all the PIDS from the /proc directory
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
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

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  float MemTotal,MemFree,MemUsed;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          std::replace(value.begin(), value.end(), '_', ' ');
          MemTotal = std::stof(value);
        }
        if (key == "MemFree") {
          std::replace(value.begin(), value.end(), '_', ' ');
          MemFree = std::stof(value);
        }
      }
      MemUsed = (MemTotal - MemFree)/MemTotal;
    }
  }
  return MemUsed;
}

// Read and return the system uptime
long LinuxParser::UpTime() { 
  string up_time, idle_time;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> up_time >> idle_time;
    return std::stol(up_time);
  }
  return std::stol(up_time);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line;
  string key;
  string value1,value2,value3,value4,value5,value6,value7,value8,value9,value10;
  vector<string> cpuVals;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value1 >> value2 >> value3 >> value4 >> value5 >> value6 >> value7 >> value8 >> value9 >> value10) {
        if (key == "cpu") {
          cpuVals.push_back(value1);
          cpuVals.push_back(value2);
          cpuVals.push_back(value3);
          cpuVals.push_back(value4);
          cpuVals.push_back(value5);
          cpuVals.push_back(value6);
          cpuVals.push_back(value7);
          cpuVals.push_back(value8);
          cpuVals.push_back(value9);
          cpuVals.push_back(value10);
        }
      }
    }
  }
  return cpuVals;
 }

// Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return std::stoi(value);
        }
      }
    }
  }
  return std::stoi(value);}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return std::stoi(value);
        }
      }
    }
  }
  return std::stoi(value);}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string line,cmd;
  string pidNum = to_string(pid);
  std::ifstream filestream(kProcDirectory + pidNum + kCmdlineFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> cmd; 
    }
  }
  return cmd;
 }

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string line,key,value,memory;
  string pidNum = to_string(pid);
  std::ifstream filestream(kProcDirectory + pidNum + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          memory = value;
        }
      }
    }
  }
  return memory;
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  string line,key,value,uid;
  string pidNum = to_string(pid);
  std::ifstream filestream(kProcDirectory + pidNum + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          uid = value;
        }
      }
    }
  }
  return uid;
 }

// Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string line;
  string username;
  string name,stuff,uidval;
  string pidNum = to_string(pid);
  std::ifstream filestream(kProcDirectory + pidNum + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> name >> stuff >> uidval) {
        if (uidval == LinuxParser::Uid(pid)) {
          username = name;
        }
      }
    }
  }
  return username;
 }

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  string pidNum = to_string(pid);
  vector<int> processStats;
  long seconds;
  int hz = sysconf(_SC_CLK_TCK);
  int num;

  //This section grabs each number in the file and adds it to a vector
  std::ifstream filestream(kProcDirectory + pidNum + kStatFilename);
  if(filestream.is_open()){
      while (filestream >> num){
          processStats.push_back(num);
      }
  }
  else {return 0.0;}

  //processStats[21] = starttime - Divide by hz to find seconds
  seconds = processStats[21] / hz;

  return seconds;
 }
