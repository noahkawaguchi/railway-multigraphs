#ifndef STOP_H
#define STOP_H

#include <cmath>
#include <limits>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

struct Line {
  std::string name = "";
  double base_cost = 0.0;
  double cost_per_mile = 0.0;
};

struct Stop {
  std::string id;
  std::string station_name;                            // The name of the station this stop is at
  std::shared_ptr<Line> line;                          // The line this stop belongs to
  std::unordered_set<std::shared_ptr<Stop>> transfers; // Stops at the same station by other lines
  std::shared_ptr<Stop> path_predecessor;
  double path_distance = std::numeric_limits<double>::max() / 2; // "Infinity"

  // 2-arg constructor for general use
  Stop(std::string id, std::shared_ptr<Line> line)
      : id(id), line(line), path_predecessor(dummy_predecessor) {}
  // 3-arg constructor to prevent dummy_predecessor from pointing to itself
  Stop(std::string id, std::shared_ptr<Line> line, std::shared_ptr<Stop> predecessor)
      : id(id), line(line), path_predecessor(predecessor) {}

  // Set the cost for shortest path algorithms. Automatically rounds to cents.
  void set_path_cost(double cost) { this->path_cost = std::round(cost * 100) / 100; }

  // Get the cost for shortest path algorithms. Always rounded to cents.
  double get_path_cost() { return this->path_cost; }

  // Reset the predecessor, distance, and cost for restarting shortest path algorithms
  void path_reset() {
    this->path_predecessor = dummy_predecessor;
    this->path_distance = std::numeric_limits<double>::max() / 2; // "Infinity"
    this->path_cost = std::numeric_limits<double>::max() / 2;     // "Infinity
  }

private:
  double path_cost = std::numeric_limits<double>::max() / 2; // "Infinity"

  // Dummy instance of Stop with pointers to nullptr to be created
  // only once and pointed to by default by all other instances
  static inline auto dummy_predecessor = std::make_shared<Stop>("No Predecessor", nullptr, nullptr);
};

// Type alias for managing multiple transfer stops
using Station = std::unordered_set<std::shared_ptr<Stop>>;

// Type alias for readability in shortest path algorithms
using Route = std::vector<std::shared_ptr<Stop>>;

#endif // STOP_H
