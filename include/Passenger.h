#ifndef PASSENGER_H
#define PASSENGER_H

#include <memory>

#include "Station.h"
class Station;

class Passenger {
public:
  Passenger(std::unique_ptr<Station> home_station,
            std::unique_ptr<Station> work_station);

  ~Passenger() = default; // Default destructor is sufficient because of smart pointers

private:
  std::unique_ptr<Station> home_station;
  std::unique_ptr<Station> work_station;
  float cost_priority;
  float time_priority;
  float transfers_priority;
};




#endif // PASSENGER_H