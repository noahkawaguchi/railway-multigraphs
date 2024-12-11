#ifndef STOP_H
#define STOP_H

#include <memory>
#include <limits>
#include <string>
#include <unordered_set>

struct Line {
  std::string name = "";
  float base_cost = 0.0f;
  float cost_per_mile = 0.0f;
};

struct Stop {
  std::string id;
  std::string station_name; // The name of the station this stop is at
  std::shared_ptr<Line> line; // The line this stop belongs to
  std::unordered_set<std::shared_ptr<Stop>> transfers; // Stops at the same station by other lines
  std::shared_ptr<Stop> path_predecessor;
  float path_distance = std::numeric_limits<float>::max() / 2; // "Infinity"
 
  // 2-arg constructor for general use
  Stop(std::string id, std::shared_ptr<Line> line) 
          : id(id), line(line), path_predecessor(dummy_predecessor) {}
  // 3-arg constructor to prevent dummy_predecessor from pointing to itself
  Stop(std::string id, std::shared_ptr<Line> line, std::shared_ptr<Stop> predecessor) 
          : id(id), line(line), path_predecessor(predecessor) {}

  // Set the cost for shortest path algorithms. Automatically rounds to cents.
  void set_path_cost(float cost) { this->path_cost = round(cost * 100) / 100; }

  // Get the cost for shortest path algorithms. Always rounded to cents.
  float get_path_cost() { return this->path_cost; }

  // Reset the predecessor, distance, and cost for restarting shortest path algorithms
  void path_reset() {
    this->path_predecessor = dummy_predecessor;
    this->path_distance = std::numeric_limits<float>::max() / 2; // "Infinity"
    this->path_cost = std::numeric_limits<float>::max() / 2; // "Infinity
  }
  
private:
  float path_cost = std::numeric_limits<float>::max() / 2; // "Infinity"

  // Dummy instance of Stop with pointers to nullptr to be created 
  // only once and pointed to by default by all other instances
  static inline std::shared_ptr<Stop> dummy_predecessor
    = std::make_shared<Stop>("No Predecessor", nullptr, nullptr);

};

struct Station {
  std::string name = "";
  std::unordered_set<std::shared_ptr<Stop>> stops; // Stops at this station by all lines
};

// Type alias for readability in shortest path algorithms
using Route = std::vector<std::shared_ptr<Stop>>;

#endif // STOP_H