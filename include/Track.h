#ifndef TRACK_H
#define TRACK_H

#include <memory>

#include "Station.h"

struct Track {
  std::shared_ptr<Station> other_station;
  float distance; // The distance to the other station (miles)
  
  // Define constructor for pointer safety
  Track(std::shared_ptr<Station> other_station, float distance) 
      : other_station(other_station), distance(distance) {}

  // Calculate the cost to go to the other station, rounded to cents
  float get_cost_from(std::shared_ptr<Station> current_station) {
    float total_cost = 0.0f;
    // Regular cost to take this section of track
    total_cost += round(this->distance * this->other_station->line->cost_per_mile * 100) / 100;
    // Additional cost to begin a new trip or transfer to a different line
    if (current_station->get_path_cost() == 0.0f 
        || this->other_station->line != current_station->line) 
    {
      total_cost += this->other_station->line->base_cost;
    }
    return total_cost;
  }

};

#endif // TRACK_H