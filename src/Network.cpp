#include <iostream>

#include "Network.h"

Network::Network() {}

std::shared_ptr<Station> Network::new_station(std::string name) {
  std::shared_ptr<Station> station = std::make_shared<Station>(name);
  this->stations.push_back(station);
  return station;
}

void Network::new_track(std::shared_ptr<Station> station1, std::shared_ptr<Station> station2, int minutes) {
  std::shared_ptr<Track> track = std::make_shared<Track>(
    station1, station2, minutes
  );
  // this->tracks.push_back(track);
  // Add track to the adjacency list for both stations
  this->tracks[station1->get_name()].push_back(track);
  this->tracks[station2->get_name()].push_back(track);
}

std::string Network::DSP_time(std::shared_ptr<Station> start, std::shared_ptr<Station> destination) {
  
  // Prepare for Dijkstra's shortest path
  for (const auto& station : this->stations) {
    // Set minutes to "infinity" and predecessor to null
    station->dijkstra_reset();
    // Enqueue in unvisited queue
    this->dijkstra_unvisited.push(station);
  }

  // Time from start to start is 0
  start->set_dijkstra_minutes(0);

  while (!this->dijkstra_unvisited.empty()) {
    // Visit minimum from unvisited queue
    std::shared_ptr<Station> current_station = this->dijkstra_unvisited.top();
    this->dijkstra_unvisited.pop();
    
    // Iterate over adjacent stations
    for (const auto& adj_station : this->tracks[current_station->get_name()]) {
      // TODO
    }


  }


  return "This is not done yet";
}

void Network::print() {
  std::cout << std::endl;
  for (const auto& station : this->stations) {
    std::cout << station->get_name() << " connections:\n";
    for (const auto& track : this->tracks[station->get_name()]) {
      std::cout << "  " << track->get_station1()->get_name() << " <- " << track->get_minutes()
      << " min" << " -> " << track->get_station2()->get_name() << '\n';
    }
    std::cout << std::endl;
  }
}


// void Network::print() {
//   std::cout << std::endl;
//   for (const auto& track : this->tracks) {
//     std::cout << track->get_station1()->get_name() << " <- " << track->get_minutes()
//     << " min" << " -> " << track->get_station2()->get_name() << '\n';
//   }
//   std::cout << std::endl;
// }
