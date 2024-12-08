#ifndef TRACK_H
#define TRACK_H

#include <memory>

#include "Station.h"
#include "Line.h"

struct Track {
  std::shared_ptr<Station> other_station;
  std::shared_ptr<Line> line; // The line this track belongs to
  float distance; // The number distance to the other station (miles)
  
  // Default line for algorithms that don't consider line
  static inline std::shared_ptr<Line> default_line_for_tracks = std::make_shared<Line>();

  // Define constructor for pointer safety
  Track(std::shared_ptr<Station> other_station, float distance) 
      : other_station(other_station), line(default_line_for_tracks), distance(distance) {}

  // Calculate the cost to go to the other station, rounded to cents
  float get_cost_from(std::shared_ptr<Station> current_station) {
    float total_cost = 0.0f;
    // Regular cost to take this section of track
    total_cost += round(this->distance * this->line->cost_per_mile * 100) / 100;
    // Additional cost to begin a new trip or transfer to a different line
    if (current_station->path_cost == 0.0f || this->line != current_station->line) {
      total_cost += this->line->base_cost;
    }
    return total_cost;
  }

};

#endif // TRACK_H