#ifndef NETWORK_H
#define NETWORK_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>

#include "Station.h"
#include "Track.h"

class Network {
public:
  Network();
  ~Network() = default;

  // Create and add a station to the network with the given name on the given line
  std::shared_ptr<Station> new_station(std::string name, std::shared_ptr<Line> line);

  // Create and add a track to the network, specifying 
  // the distance traveled between the two stations
  void new_track(std::shared_ptr<Station> station1,
                 std::shared_ptr<Station> station2,
                 float distance);

  // Set the two stations as transfers for each other
  void set_transfer(std::shared_ptr<Station> station1, std::shared_ptr<Station> station2);
  
  // Get all adjacent tracks for a given station, including connections to different lines
  std::unordered_set<std::shared_ptr<Track>> get_adjacent_tracks(std::shared_ptr<Station> station);
  
  // Print a representation of the network
  void print();

  // Print a Route from a shortest path algorithm
  void print_route(Route route);

  // Find Dijkstra's shortest path from start to destination based on the distance between stations
  Route basic_DSP(std::shared_ptr<Station> start, std::shared_ptr<Station> destination);

  // Find Dijkstra's shortest path from start to destination, prioritizing cost
  Route cost_DSP(std::shared_ptr<Station> start, std::shared_ptr<Station> destination);

  // Find Yen's K shortest paths. Fares are free and transfers are instant.
  std::vector<Route> basic_yen(std::shared_ptr<Station> start,
                               std::shared_ptr<Station> destination,
                               int k);

private:
  std::vector<std::shared_ptr<Station>> stations;
  std::unordered_map<std::shared_ptr<Station>, std::unordered_set<std::shared_ptr<Track>>> tracks;
  
};

#endif // NETWORK_H