#ifndef LINE_H
#define LINE_H

#include <string>

struct Line {
  std::string name = "";
  double base_cost = 0.0;
  double cost_per_mile = 0.0;
};

#endif // LINE_H