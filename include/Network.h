#ifndef NETWORK_H
#define NETWORK_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

#include "Station.h"
#include "Track.h"

class Network {
public:
  Network();
  ~Network() = default;

  // Create and add a station to the network with the given ID
  std::shared_ptr<Station> new_station(std::string name);

  // Create and add a track to the network, specifying the number 
  // of minutes it takes to go between the two stations
  void new_track(std::shared_ptr<Station> station1,
                 std::shared_ptr<Station> station2,
                 int minutes);

  // Calculate and print Dijkstra's shortest (quickest) path from start.
  // Fares are free and transfers are instant.
  // If destination_only is true, find a single path to the destination.
  // Else find all shortest paths from start.
  void basic_DSP(std::shared_ptr<Station> start,
                 std::shared_ptr<Station> destination,
                 bool destination_only);

  // Print a representation of the network
  void print();

private:
  std::vector<std::shared_ptr<Station>> stations;
  std::unordered_map<std::string, std::vector<std::shared_ptr<Track>>> tracks;

  // Custom comparator for priority queue
  struct MinimumMinutes {
    bool operator()(const std::shared_ptr<Station>& a, const std::shared_ptr<Station>& b) {
      return a->get_dijkstra_minutes() > b->get_dijkstra_minutes();
    }
  };
  std::priority_queue<std::shared_ptr<Station>, std::vector<std::shared_ptr<Station>>,
                      MinimumMinutes> dijkstra_unvisited;

};

#endif // NETWORK_H