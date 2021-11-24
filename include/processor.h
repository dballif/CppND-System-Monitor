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
    long PIdle{0};
    long PTotal{0};
    std::vector<std::string> cpuVals,cpuVals2;
};

#endif