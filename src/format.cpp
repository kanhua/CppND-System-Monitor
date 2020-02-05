#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  long minutes = seconds / 60;
  long r_seconds = seconds % 60;

  long hours = minutes / 60;
  long r_mintues = minutes % 60;

  if (hours > 99) hours = 99;

  char buffer[20];
  sprintf(buffer, "%02d:%02d:%02d", hours, r_mintues, r_seconds);
  string output_string(buffer, 8);

  return output_string;
}