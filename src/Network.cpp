#include <iostream>
#include <algorithm>

#include "Network.h"
#include "UnvisitedQueue.h"

Network::Network() {}

std::shared_ptr<Stop> Network::new_stop(std::string name, std::shared_ptr<Line> line) {
  auto stop = std::make_shared<Stop>(name, line);
  this->stops.push_back(stop);
  return stop;
}

void Network::new_track(std::shared_ptr<Stop> stop1, std::shared_ptr<Stop> stop2, float distance) {
  auto track_from_1 = std::make_shared<Track>(stop2, distance);
  auto track_from_2 = std::make_shared<Track>(stop1, distance);
  // Add track to the adjacency list for both stops
  this->tracks[stop1].insert(track_from_1);
  this->tracks[stop2].insert(track_from_2);
}

void Network::set_transfer(std::shared_ptr<Stop> stop1, std::shared_ptr<Stop> stop2) {
  stop1->transfers.insert(stop2);
  stop2->transfers.insert(stop1);
}

std::unordered_set<std::shared_ptr<Track>> Network::get_adjacent_tracks(std::shared_ptr<Stop> stop) {
  // Get the stop's adjacent tracks
  std::unordered_set<std::shared_ptr<Track>> ret = this->tracks[stop];
  // Get the adjacent tracks from any transfers
  if (!stop->transfers.empty()) {
    for (const auto& transfer : stop->transfers) {
      // Make a copy so merge() doesn't clear the contents of transfer's tracks
      std::unordered_set<std::shared_ptr<Track>> transfer_tracks = this->tracks[transfer];
      ret.merge(transfer_tracks);
    }
  }
  return ret;
}

void Network::print() {
  std::cout << std::endl << std::string(20, '-') << '\n' << std::endl;
  for (const auto& stop : this->stops) {
    std::cout << stop->name << " connections:\n";
    for (const auto& track : this->tracks[stop]) {
      std::cout << "  " << track->distance << " mi to "<< track->other_stop->name << '\n';
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
  for (const auto& stop : route) {
    std::cout << stop->name;
    if (stop != route.back()) {
      std::cout << " -> ";
    }
  }
  std::cout << "\n  Total distance: " << route.back()->path_distance << " mi\n";
  // Always show the cost with cents
  std::cout << "  Total cost: $" << std::format("{0:.2f}", route.back()->get_path_cost());
  std::cout << "\n\n" << std::string(20, '-') << '\n' << std::endl;
}

// *** SHORTEST PATH ALGORITHMS *** //

Route Network::basic_DSP(std::shared_ptr<Stop> start, std::shared_ptr<Stop> destination) {
  // Set all stops' distance and cost to "infinity" and predecessor to dummy predecessor
  for (const auto& stop : this->stops) {
    stop->path_reset();
  }

  // Distance and cost from start to start is 0
  start->path_distance = 0.0f;
  start->set_path_cost(0.0f);

  // Enqueue all stops in unvisited queue
  UnvisitedQueue uq;
  for (const auto& stop : this->stops) {
    uq.push(stop, stop->path_distance);
  }

  // Visit each of the unvisited stops
  while (!uq.empty()) {
    // Visit minimum from unvisited queue
    std::shared_ptr<Stop> current_station = uq.top_unprocessed();

    // Stop early if the destination is found
    if (current_station == destination) { break; }
    
    // Iterate over adjacent stops (via adjacent tracks)
    for (const auto& adj_track : this->get_adjacent_tracks(current_station)) {
      float alt_path_distance = current_station->path_distance + adj_track->distance;

      // If a shorter path from the starting stop to the adjacent stop is found, 
      // update the adjacent stop's distance, cost, and predecessor.
      if (alt_path_distance < adj_track->other_stop->path_distance) {
        adj_track->other_stop->path_distance = alt_path_distance;
        adj_track->other_stop->set_path_cost(current_station->get_path_cost() 
                                                + adj_track->get_cost_from(current_station));
        adj_track->other_stop->path_predecessor = current_station;
        // The stop with modified data must be reinserted to maintain sorting
        uq.push(adj_track->other_stop, adj_track->other_stop->path_distance);
      }
    }
  }
  // Accumulate the path from start to destination in reverse using the predecessors
  Route route;
  std::shared_ptr<Stop> cursor = destination;
  while (cursor != start) {
    route.push_back(cursor);
    cursor = cursor->path_predecessor;
  }
  route.push_back(start);
  // Reverse to get the stops in the correct order 
  std::reverse(route.begin(), route.end());
  return route;
}

Route Network::cost_DSP(std::shared_ptr<Stop> start, std::shared_ptr<Stop> destination) {
  // Set all stops' distance and cost to "infinity" and predecessor to dummy predecessor
  for (const auto& stop : this->stops) {
    stop->path_reset();
  }

  // Distance and cost from start to start is 0
  start->path_distance = 0.0f;
  start->set_path_cost(0.0f);

  // Enqueue all stops in unvisited queue
  UnvisitedQueue uq;
  for (const auto& stop : this->stops) {
    uq.push(stop, stop->get_path_cost());
  }

  // Visit each of the unvisited stops
  while (!uq.empty()) {
    // Visit minimum from unvisited queue
    std::shared_ptr<Stop> current_station = uq.top_unprocessed();

    // Stop early if the destination is found
    if (current_station == destination) { break; }
    
    // Iterate over adjacent stops (via adjacent tracks)

    for (const auto& adj_track : this->get_adjacent_tracks(current_station)) {
      float alt_path_cost = current_station->get_path_cost() + adj_track->get_cost_from(current_station);

      // If a cheaper path from the starting stop to the adjacent stop is found, 
      // update the adjacent stop's distance, cost, and predecessor.
      if (alt_path_cost < adj_track->other_stop->get_path_cost()) {
        adj_track->other_stop->path_distance = current_station->path_distance + adj_track->distance;
        adj_track->other_stop->set_path_cost(alt_path_cost);
        adj_track->other_stop->path_predecessor = current_station;
        // The stop with modified data must be reinserted to maintain sorting
        uq.push(adj_track->other_stop, adj_track->other_stop->get_path_cost());
      }
    }
  }
  // Accumulate the path from start to destination in reverse using the predecessors
  Route route;
  std::shared_ptr<Stop> cursor = destination;
  while (cursor != start) {
    route.push_back(cursor);
    cursor = cursor->path_predecessor;
  }
  route.push_back(start);
  // Reverse to get the stops in the correct order 
  std::reverse(route.begin(), route.end());
  return route;
}

// Custom comparator for Yen priority queue
struct ShorterPath {
  bool operator()(std::shared_ptr<Route>& a, std::shared_ptr<Route>& b) {
    return a->back()->path_distance > b->back()->path_distance;
  }
};

std::vector<Route> Network::basic_yen(std::shared_ptr<Stop> start,
                                      std::shared_ptr<Stop> destination,
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
