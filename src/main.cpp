#include <memory>

#include "Network.h"

int main() {

  // Make network
  std::unique_ptr<Network> memoryland_railways = std::make_unique<Network>();

  // Add stations to network
  std::shared_ptr<Station> stationA = memoryland_railways->new_station("Station A");
  std::shared_ptr<Station> stationB = memoryland_railways->new_station("Station B");
  std::shared_ptr<Station> stationC = memoryland_railways->new_station("Station C");
  std::shared_ptr<Station> stationD = memoryland_railways->new_station("Station D");

  // Connect stations with tracks
  memoryland_railways->new_track(stationA, stationB, 3);
  memoryland_railways->new_track(stationA, stationC, 7);
  memoryland_railways->new_track(stationB, stationC, 5);
  memoryland_railways->new_track(stationB, stationD, 1);
  memoryland_railways->new_track(stationC, stationD, 2);

  // Print the network
  memoryland_railways->print();

  // Calculate Dijkstra's shortest path from Station A (destination not implemented yet)
  memoryland_railways->DSP_time(stationA, stationB);



  return 0;
}
