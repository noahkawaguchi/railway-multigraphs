#ifndef NETWORK_H
#define NETWORK_H

#include <memory>
#include <vector>
#include <unordered_map>

#include "Station.h"
#include "Track.h"

class Network {
public:
  Network();
  ~Network() = default;

  // Create and add a station to the network with the given ID
  void new_station(char id);

  // Create and add a track to the network, specifying the number of minutes 
  // it takes to go between the two stations with the given IDs
  void new_track(char id1, char id2, int minutes);

  // Print a representation of the network
  void print();

private:
  std::unordered_map<char, std::shared_ptr<Station>> stations;
  std::vector<std::shared_ptr<Track>> tracks;

};

#endif // NETWORK_H