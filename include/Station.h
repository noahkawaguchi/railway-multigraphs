#ifndef STATION_H
#define STATION_H

#include <memory>
#include <limits>

class Station {
public:
  Station(char id);
  ~Station() = default;

  // Get the station ID
  char get_id();

  // Get the minutes from the starting station for Dijkstra's algorithm
  int get_dijkstra_minutes();

  // Get the predecessor station for Dijkstra's algorithm
  std::shared_ptr<Station> get_dijkstra_predecessor();

  // Reset the minutes and predecessor for restarting Dijkstra's algorithm
  void dijkstra_reset();

private:
  char id;
  int dijkstra_minutes = std::numeric_limits<int>::max(); // Initialize to "inifinity"
  std::shared_ptr<Station> dijkstra_predecessor = nullptr;

};

#endif // STATION_H