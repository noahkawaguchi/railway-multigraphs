#include "Track.h"

Track::Track(std::shared_ptr<Station> station1, std::shared_ptr<Station> station2, int minutes)
    : station1(station1), station2(station2), minutes(minutes) {}

std::shared_ptr<Station> Track::get_station1() {
  return this->station1;
}

std::shared_ptr<Station> Track::get_station2() {
  return this->station2;
}

int Track::get_minutes() {
  return this->minutes;
}
