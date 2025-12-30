#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

struct Line {
  std::string name;
  double base_cost = 0.0;
  double cost_per_mile = 0.0;
};

struct Stop {
  std::string id;
  std::string station_name;                            // The name of the station this stop is at
  std::shared_ptr<Line> line;                          // The line this stop belongs to
  std::unordered_set<std::shared_ptr<Stop>> transfers; // Stops at the same station by other lines
  std::shared_ptr<Stop> path_predecessor{nullptr};
  double path_distance = std::numeric_limits<double>::max() / 2; // "Infinity"

  Stop(std::string id, std::shared_ptr<Line> line) : id(std::move(id)), line(std::move(line)) {}

  // Set the cost for shortest path algorithms. Automatically rounds to cents.
  void set_path_cost(double cost) { this->path_cost = std::round(cost * 100) / 100; }

  // Get the cost for shortest path algorithms. Always rounded to cents.
  auto get_path_cost() const -> double { return this->path_cost; }

  // Reset the predecessor, distance, and cost for restarting shortest path algorithms
  void path_reset() {
    this->path_predecessor = nullptr;
    this->path_distance = std::numeric_limits<double>::max() / 2; // "Infinity"
    this->path_cost = std::numeric_limits<double>::max() / 2;     // "Infinity
  }

private:
  double path_cost = std::numeric_limits<double>::max() / 2; // "Infinity"
};

// Type alias for managing multiple transfer stops
using Station = std::unordered_set<std::shared_ptr<Stop>>;

// Struct for managing a pair of start and destination stations
struct StationPair {
  Station start, dest;
};

// Type alias for readability in shortest path algorithms
using Route = std::vector<std::shared_ptr<Stop>>;
