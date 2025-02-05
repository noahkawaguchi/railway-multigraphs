#ifndef NETWORK_H
#define NETWORK_H

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>

#include "Stop.h"
#include "Track.h"

class Network {
public:
  Network();
  ~Network() = default;

  // Create and add a stop to the network
  std::shared_ptr<Stop> new_stop(std::string id, std::shared_ptr<Line> line);

  // Create and add a track to the network, specifying the distance traveled between the two stops
  void new_track(std::shared_ptr<Stop> stop1, std::shared_ptr<Stop> stop2, double distance);

  // Create a new station that has all the provided stops
  Station new_station(std::string name, std::unordered_set<std::shared_ptr<Stop>> stops);
  
  // Get all adjacent tracks for a given stop, including connections to different lines
  std::unordered_set<std::shared_ptr<Track>> get_adjacent_tracks(std::shared_ptr<Stop> stop);

  // Print a Route from a shortest path algorithm
  void print_route(Route route);

  // Find Dijkstra's shortest path from start to destination, prioritizing distance (miles)
  Route distance_DSP(Station start, Station destination);

  // Find Dijkstra's shortest path from start to destination, prioritizing cost
  Route cost_DSP(Station start, Station destination);

private:
  std::vector<std::shared_ptr<Stop>> stops;
  std::unordered_map<std::shared_ptr<Stop>, std::unordered_set<std::shared_ptr<Track>>> tracks;
  
};

#endif // NETWORK_H