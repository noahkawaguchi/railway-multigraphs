#ifndef TRAIN_H
#define TRAIN_H

#include <memory>

#include "Line.h"
class Line;

class Train {
public:
  Train(std::shared_ptr<Line> line);
  ~Train() = default; // Default destructor is sufficient because of smart pointers

  // Set the train to begin the day facing forward from 
  // the origin or facing backward from the terminus
  void begin_day(bool facing_forward);

  // Proceed to the next stop
  void depart();

private:
  std::shared_ptr<Line> line;
  int capacity = 300;
  int passengers = 0;
  std::shared_ptr<Stop> current_stop = nullptr;
  bool facing_forward = true;
};

#endif // TRAIN_H