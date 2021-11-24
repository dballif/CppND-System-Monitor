#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
 Process(int newPid){
     pid = newPid;
 }
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // See src/process.cpp
  std::string Command();                   // See src/process.cpp
  float CpuUtilization();                  // See src/process.cpp
  std::string Ram();                       // See src/process.cpp
  long int UpTime();                       // See src/process.cpp
  bool operator<(Process a);  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
    int pid;
};

#endif