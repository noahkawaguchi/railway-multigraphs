#ifndef LINE_H
#define LINE_H

#include <string>

struct Line {
  std::string name = "";
  float base_cost = 0.0f;
  float cost_per_mile = 0.0f;
};

#endif // LINE_H