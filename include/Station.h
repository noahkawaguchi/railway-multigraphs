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

  // Dummy instance pointing to nullptr to be created only 
  // once and pointed to by default by all other instances
  static inline std::shared_ptr<Station> dummy_predecessor 
    = std::make_shared<Station>("No Predecessor", nullptr);

  // Default line for algorithms that don't consider line
  static inline std::shared_ptr<Line> default_line_for_stations = std::make_shared<Line>();

  // 1-arg constructor for general use
  Station(std::string name) : name(name), line(default_line_for_stations),
                              path_predecessor(dummy_predecessor) {}
  // 2-arg constructor to prevent dummy_predecessor from pointing to itself
  Station(std::string name, std::shared_ptr<Station> predecessor) 
          : name(name), line(default_line_for_stations), path_predecessor(predecessor) {}

  // Reset the predecessor, distance, and cost for restarting shortest path algorithms
  void path_reset() {
    this->path_predecessor = dummy_predecessor;
    this->path_distance = std::numeric_limits<float>::max() / 2; // "Infinity"
    this->path_cost = std::numeric_limits<float>::max() / 2; // "Infinity
  }

};

#endif // STATION_H