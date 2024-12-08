#ifndef STATION_H
#define STATION_H

#include <memory>
#include <limits>
#include <string>
#include <unordered_set>

class Station {
public:
  Station(std::string name);
  ~Station() = default;

  // Get the station name
  std::string get_name();

  // Get the distance from the starting station for shortest path algorithms
  float get_path_distance();

  // Get the predecessor station for shortest path algorithms
  std::shared_ptr<Station> get_path_predecessor();

  // Get stops at the same location by other lines
  std::unordered_set<std::shared_ptr<Station>> get_transfers();
  
  // Set the distance from the starting station for shortest path algorithms
  void set_path_distance(float distance);

  // Set the predecessor station for shortest path algorithms
  void set_path_predecessor(std::shared_ptr<Station> predecessor);

  // Reset the distance, predecessor, and processed flag for restarting shortest path algorithms
  void path_reset();

  // Add a stop at the same location by another line
  void set_transfer(std::shared_ptr<Station> station);

private:
  std::string name;
  float path_distance = std::numeric_limits<float>::max() / 2; // Initialize to "inifinity"
  std::shared_ptr<Station> path_predecessor;
  std::unordered_set<std::shared_ptr<Station>> transfers; // Stops at the same location by other lines

};

#endif // STATION_H