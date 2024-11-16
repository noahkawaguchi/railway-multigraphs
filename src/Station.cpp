#include "Station.h"

Station::Station(char id) : id(id) {}

char Station::get_id() {
  return this->id;
}

int Station::get_dijkstra_minutes() {
  return this->dijkstra_minutes;
}

std::shared_ptr<Station> Station::get_dijkstra_predecessor() {
  return this->dijkstra_predecessor;
}

void Station::dijkstra_reset() {
  this->dijkstra_minutes = std::numeric_limits<int>::max(); // "Infinity"
  this->dijkstra_predecessor = nullptr;
}

