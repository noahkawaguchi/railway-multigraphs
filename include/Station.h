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

  // Get the minutes from the starting station for shortest path algorithms
  int get_path_minutes();

  // Get the predecessor station for shortest path algorithms
  std::shared_ptr<Station> get_path_predecessor();

  // Get the processed flag for shortest path algorithms
  bool get_path_processed();

  // Set the minutes from the starting station for shortest path algorithms
  void set_path_minutes(int minutes);

  // Set the predecessor station for shortest path algorithms
  void set_path_predecessor(std::shared_ptr<Station> predecessor);

  // Set the processed flag for shortest path algorithms
  void set_path_processed(bool processed);

  // Reset the minutes, predecessor, and processed flag for restarting shortest path algorithms
  void path_reset();

private:
  std::string name;
  int path_minutes = std::numeric_limits<int>::max() / 2; // Initialize to "inifinity"
  std::shared_ptr<Station> path_predecessor;
  bool path_processed = false;

};

#endif // STATION_H