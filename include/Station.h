#ifndef STATION_H
#define STATION_H

#include <memory>
#include <limits>
#include <string>
#include <unordered_set>

struct Station {
  std::string name;
  std::unordered_set<std::shared_ptr<Station>> transfers; // Stops at the same location by other lines
  float path_distance = std::numeric_limits<float>::max() / 2; // "Infinity"
  std::shared_ptr<Station> path_predecessor;

  // Dummy instance pointing to nullptr to be created only 
  // once and pointed to by default by all other instances
  static inline std::shared_ptr<Station> dummy_predecessor 
    = std::make_shared<Station>("No Predecessor", nullptr);

  // 1-arg constructor for general use
  Station(std::string name) : name(name), path_predecessor(dummy_predecessor) {}
  // 2-arg constructor to prevent dummy_predecessor from 
  // pointing to itself by explicitly passing nullptr
  Station(std::string name, std::shared_ptr<Station> predecessor) 
          : name(name), path_predecessor(predecessor) {}

  // Reset the distance and predecessor for restarting shortest path algorithms
  void path_reset() {
    this->path_distance = std::numeric_limits<float>::max() / 2; // "Infinity"
    this->path_predecessor = dummy_predecessor;
  }

};

#endif // STATION_H