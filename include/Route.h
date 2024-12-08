#ifndef ROUTE_H
#define ROUTE_H

#include <memory>
#include <vector>

#include "Station.h"

struct Route {
  std::vector<std::shared_ptr<Station>> stations;

  // Get the distance traveled when traversing the route
  float get_distance() {
    if (stations.empty()) {
      return 0.0f;
    } else {
      return stations.back()->get_path_distance();
    }
  }
};

#endif // ROUTE_H