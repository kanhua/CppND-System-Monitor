#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    int minutes=seconds/60;
    int r_seconds=seconds%60;

    int hours=minutes/60;
    int r_mintues=minutes%60;

    return std::to_string(hours)+":"+std::to_string(r_mintues)+":"+std::to_string(r_seconds); }