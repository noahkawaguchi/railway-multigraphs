#ifndef NETWORK_H
#define NETWORK_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

#include "Station.h"
#include "Track.h"
#include "Route.h"

class Network {
public:
  Network();
  ~Network() = default;

  // Create and add a station to the network with the given name
  std::shared_ptr<Station> new_station(std::string name);

  // Create and add a track to the network, specifying the number 
  // of minutes it takes to go between the two stations
  void new_track(std::shared_ptr<Station> station1,
                 std::shared_ptr<Station> station2,
                 int minutes);
  
  // Print a representation of the network
  void print();

  // Find Dijkstra's shortest (quickest) path from start to 
  // destination. Fares are free and transfers are instant.
  std::shared_ptr<Route> basic_DSP(std::shared_ptr<Station> start,
                                   std::shared_ptr<Station> destination);

  // // Print Dijkstra's shortest (quickest) path from start to 
  // // destination. Fares are free and transfers are instant.
  // void print_basic_DSP(std::shared_ptr<Station> start, std::shared_ptr<Station> destination);

  // // Find Yen's K shortest (quickest) paths. Fares are free and transfers are instant.
  // std::vector<std::shared_ptr<Route>> basic_yen(std::shared_ptr<Station> start,
  //                                               std::shared_ptr<Station> destination,
  //                                               int k);

private:
  std::vector<std::shared_ptr<Station>> stations;
  std::unordered_map<std::string, std::vector<std::shared_ptr<Track>>> tracks;
  
};

#endif // NETWORK_H