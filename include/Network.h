#ifndef NETWORK_H
#define NETWORK_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

#include "Station.h"
#include "Track.h"
#include "Route.h" // For shortest path algorithms

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
  
  // Print a representation of the network
  void print();

  // Calculate and print Dijkstra's shortest (quickest) path from start 
  // to all other stations. Fares are free and transfers are instant.
  void basic_DSP(std::shared_ptr<Station> start);

  // Calculate and print Dijkstra's shortest (quickest) path from start 
  // to destination only. Fares are free and transfers are instant.
  void basic_DSP(std::shared_ptr<Station> start, std::shared_ptr<Station> destination);

  // Find Dijkstra's shortest path from start to destination for use in other member functions
  std::shared_ptr<Route> helper_DSP(std::shared_ptr<Station> start, std::shared_ptr<Station> destination);

  // Calculate and print Yen's K shortest (quickest) paths. 
  // Fares are free and transfers are instant.
  void basic_yen(std::shared_ptr<Station> start, std::shared_ptr<Station> destination, int k);

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