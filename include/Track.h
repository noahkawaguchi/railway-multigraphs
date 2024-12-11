#ifndef TRACK_H
#define TRACK_H

#include <memory>
#include <cmath>

#include "Stop.h"

struct Track {
  std::shared_ptr<Stop> other_stop;
  double distance; // The distance to the other stop (miles)
  
  // Define constructor for pointer safety
  Track(std::shared_ptr<Stop> other_stop, double distance) 
        : other_stop(other_stop), distance(distance) {}

  // Calculate the cost to go to the other stop, rounded to cents
  double get_cost_from(std::shared_ptr<Stop> current_stop) {
    double total_cost = 0.0;
    // Regular cost to take this section of track
    total_cost += std::round(this->distance * this->other_stop->line->cost_per_mile * 100) / 100;
    // Additional cost to begin a new trip or transfer to a different line
    if (current_stop->get_path_cost() == 0.0 || this->other_stop->line != current_stop->line) {
      total_cost += this->other_stop->line->base_cost;
    }
    return total_cost;
  }
};

#endif // TRACK_H