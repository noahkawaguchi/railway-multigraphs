#include <iostream>
#include <algorithm>

#include "Network.h"
#include "UnvisitedQueue.h"

Network::Network() {}

std::shared_ptr<Station> Network::new_station(std::string name, std::shared_ptr<Line> line) {
  auto station = std::make_shared<Station>(name, line);
  this->stations.push_back(station);
  return station;
}

void Network::new_track(std::shared_ptr<Station> station1,
                        std::shared_ptr<Station> station2,
                        float distance) 
{
  auto track_from_1 = std::make_shared<Track>(station2, distance);
  auto track_from_2 = std::make_shared<Track>(station1, distance);
  // Add track to the adjacency list for both stations
  this->tracks[station1].insert(track_from_1);
  this->tracks[station2].insert(track_from_2);
}

void Network::set_transfer(std::shared_ptr<Station> station1, std::shared_ptr<Station> station2) {
  station1->transfers.insert(station2);
  station2->transfers.insert(station1);
}

std::unordered_set<std::shared_ptr<Track>> Network::get_adjacent_tracks(std::shared_ptr<Station> station) {
  std::unordered_set<std::shared_ptr<Track>> ret = this->tracks[station]; // Input station's adjacent tracks
  if (!station->transfers.empty()) {
    // Adjacent tracks from transfers
    for (const auto& transfer : station->transfers) {
      // Make a copy so merge doesn't clear the contents of transfer's tracks
      std::unordered_set<std::shared_ptr<Track>> transfer_tracks = this->tracks[transfer];
      ret.merge(transfer_tracks);
    }
  }
  return ret;
}

void Network::print() {
  std::cout << std::endl << std::string(20, '-') << '\n' << std::endl;
  for (const auto& station : this->stations) {
    std::cout << station->name << " connections:\n";
    for (const auto& track : this->tracks[station]) {
      std::cout << "  " << track->distance << " mi to "<< track->other_station->name << '\n';
    }
    std::cout << std::endl; 
  }
  std::cout << std::string(20, '-') << '\n' << std::endl;
}

void Network::print_route(Route route) {
  std::cout << std::endl << std::string(20, '-') << std::endl;
  std::cout << "\nHere is your route from " << route.front()->name 
            << " to " << route.back()->name << ":\n" << std::endl;
  std::cout << "  ";
  for (const auto& station : route) {
    std::cout << station->name;
    if (station != route.back()) {
      std::cout << " -> ";
    }
  }
  std::cout << "\n  Total distance: " << route.back()->path_distance << " mi\n";
  std::cout << "  Total cost: $" << route.back()->get_path_cost() << "\n\n";
  std::cout << std::string(20, '-') << '\n' << std::endl;
}

// *** SHORTEST PATH ALGORITHMS *** //

Route Network::basic_DSP(std::shared_ptr<Station> start, std::shared_ptr<Station> destination) {
  // Set all stations' distance and cost to "infinity" and predecessor to dummy predecessor
  for (const auto& station : this->stations) {
    station->path_reset();
  }

  // Distance and cost from start to start is 0
  start->path_distance = 0.0f;
  start->set_path_cost(0.0f);

  // Enqueue all stations in unvisited queue
  UnvisitedQueue uq;
  for (const auto& station : this->stations) {
    uq.push(station, station->path_distance);
  }

  // Visit each of the unvisited stations
  while (!uq.empty()) {
    // Visit minimum from unvisited queue
    std::shared_ptr<Station> current_station = uq.top_unprocessed();

    // Stop early if the destination is found
    if (current_station == destination) { break; }
    
    // Iterate over adjacent stations (via adjacent tracks)
    for (const auto& adj_track : this->get_adjacent_tracks(current_station)) {
      float alt_path_distance = current_station->path_distance + adj_track->distance;

      // If a shorter path from the starting station to the adjacent station 
      // is found, update the adjacent station's distance, cost, and predecessor.
      if (alt_path_distance < adj_track->other_station->path_distance) {
        adj_track->other_station->path_distance = alt_path_distance;
        adj_track->other_station->set_path_cost(current_station->get_path_cost() 
                                                + adj_track->get_cost_from(current_station));
        adj_track->other_station->path_predecessor = current_station;
        // The station with modified data must be reinserted to maintain sorting
        uq.push(adj_track->other_station, adj_track->other_station->path_distance);
      }
    }
  }

  // Accumulate the path from start to destination in reverse using the predecessors
  Route route;
  std::shared_ptr<Station> cursor = destination;
  while (cursor != start) {
    route.push_back(cursor);
    cursor = cursor->path_predecessor;
  }
  route.push_back(start);
  // Reverse to get the stations in the correct order 
  std::reverse(route.begin(), route.end());

  return route;
}

Route Network::cost_DSP(std::shared_ptr<Station> start, std::shared_ptr<Station> destination) {
 // Set all stations' distance and cost to "infinity" and predecessor to dummy predecessor
  for (const auto& station : this->stations) {
    station->path_reset();
  }

  // Distance and cost from start to start is 0
  start->path_distance = 0.0f;
  start->set_path_cost(0.0f);

  // Enqueue all stations in unvisited queue
  UnvisitedQueue uq;
  for (const auto& station : this->stations) {
    uq.push(station, station->get_path_cost());
  }

  // Visit each of the unvisited stations
  while (!uq.empty()) {
    // Visit minimum from unvisited queue
    std::shared_ptr<Station> current_station = uq.top_unprocessed();

    // Stop early if the destination is found
    if (current_station == destination) { break; }
    
    // Iterate over adjacent stations (via adjacent tracks)

    for (const auto& adj_track : this->get_adjacent_tracks(current_station)) {
      float alt_path_cost = current_station->get_path_cost() + adj_track->get_cost_from(current_station);

      // If a cheaper path from the starting station to the adjacent station 
      // is found, update the adjacent station's distance, cost, and predecessor.
      if (alt_path_cost < adj_track->other_station->get_path_cost()) {
        adj_track->other_station->path_distance = current_station->path_distance + adj_track->distance;
        adj_track->other_station->set_path_cost(alt_path_cost);
        adj_track->other_station->path_predecessor = current_station;
        // The station with modified data must be reinserted to maintain sorting
        uq.push(adj_track->other_station, adj_track->other_station->get_path_cost());
      }
    }
  }

  // Accumulate the path from start to destination in reverse using the predecessors
  Route route;
  std::shared_ptr<Station> cursor = destination;
  while (cursor != start) {
    route.push_back(cursor);
    cursor = cursor->path_predecessor;
  }
  route.push_back(start);
  // Reverse to get the stations in the correct order 
  std::reverse(route.begin(), route.end());

  return route;
}

// Custom comparator for Yen priority queue
struct ShorterPath {
  bool operator()(std::shared_ptr<Route>& a, std::shared_ptr<Route>& b) {
    return a->back()->path_distance > b->back()->path_distance;
  }
};

std::vector<Route> Network::basic_yen(std::shared_ptr<Station> start,
                                                       std::shared_ptr<Station> destination,
                                                       int k)
{
  std::vector<Route> A; // K shortest paths in order of shortest to longest
  std::priority_queue<std::shared_ptr<Route>,
                      std::vector<std::shared_ptr<Route>>,
                      ShorterPath> B; // Candidate paths

  // Find #1 shortest path using regular Dijkstra
  A.push_back(this->basic_DSP(start, destination));

  // For each node in the path most recently added to A other 
  // than the destination, that node becomes the spur node 



  // TODO
  



  // Just to avoid compiler warnings for now
  Route dummy_route;
  std::vector<Route> dummy_ret = {dummy_route};
  return dummy_ret;
}
