#ifndef TRACK_H
#define TRACK_H

#include <memory>

#include "Station.h"

class Track {
public:
  Track(std::shared_ptr<Station> station1, std::shared_ptr<Station> station2, int minutes);
  ~Track() = default;

  // Get the first station this track connects
  std::shared_ptr<Station> get_station1();
  
  // Get the second station this track connects
  std::shared_ptr<Station> get_station2();

  // Get the number of minutes it takes to get 
  // from one end of the track to the other
  int get_minutes();

private:
  std::shared_ptr<Station> station1, station2; // Undirected
  int minutes;

};

#endif // TRACK_H