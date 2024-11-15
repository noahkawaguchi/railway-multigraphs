#ifndef LINE_H
#define LINE_H

#include <memory>

#include "Station.h"
class Station;

struct Stop {
  std::shared_ptr<Station> station = nullptr;
  std::shared_ptr<Stop> next = nullptr;
  std::shared_ptr<Stop> previous = nullptr;
};

class Line {
public:
  Line();
  ~Line() = default; // Default destructor is sufficient because of smart pointers

  // Return a pointer to the line's origin
  std::shared_ptr<Stop> get_origin();

  // Return a pointer to the line's terminus
  std::shared_ptr<Stop> get_terminus();

  // Add a station to the end of the line
  void add_station(std::shared_ptr<Station> station);

  // Get the next stop based on the train's direction
  std::shared_ptr<Stop> get_next_stop(bool facing_forward,
                                      std::shared_ptr<Stop> current_stop);

  // Print line info
  void print();

private:
  // Trains move in both directions, so both ends are technically both origins and 
  //   termini. The distinction here is for ease of use as a doubly linked list.
  // Initially set origin and terminus pointers to nullptr
  std::shared_ptr<Stop> origin = nullptr;
  std::shared_ptr<Stop> terminus = nullptr;

};


// TODO: ADD CIRCULAR LINKED LIST SUBCLASS



#endif // LINE_H