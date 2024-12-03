#include <iostream>

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

void Network::basic_DSP(std::shared_ptr<Station> start) {
  // Prepare for Dijkstra's shortest path
  for (const auto& station : this->stations) {
    // Set minutes to "infinity," predecessor to dummy predecessor, and processed to false
    station->dijkstra_reset();
    // Enqueue in unvisited queue
    this->dijkstra_unvisited.push(station);
  }

  // Time from start to start is 0
  start->set_dijkstra_minutes(0);

  // Visit each of the unvisited stations
  while (!this->dijkstra_unvisited.empty()) {
    // Visit minimum from unvisited queue
    std::shared_ptr<Station> current_station = this->dijkstra_unvisited.top();
    this->dijkstra_unvisited.pop();

    // Skip if this station has already been processed. (There may be 
    // duplicate pointers to processed stations left in the queue because 
    // of reinsertion.) Otherwise mark it as being processed now.
    if (current_station->get_dijkstra_processed()) { continue; }
    current_station->set_dijkstra_processed(true);
    
    // Iterate over adjacent stations (via adjacent tracks)
    for (const auto& adj_track : this->tracks[current_station->get_name()]) {
      int track_minutes = adj_track->minutes;
      int alt_path_minutes = current_station->get_dijkstra_minutes() + track_minutes;

      // If a shorter path from the starting station to the adjacent station 
      // is found, update the adjacent station's time and predecessor.
      if (alt_path_minutes < adj_track->other_station->get_dijkstra_minutes()) {
        adj_track->other_station->set_dijkstra_minutes(alt_path_minutes);
        adj_track->other_station->set_dijkstra_predecessor(current_station);
        // The station with modified data must be reinserted to maintain sorting
        this->dijkstra_unvisited.push(adj_track->other_station);
      }
    }
  }

  // Print full Dijkstra results
  std::cout << std::endl << std::string(20, '-') << std::endl;
  std::cout << "\nDijkstra's shortest path from " << start->get_name() << '\n' << std::endl;
  for (const auto& station : this->stations) {
    std::cout << "  " << station->get_name() << ":\n";
    std::cout << "    Minutes: " << station->get_dijkstra_minutes() << std::endl;
    std::cout << "    Predecessor: " << station->get_dijkstra_predecessor()->get_name() << std::endl;
    std::cout << std::endl;
  }
  std::cout << std::string(20, '-') << '\n' << std::endl;
}

void Network::basic_DSP(std::shared_ptr<Station> start, std::shared_ptr<Station> destination) {
  // Prepare for Dijkstra's shortest path
  for (const auto& station : this->stations) {
    // Set minutes to "infinity," predecessor to dummy predecessor, and processed to false
    station->dijkstra_reset();
    // Enqueue in unvisited queue
    this->dijkstra_unvisited.push(station);
  }

  // Time from start to start is 0
  start->set_dijkstra_minutes(0);

  // Visit each of the unvisited stations
  while (!this->dijkstra_unvisited.empty()) {
    // Visit minimum from unvisited queue
    std::shared_ptr<Station> current_station = this->dijkstra_unvisited.top();
    this->dijkstra_unvisited.pop();

    // Skip if this station has already been processed. (There may be 
    // duplicate pointers to processed stations left in the queue because 
    // of reinsertion.) Otherwise mark it as being processed now.
    if (current_station->get_dijkstra_processed()) { continue; }
    current_station->set_dijkstra_processed(true);

    // Stop early if the destination is found
    if (current_station == destination) { break; }
    
    // Iterate over adjacent stations (via adjacent tracks)
    for (const auto& adj_track : this->tracks[current_station->get_name()]) {
      int track_minutes = adj_track->minutes;
      int alt_path_minutes = current_station->get_dijkstra_minutes() + track_minutes;

      // If a shorter path from the starting station to the adjacent station 
      // is found, update the adjacent station's time and predecessor.
      if (alt_path_minutes < adj_track->other_station->get_dijkstra_minutes()) {
        adj_track->other_station->set_dijkstra_minutes(alt_path_minutes);
        adj_track->other_station->set_dijkstra_predecessor(current_station);
        // The station with modified data must be reinserted to maintain sorting
        this->dijkstra_unvisited.push(adj_track->other_station);
      }
    }
  }

  // Print the path from start to finish
  std::vector<std::shared_ptr<Station>> route;
  std::shared_ptr<Station> cursor = destination;
  while (cursor != start) {
    route.push_back(cursor);
    cursor = cursor->get_dijkstra_predecessor();
  }
  std::cout << "Start: " << start->get_name() << std::endl;
  for (int i = route.size() - 1; i >= 0; i--) {
    std::cout << route[i]->get_dijkstra_minutes() << " min to " << route[i]->get_name() << std::endl;
  }
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
