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
  void new_station(char id);

  // Create and add a track to the network, specifying the number of minutes 
  // it takes to go between the two stations with the given IDs
  void new_track(char id1, char id2, int minutes);

  // Find Dijkstra's shortest path from start to destination prioritizing time
  std::string DSP_time(char start, char destination);

  // Print a representation of the network
  void print();

private:
  std::unordered_map<char, std::shared_ptr<Station>> stations;
  std::vector<std::shared_ptr<Track>> tracks;

  // Custom comparator for priority queue
  struct MinimumMinutes {
    bool operator()(const std::shared_ptr<Station>& a, const std::shared_ptr<Station> b) {
      return a->get_dijkstra_minutes() > b->get_dijkstra_minutes();
    }
  };
  std::priority_queue<std::shared_ptr<Station>, std::vector<std::shared_ptr<Station>>,
                      MinimumMinutes> dijkstra_unvisited;

};

#endif // NETWORK_H