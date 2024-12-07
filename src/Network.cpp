#include <iostream>
#include <algorithm>

#include "Network.h"

Network::Network() {}

std::shared_ptr<Station> Network::new_station(std::string name) {
  std::shared_ptr<Station> station = std::make_shared<Station>(name);
  this->stations.push_back(station);
  return station;
}

void Network::new_track(std::shared_ptr<Station> station1,
                        std::shared_ptr<Station> station2,
                        int minutes) 
{
  std::shared_ptr<Track> track_from_1 = std::make_shared<Track>(station2, minutes);
  std::shared_ptr<Track> track_from_2 = std::make_shared<Track>(station1, minutes);
  // Add track to the adjacency list for both stations
  this->tracks[station1->get_name()].push_back(track_from_1);
  this->tracks[station2->get_name()].push_back(track_from_2);
}

void Network::print() {
  std::cout << std::endl << std::string(20, '-') << '\n' << std::endl;
  for (const auto& station : this->stations) {
    std::cout << station->get_name() << " connections:\n";
    for (const auto& track : this->tracks[station->get_name()]) {
      std::cout << "  " << track->minutes << " min to "<< track->other_station->get_name() << '\n';
    }
    std::cout << std::endl; 
  }
  std::cout << std::string(20, '-') << '\n' << std::endl;
}

// *** SHORTEST PATH ALGORITHMS *** //

// std::shared_ptr<Route> Network::basic_DSP(std::shared_ptr<Station> start,
//                                           std::shared_ptr<Station> destination)
// {
//   // Set all stations' minutes to "infinity," predecessor to dummy predecessor, and processed to false
//   for (const auto& station : this->stations) {
//     station->path_reset();
//   }

//   // Time from start to start is 0
//   start->set_path_minutes(0);

//   // Enqueue all stations in unvisited queue
//   for (const auto& station : this->stations) {
//     this->dijkstra_unvisited.push(station);
//   }

//   // Visit each of the unvisited stations
//   while (!this->dijkstra_unvisited.empty()) {
//     // Visit minimum from unvisited queue
//     std::shared_ptr<Station> current_station = this->dijkstra_unvisited.top();
//     this->dijkstra_unvisited.pop();

//     // Skip if this station has already been processed. (There may be 
//     // duplicate pointers to processed stations left in the queue because 
//     // of reinsertion.) Otherwise mark it as being processed now.
//     if (current_station->get_path_processed()) { continue; }
//     current_station->set_path_processed(true);

//     // Stop early if the destination is found
//     if (current_station == destination) { break; }
    
//     // Iterate over adjacent stations (via adjacent tracks)
//     for (const auto& adj_track : this->tracks[current_station->get_name()]) {
//       int track_minutes = adj_track->minutes;
//       int alt_path_minutes = current_station->get_path_minutes() + track_minutes;

//       // If a shorter path from the starting station to the adjacent station 
//       // is found, update the adjacent station's time and predecessor.
//       if (alt_path_minutes < adj_track->other_station->get_path_minutes()) {
//         adj_track->other_station->set_path_minutes(alt_path_minutes);
//         adj_track->other_station->set_path_predecessor(current_station);
//         // The station with modified data must be reinserted to maintain sorting
//         this->dijkstra_unvisited.push(adj_track->other_station);
//       }
//     }
//   }

//   // Accumulate the path from start to destination in reverse using the predecessors
//   std::shared_ptr<Route> route = std::make_shared<Route>();
//   std::shared_ptr<Station> cursor = destination;
//   while (cursor != start) {
//     route->stations.push_back(cursor);
//     cursor = cursor->get_path_predecessor();
//   }
//   route->stations.push_back(start);
//   // Reverse to get the stations in the correct order 
//   std::reverse(route->stations.begin(), route->stations.end());

//   return route;
// }

// void Network::print_basic_DSP(std::shared_ptr<Station> start, std::shared_ptr<Station> destination) {

//   // Get the shortest path
//   std::shared_ptr<Route> route = basic_DSP(start, destination);

//   // Print the path from start to destination
//   std::cout << std::endl << std::string(20, '-') << std::endl;
//   std::cout << "\nDijkstra's shortest path from " << start->get_name() 
//             << " to " << destination->get_name() << ":\n" << std::endl;
//   std::cout << "  ";
//   for (const auto& station : route->stations) {
//     std::cout << station->get_name();
//     if (station != route->stations.back()) {
//       std::cout << " -> ";
//     }
//   }
//   std::cout << "\n  Total time: " << destination->get_path_minutes() << " min\n\n";
//   std::cout << std::string(20, '-') << '\n' << std::endl;
// }

// // Custom comparator for Yen priority queue--orders by the minutes it takes to traverse the path
// struct ShorterPath {
//   bool operator()(std::shared_ptr<Route>& a, std::shared_ptr<Route>& b) {
//     return a->get_minutes() > b->get_minutes();
//   }
// };

// std::vector<std::shared_ptr<Route>> Network::basic_yen(std::shared_ptr<Station> start,
//                                                        std::shared_ptr<Station> destination,
//                                                        int k)
// {
//   std::vector<std::shared_ptr<Route>> A; // K shortest paths in order of shortest to longest
//   std::priority_queue<std::shared_ptr<Route>,
//                       std::vector<std::shared_ptr<Route>>,
//                       ShorterPath> B; // Candidate paths

//   // Find #1 shortest path using regular Dijkstra
//   A.push_back(this->basic_DSP(start, destination));

//   // For each node in the path most recently added to A other 
//   // than the destination, that node becomes the spur node 



//   // TODO
  



//   // Just to avoid compiler warnings for now
//   std::shared_ptr<Route> dummy_route = std::make_shared<Route>();
//   std::vector<std::shared_ptr<Route>> dummy_ret;
//   dummy_ret.push_back(dummy_route);
//   return dummy_ret;
// }
