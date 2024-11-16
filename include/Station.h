#ifndef STATION_H
#define STATION_H

#include <memory>

class Station {
public:
  Station(char id);
  ~Station() = default;

  // Get the station ID
  char get_id();

private:
  char id;
  std::shared_ptr<Station> dijkstra_predecessor;
  int dijkstra_minutes;

};

#endif // STATION_H