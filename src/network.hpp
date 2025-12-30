#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "stop.hpp"
#include "track.hpp"

class Network {
public:
  // Create and add a stop to the network
  auto new_stop(std::string name, std::shared_ptr<Line> line) -> std::shared_ptr<Stop>;

  // Create and add a track to the network, specifying the distance traveled between the two stops
  void new_track(std::shared_ptr<Stop> stop1, std::shared_ptr<Stop> stop2, double distance);

  // Create a new station that has all the provided stops
  static auto new_station(const std::string &name,
                          const std::unordered_set<std::shared_ptr<Stop>> &stops) -> Station;

  // Get all adjacent tracks for a given stop, including connections to different lines
  auto get_adjacent_tracks(const std::shared_ptr<Stop> &stop)
      -> std::unordered_set<std::shared_ptr<Track>>;

  // Print a Route from a shortest path algorithm
  static void print_route(Route route);

  // Find Dijkstra's shortest path from start to destination, prioritizing distance (miles)
  auto distance_DSP(Station start, Station destination) -> Route;

  // Find Dijkstra's shortest path from start to destination, prioritizing cost
  auto cost_DSP(Station start, Station destination) -> Route;

private:
  std::vector<std::shared_ptr<Stop>> stops;
  std::unordered_map<std::shared_ptr<Stop>, std::unordered_set<std::shared_ptr<Track>>> tracks;
};
