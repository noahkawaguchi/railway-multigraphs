#include <iostream>

#include "Network.h"

Network::Network() {}

void Network::new_station(char id) {
  std::shared_ptr<Station> station = std::make_shared<Station>(id);
  this->stations[id] = station;
  // this->stations.push_back(station);
}

void Network::new_track(char id1, char id2, int minutes) {
  std::shared_ptr<Track> track = std::make_shared<Track>(
    this->stations[id1], this->stations[id2], minutes
  );
  this->tracks.push_back(track);
}

void Network::print() {
  std::cout << std::endl;
  for (const auto& track : this->tracks) {
    std::shared_ptr<Station> station1 = track->get_station1();
    std::shared_ptr<Station> station2 = track->get_station2();

    std::cout << station1->get_id() << " <- " << track->get_minutes() << " min"
    << " -> " << station2->get_id() << '\n';
  }
  std::cout << std::endl;
}
