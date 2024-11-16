#ifndef STATION_H
#define STATION_H

#include <memory>
#include <limits>
#include <string>

class Station {
public:
  Station(std::string name);
  ~Station() = default;

  // Get the station name
  std::string get_name();

  // Get the minutes from the starting station for Dijkstra's algorithm
  int get_dijkstra_minutes();

  // Get the predecessor station for Dijkstra's algorithm
  std::shared_ptr<Station> get_dijkstra_predecessor();

  // Set the minutes from the starting station for Dijkstra's algorithm
  void set_dijkstra_minutes(int minutes);

  // Set the predecessor station for Dijkstra's algorithm
  void set_dijkstra_predecessor(std::shared_ptr<Station> predecessor);

  // Reset the minutes and predecessor for restarting Dijkstra's algorithm
  void dijkstra_reset();

private:
  std::string name;
  int dijkstra_minutes = std::numeric_limits<int>::max(); // Initialize to "inifinity"
  std::shared_ptr<Station> dijkstra_predecessor = nullptr;

};

#endif // STATION_H