#include <memory>
#include <iostream>

#include "Network.h"

int main() {

  // Make network
  auto basic_network = std::make_unique<Network>();

  // Add line and stops to network
  auto ABCD_line = std::make_shared<Line>(Line{"ABCD Line"});
  std::shared_ptr<Stop> stopA = basic_network->new_stop("Stop A", ABCD_line);
  std::shared_ptr<Stop> stopB = basic_network->new_stop("Stop B", ABCD_line);
  std::shared_ptr<Stop> stopC = basic_network->new_stop("Stop C", ABCD_line);
  std::shared_ptr<Stop> stopD = basic_network->new_stop("Stop D", ABCD_line);

  // Connect stops with tracks
  basic_network->new_track(stopA, stopB, 3);
  basic_network->new_track(stopA, stopC, 7);
  basic_network->new_track(stopB, stopC, 5);
  basic_network->new_track(stopB, stopD, 1);
  basic_network->new_track(stopC, stopD, 2);

  // Print the network
  basic_network->print();

  // Calculate Dijkstra's shortest path from Stop A to Stop C
  basic_network->print_route(basic_network->basic_DSP(stopA, stopC));


  // Make network
  auto tiny_city = std::make_unique<Network>();

  // Add line and stops to network
  auto tiny_city_railway = std::make_shared<Line>(Line{"Tiny City Railway"});
  std::shared_ptr<Stop> hospital = tiny_city->new_stop("Hospital", tiny_city_railway);
  std::shared_ptr<Stop> airport = tiny_city->new_stop("Airport", tiny_city_railway);
  std::shared_ptr<Stop> west_residential = tiny_city->new_stop("West Residential", tiny_city_railway);
  std::shared_ptr<Stop> city_hall = tiny_city->new_stop("City Hall", tiny_city_railway);
  std::shared_ptr<Stop> east_residential = tiny_city->new_stop("East Residential", tiny_city_railway);
  std::shared_ptr<Stop> park = tiny_city->new_stop("Park", tiny_city_railway);
  std::shared_ptr<Stop> mall = tiny_city->new_stop("Mall", tiny_city_railway);
  std::shared_ptr<Stop> seaport = tiny_city->new_stop("Seaport", tiny_city_railway);

  // Connect stops with tracks
  tiny_city->new_track(hospital, west_residential, 2);
  tiny_city->new_track(hospital, city_hall, 3);
  tiny_city->new_track(airport, city_hall, 10);
  tiny_city->new_track(airport, east_residential, 7);
  tiny_city->new_track(west_residential, city_hall, 7);
  tiny_city->new_track(west_residential, park, 1);
  tiny_city->new_track(city_hall, mall, 2);
  tiny_city->new_track(east_residential, seaport, 8);
  tiny_city->new_track(park, mall, 7);
  tiny_city->new_track(mall, seaport, 8);

  // Print the network
  tiny_city->print();

  // Calculate Dijkstra's shortest path from the park to the airport
  tiny_city->print_route(tiny_city->basic_DSP(park, airport));



  return 0;
}
