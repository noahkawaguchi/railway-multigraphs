#include "Line.h"

#include <iostream>

Line::Line() {}

void Line::add_station(std::shared_ptr<Station> station) {
  
  // Create stop at this station
  std::shared_ptr<Stop> stop = std::make_shared<Stop>();
  stop->station = station;
  
  // Add stop to the end of the line
  if (this->origin == nullptr) { // Empty
    this->origin = stop;
    this->terminus = stop;
  } else { // Not empty
    this->terminus->next = stop;
    stop->previous = this->terminus;
    this->terminus = stop;
  }
}

std::shared_ptr<Stop> Line::get_origin() {
  return this->origin;
}

std::shared_ptr<Stop> Line::get_terminus() {
  return this->terminus;
}

std::shared_ptr<Stop> Line::get_next_stop(bool facing_forward,
                                          std::shared_ptr<Stop> current_stop
) {
  
  // Safety check, but this should never happen
  if (current_stop == nullptr) { return current_stop; }

  std::shared_ptr<Stop> cursor = current_stop;
  if (facing_forward) {
    while (cursor->next != nullptr && cursor->next) {

      // TODO

      break;
    }

  }

}

void Line::print() {
  if (this->origin == nullptr) {
    std::cout << "\nThe line is empty!\n" << std::endl;
  }
  
  else {
    std::shared_ptr<Stop> cursor = this->origin;

    int count = 1;
    // May or may not be a circular linked list
    while (cursor->next != nullptr && cursor->next != this->origin) {
      cursor = cursor->next;
      count++;
    }
    std::cout << "\nStations found: " << count << "\n\n";
  }
}
