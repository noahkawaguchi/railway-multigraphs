#include "Station.h"

Station::Station(std::string name) : name(name) {}

std::string Station::get_name() {
  return this->name;
}

int Station::get_dijkstra_minutes() {
  return this->dijkstra_minutes;
}

std::shared_ptr<Station> Station::get_dijkstra_predecessor() {
  return this->dijkstra_predecessor;
}

void Station::set_dijkstra_minutes(int minutes) {
  this->dijkstra_minutes = minutes;
}

void Station::set_dijkstra_predecessor(std::shared_ptr<Station> predecessor) {
  this->dijkstra_predecessor = predecessor;
}

void Station::dijkstra_reset() {
  this->dijkstra_minutes = std::numeric_limits<int>::max(); // "Infinity"
  this->dijkstra_predecessor = nullptr;
}

