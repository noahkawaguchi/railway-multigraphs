#include "Station.h"

// Dummy predecessor to point to by default
static std::shared_ptr<Station> dummy_predecessor = std::make_shared<Station>("No Predecessor");

Station::Station(std::string name) : name(name) {
  // Avoid dummy_predecessor pointing to itself
  if (this != dummy_predecessor.get()) {
    this->path_predecessor = dummy_predecessor;
  } else {
    this->path_predecessor = nullptr;
  }
}

std::string Station::get_name() {
  return this->name;
}

int Station::get_path_minutes() {
  return this->path_minutes;
}

std::shared_ptr<Station> Station::get_path_predecessor() {
  return this->path_predecessor;
}

bool Station::get_path_processed() {
  return this->path_processed;
}

void Station::set_path_minutes(int minutes) {
  this->path_minutes = minutes;
}

void Station::set_path_predecessor(std::shared_ptr<Station> predecessor) {
  this->path_predecessor = predecessor;
}

void Station::set_path_processed(bool processed) {
  this->path_processed = processed;
}

void Station::path_reset() {
  this->path_minutes = std::numeric_limits<int>::max() / 2; // "Infinity"
  this->path_predecessor = dummy_predecessor;
  this->path_processed = false;
}

