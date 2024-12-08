#ifndef TRACK_H
#define TRACK_H

#include <memory>

#include "Station.h"
#include "Line.h"

struct Track {
  std::shared_ptr<Station> other_station;
  float distance; // The number of miles to the other station
  std::shared_ptr<Line> line; // The line this track belongs to
  
  // Define constructor for pointer safety
  Track(std::shared_ptr<Station> other_station, float distance) 
      : other_station(other_station), distance(distance) {}

};

#endif // TRACK_H