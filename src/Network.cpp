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

void Network::new_track(std::shared_ptr<Stop> stop1, std::shared_ptr<Stop> stop2, double distance) {
  auto track_from_1 = std::make_shared<Track>(stop2, distance);
  auto track_from_2 = std::make_shared<Track>(stop1, distance);
  // Add track to the adjacency list for both stops
  this->tracks[stop1].insert(track_from_1);
  this->tracks[stop2].insert(track_from_2);
}

Station Network::new_station(std::string name, std::unordered_set<std::shared_ptr<Stop>> stops) {
  // Set stops as transfers for each other
  for (const auto& stop_outer : stops) {
    for (const auto& stop_inner : stops) {
      if (stop_inner != stop_outer) {
        stop_inner->transfers.insert(stop_outer);
        stop_outer->transfers.insert(stop_inner);
      }
    }
  }
  // Set the station name for all the stops
  for (const auto& stop : stops) { stop->station_name = name; }
  return Station{stops};
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

void Network::print_route(Route route) {
  std::cout << std::endl << std::string(20, '-') << std::endl;
  std::cout << "\nHere is your route from " << route.front()->station_name 
            << " to " << route.back()->station_name << ":\n" << std::endl;
  for (const auto& stop : route) {
    std::cout << "  ";
    if (stop == route.front()) {
      std::cout << "Start: " << stop->station_name;
    } else {
      std::cout << "-> Go to " << stop->station_name << " via the " << stop->line->name;
    }
    std::cout << std::endl;
  }
  std::cout << "\n  Total distance: " << route.back()->path_distance << " mi\n";
  // Always show the cost with cents
  double cost = route.back()->get_path_cost();
  if (cost != 0) {
    std::cout << "  Total cost: $" << std::format("{0:.2f}", cost) << std::endl;
  }
  std::cout << "\n" << std::string(20, '-') << '\n' << std::endl;
}

Route Network::distance_DSP(Station start, Station destination) {
  // Set all stops' distance and cost to "infinity" and predecessor to dummy predecessor
  for (const auto& stop : this->stops) {
    stop->path_reset();
  }

  // The algorithm works the same starting from any of the stops at the starting station
  std::shared_ptr<Stop> starting_stop = *start.begin();
  std::shared_ptr<Stop> destination_stop; // Will be set when found

  // Distance and cost from start to start is 0
  starting_stop->path_distance = 0.0;
  starting_stop->set_path_cost(0.0);

  // Enqueue all stops in unvisited queue
  UnvisitedQueue uq;
  for (const auto& stop : this->stops) {
    uq.push(stop, stop->path_distance);
  }

  // Visit each of the unvisited stops
  while (!uq.empty()) {
    // Visit minimum from unvisited queue
    std::shared_ptr<Stop> current_stop = uq.top_unprocessed();

    // Stop early if the destination is found
    if (destination.contains(current_stop)) {
      destination_stop = current_stop;
      break;
    }
    
    // Iterate over adjacent stops (via adjacent tracks)
    for (const auto& adj_track : this->get_adjacent_tracks(current_stop)) {
      double alt_path_distance = current_stop->path_distance + adj_track->distance;
      double alt_path_cost = current_stop->get_path_cost() + adj_track->get_cost_from(current_stop);

      // If a shorter path from the starting stop to the adjacent stop is found, 
      // or if the path is the same length but cheaper, update the adjacent stop's 
      // distance, cost, and predecessor.
      if (alt_path_distance < adj_track->other_stop->path_distance
          || (alt_path_distance == adj_track->other_stop->path_distance
              && alt_path_cost < adj_track->other_stop->get_path_cost()))
      {
        adj_track->other_stop->path_distance = alt_path_distance;
        adj_track->other_stop->set_path_cost(alt_path_cost);
        adj_track->other_stop->path_predecessor = current_stop;
        // The stop with modified data must be reinserted to maintain sorting
        uq.push(adj_track->other_stop, adj_track->other_stop->path_distance);
      }
    }
  }
  // Accumulate the path from start to destination in reverse using the predecessors
  Route route;
  std::shared_ptr<Stop> cursor = destination_stop;
  while (cursor != starting_stop) {
    route.push_back(cursor);
    cursor = cursor->path_predecessor;
  }
  route.push_back(starting_stop);
  // Reverse to get the stops in the correct order 
  std::reverse(route.begin(), route.end());
  return route;
}

Route Network::cost_DSP(Station start, Station destination) {
  // Set all stops' distance and cost to "infinity" and predecessor to dummy predecessor
  for (const auto& stop : this->stops) {
    stop->path_reset();
  }

  // The algorithm works the same starting from any of the stops at the starting station
  std::shared_ptr<Stop> starting_stop = *start.begin();
  std::shared_ptr<Stop> destination_stop; // Will be set when found

  // Distance and cost from start to start is 0
  starting_stop->path_distance = 0.0;
  starting_stop->set_path_cost(0.0);

  // Enqueue all stops in unvisited queue
  UnvisitedQueue uq;
  for (const auto& stop : this->stops) {
    uq.push(stop, stop->get_path_cost());
  }

  // Visit each of the unvisited stops
  while (!uq.empty()) {
    // Visit minimum from unvisited queue
    std::shared_ptr<Stop> current_stop = uq.top_unprocessed();

    // Stop early if the destination is found
    if (destination.contains(current_stop)) {
      destination_stop = current_stop;
      break;
    }

    // Iterate over adjacent stops (via adjacent tracks)
    for (const auto& adj_track : this->get_adjacent_tracks(current_stop)) {
      double alt_path_distance = current_stop->path_distance + adj_track->distance;
      double alt_path_cost = current_stop->get_path_cost() + adj_track->get_cost_from(current_stop);

      // If a cheaper path from the starting stop to the adjacent stop is found, 
      // or if the path is the same price but shorter, update the adjacent stop's 
      // distance, cost, and predecessor.
      if (alt_path_cost < adj_track->other_stop->get_path_cost()
          || (alt_path_cost == adj_track->other_stop->get_path_cost()
              && alt_path_distance < adj_track->other_stop->path_distance))
      {
        adj_track->other_stop->path_distance = current_stop->path_distance + adj_track->distance;
        adj_track->other_stop->set_path_cost(alt_path_cost);
        adj_track->other_stop->path_predecessor = current_stop;
        // The stop with modified data must be reinserted to maintain sorting
        uq.push(adj_track->other_stop, adj_track->other_stop->get_path_cost());
      }
    }
  }
  // Accumulate the path from start to destination in reverse using the predecessors
  Route route;
  std::shared_ptr<Stop> cursor = destination_stop;
  while (cursor != starting_stop) {
    route.push_back(cursor);
    cursor = cursor->path_predecessor;
  }
  route.push_back(starting_stop);
  // Reverse to get the stops in the correct order 
  std::reverse(route.begin(), route.end());
  return route;
}
