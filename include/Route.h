#ifndef ROUTE_H
#define ROUTE_H

#include <memory>
#include <vector>

#include "Station.h"

struct Route {
  std::vector<std::shared_ptr<Station>> stations;

  // Get the number of minutes it takes to traverse the route
  int get_minutes() {
    if (stations.empty()) {
      return 0;
    } else {
      return stations.back()->get_path_minutes();
    }
  }
};

#endif // ROUTE_H