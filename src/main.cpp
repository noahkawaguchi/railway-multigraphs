#include <memory>
#include <iostream>

#include "Network.h"

int main() {

  // Make network
  auto basic_network = std::make_unique<Network>();

  // Add line and stations to network
  auto ABCD_line = std::make_shared<Line>(Line{"ABCD Line"});
  std::shared_ptr<Station> stationA = basic_network->new_station("Station A", ABCD_line);
  std::shared_ptr<Station> stationB = basic_network->new_station("Station B", ABCD_line);
  std::shared_ptr<Station> stationC = basic_network->new_station("Station C", ABCD_line);
  std::shared_ptr<Station> stationD = basic_network->new_station("Station D", ABCD_line);

  // Connect stations with tracks
  basic_network->new_track(stationA, stationB, 3);
  basic_network->new_track(stationA, stationC, 7);
  basic_network->new_track(stationB, stationC, 5);
  basic_network->new_track(stationB, stationD, 1);
  basic_network->new_track(stationC, stationD, 2);

  // Print the network
  basic_network->print();

  // Calculate Dijkstra's shortest path from Station A to Station C
  basic_network->print_route(basic_network->basic_DSP(stationA, stationC));


  // Make network
  auto tiny_city = std::make_unique<Network>();

  // Add line and stations to network
  auto tiny_city_railway = std::make_shared<Line>(Line{"Tiny City Railway"});
  std::shared_ptr<Station> hospital = tiny_city->new_station("Hospital", tiny_city_railway);
  std::shared_ptr<Station> airport = tiny_city->new_station("Airport", tiny_city_railway);
  std::shared_ptr<Station> west_residential = tiny_city->new_station("West Residential", tiny_city_railway);
  std::shared_ptr<Station> city_hall = tiny_city->new_station("City Hall", tiny_city_railway);
  std::shared_ptr<Station> east_residential = tiny_city->new_station("East Residential", tiny_city_railway);
  std::shared_ptr<Station> park = tiny_city->new_station("Park", tiny_city_railway);
  std::shared_ptr<Station> mall = tiny_city->new_station("Mall", tiny_city_railway);
  std::shared_ptr<Station> seaport = tiny_city->new_station("Seaport", tiny_city_railway);

  // Connect stations with tracks
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
