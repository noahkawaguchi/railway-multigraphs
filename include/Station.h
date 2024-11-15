#ifndef STATION_H
#define STATION_H

#include <memory>
#include <queue>

#include "Passenger.h"
class Passenger;

class Station {
public:
  enum AreaType {
    RESIDENTIAL,
    BUSINESS,
    LEISURE,
    SPECIALITY
  };

  Station(AreaType area_type);

  ~Station() = default; // Default destructor is sufficient because of smart pointers

private:
  AreaType area_type;
  std::queue<std::unique_ptr<Passenger>> platform;
};



#endif // STATION_H