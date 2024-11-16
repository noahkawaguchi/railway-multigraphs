#include <iostream>

#include "Network.h"

Network::Network() {}

void Network::new_station(char id) {
  std::shared_ptr<Station> station = std::make_shared<Station>(id);
  this->stations[id] = station;
}

void Network::new_track(char id1, char id2, int minutes) {
  std::shared_ptr<Track> track = std::make_shared<Track>(
    this->stations[id1], this->stations[id2], minutes
  );
  this->tracks.push_back(track);
}

std::string Network::DSP_time(char start, char destination) {
  
  // Prepare for Dijkstra's shortest path
  for (const auto& pair : this->stations) {
    // Set minutes to "infinity" and predecessor to null
    pair.second->dijkstra_reset();
    // Enqueue in unvisited queue
    this->dijkstra_unvisited.push(pair.second);
  }
  
  // Get start and destination stations
  std::shared_ptr<Station> start_station = this->stations[start];
  std::shared_ptr<Station> destination_station = this->stations[destination];



  return "This is not done yet";
}

void Network::print() {
  std::cout << std::endl;
  for (const auto& track : this->tracks) {
    std::cout << track->get_station1()->get_id() << " <- " << track->get_minutes()
    << " min" << " -> " << track->get_station2()->get_id() << '\n';
  }
  std::cout << std::endl;
}
