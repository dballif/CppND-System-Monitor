#include <string>

#include "format.h"

using std::string;

// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
    string time;
    int hh,mm,ss;
    int remainder;
    hh = seconds / 3600;
    remainder = seconds % 3600;
    mm = remainder / 60;
    ss = (int)(remainder % 60);
    time = std::to_string(hh) + ":" + std::to_string(mm) + ":" + std::to_string(ss);
    return time;
 }