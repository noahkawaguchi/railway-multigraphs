#include <memory>

#include "Network.h"

int main() {

  // Make network
  std::unique_ptr<Network> basic_network = std::make_unique<Network>();

  // Add stations to network
  std::shared_ptr<Station> stationA = basic_network->new_station("Station A");
  std::shared_ptr<Station> stationB = basic_network->new_station("Station B");
  std::shared_ptr<Station> stationC = basic_network->new_station("Station C");
  std::shared_ptr<Station> stationD = basic_network->new_station("Station D");

  // Connect stations with tracks
  basic_network->new_track(stationA, stationB, 3);
  basic_network->new_track(stationA, stationC, 7);
  basic_network->new_track(stationB, stationC, 5);
  basic_network->new_track(stationB, stationD, 1);
  basic_network->new_track(stationC, stationD, 2);

  // Print the network
  basic_network->print();

  // Calculate Dijkstra's shortest path from Station A to all other stations
  basic_network->basic_DSP(stationA);

  // Calculate Dijkstra's shortest path from Station A to station C
  basic_network->basic_DSP(stationA, stationC);

  /*
    TODO:
      Make two arg output more readable
  */




  return 0;
}
