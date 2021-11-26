#include <string>

#include "format.h"

using std::string;

// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
    string time;
    int hh,mm,ss;
    int remainder;
    string hh_string, mm_string,ss_string;

    hh = seconds / 3600;
    remainder = seconds % 3600;
    mm = remainder / 60;
    ss = (int)(remainder % 60);
    
    //Deal with leading 0 for hh
    if(hh < 10){
        hh_string = "0" + std::to_string(hh);
    }
    else { hh_string = std::to_string(hh);}

    //Deal with leading 0 for mm
    if(mm < 10){
        mm_string = "0" + std::to_string(mm);
    }
    else { mm_string = std::to_string(mm);}

    //Deal with leading 0 for ss
    if(ss < 10){
        ss_string = "0" + std::to_string(ss);
    }
    else { ss_string = std::to_string(ss);}


    time = hh_string + ":" + mm_string + ":" + ss_string;
    return time;
 }