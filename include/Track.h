#ifndef TRACK_H
#define TRACK_H

#include <memory>

#include "Station.h"

struct Track {
  std::shared_ptr<Station> other_station;
  int minutes; // How long it takes to get to the other station
  
  // Constructor 
  Track(std::shared_ptr<Station> other_station, int minutes) 
      : other_station(other_station), minutes(minutes) {}

};

#endif // TRACK_H