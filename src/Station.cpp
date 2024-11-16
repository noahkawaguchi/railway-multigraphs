#include "Station.h"

Station::Station(char id) : id(id) {}

char Station::get_id() {
  return this->id;
}
