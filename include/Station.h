#ifndef STATION_H
#define STATION_H

#include <memory>
#include <limits>
#include <string>
#include <unordered_set>

#include "Line.h"

struct Station {
  std::string name;
  std::shared_ptr<Line> line; // The line this station belongs to
  std::unordered_set<std::shared_ptr<Station>> transfers; // Stops at the same location by other lines
  std::shared_ptr<Station> path_predecessor;
  float path_distance = std::numeric_limits<float>::max() / 2; // "Infinity"
  float path_cost = std::numeric_limits<float>::max() / 2; // "Infinity"
 
  // 2-arg constructor for general use
  Station(std::string name, std::shared_ptr<Line> line) 
          : name(name), line(line), path_predecessor(dummy_predecessor) {}
  // 3-arg constructor to prevent dummy_predecessor from pointing to itself
  Station(std::string name, std::shared_ptr<Line> line, std::shared_ptr<Station> predecessor) 
          : name(name), line(line), path_predecessor(predecessor) {}

  // Reset the predecessor, distance, and cost for restarting shortest path algorithms
  void path_reset() {
    this->path_predecessor = dummy_predecessor;
    this->path_distance = std::numeric_limits<float>::max() / 2; // "Infinity"
    this->path_cost = std::numeric_limits<float>::max() / 2; // "Infinity
  }
  
private:
  // Dummy instance of Station with pointers to nullptr to be created 
  // only once and pointed to by default by all other instances
  static inline std::shared_ptr<Station> dummy_predecessor 
    = std::make_shared<Station>("No Predecessor", nullptr, nullptr);

};

// Type alias for readability in shortest path algorithms
using Route = std::vector<std::shared_ptr<Station>>;

#endif // STATION_H