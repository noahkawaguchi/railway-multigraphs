#include <memory>

#include "Network.h"

int main() {

  // Make network
  std::unique_ptr<Network> memoryland_railways = std::make_unique<Network>();

  // Add stations to network
  memoryland_railways->new_station('A');
  memoryland_railways->new_station('B');
  memoryland_railways->new_station('C');
  memoryland_railways->new_station('D');

  // Connect stations with tracks
  memoryland_railways->new_track('A', 'B', 3);
  memoryland_railways->new_track('A', 'C', 7);
  memoryland_railways->new_track('B', 'C', 5);
  memoryland_railways->new_track('B', 'D', 1);
  memoryland_railways->new_track('C', 'D', 2);

  // Print the result
  memoryland_railways->print();


  return 0;
}
