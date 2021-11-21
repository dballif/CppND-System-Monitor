#ifndef PROCESSOR_H
    #include <vector>
    #include <string>
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // See src/processor.cpp

  // Declare any necessary private members
 private:
    long Idle,PNIdle,NIdle,Total,totald,idled;
    long PIdle;
    long PTotal;
    std::vector<std::string> cpuVals,cpuVals2;
};

#endif