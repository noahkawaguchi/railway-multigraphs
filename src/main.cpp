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

  // Print the result
  memoryland_railways->print();
  
  
  // // Make network
  // std::unique_ptr<Network> memoryland_railways = std::make_unique<Network>();

  // // Add stations to network
  // memoryland_railways->new_station('A');
  // memoryland_railways->new_station('B');
  // memoryland_railways->new_station('C');
  // memoryland_railways->new_station('D');

  // // Connect stations with tracks
  // memoryland_railways->new_track('A', 'B', 3);
  // memoryland_railways->new_track('A', 'C', 7);
  // memoryland_railways->new_track('B', 'C', 5);
  // memoryland_railways->new_track('B', 'D', 1);
  // memoryland_railways->new_track('C', 'D', 2);

  // // Print the result
  // memoryland_railways->print();


  return 0;
}
