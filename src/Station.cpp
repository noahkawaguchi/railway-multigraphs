#include "Station.h"

// Dummy predecessor to point to by default
static std::shared_ptr<Station> dummy_predecessor = std::make_shared<Station>("No predecessor");

Station::Station(std::string name) : name(name) {
  // Avoid dummy_predecessor pointing to itself
  if (this != dummy_predecessor.get()) {
    this->dijkstra_predecessor = dummy_predecessor;
  } else {
    this->dijkstra_predecessor = nullptr;
  }
}

std::string Station::get_name() {
  return this->name;
}

int Station::get_dijkstra_minutes() {
  return this->dijkstra_minutes;
}

std::shared_ptr<Station> Station::get_dijkstra_predecessor() {
  return this->dijkstra_predecessor;
}

bool Station::get_dijkstra_processed() {
  return this->dijkstra_processed;
}

void Station::set_dijkstra_minutes(int minutes) {
  this->dijkstra_minutes = minutes;
}

void Station::set_dijkstra_predecessor(std::shared_ptr<Station> predecessor) {
  this->dijkstra_predecessor = predecessor;
}

void Station::set_dijkstra_processed(bool processed) {
  this->dijkstra_processed = processed;
}

void Station::dijkstra_reset() {
  this->dijkstra_minutes = std::numeric_limits<int>::max(); // "Infinity"
  this->dijkstra_predecessor = dummy_predecessor;
  this->dijkstra_processed = false;
}

