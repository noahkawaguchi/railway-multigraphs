#include <memory>
#include <iostream>

#include "Network.h"

void toy_data_ABCD();
void toy_data_tiny_city();
void toy_data_long_cheap_way();

int main() {
  toy_data_ABCD();
  toy_data_tiny_city();
  toy_data_long_cheap_way();
  return 0;
}

void toy_data_ABCD() {
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

  // Make stations
  Station stationA = basic_network->new_station("Station A", {stopA});
  Station stationB = basic_network->new_station("Station B", {stopB});
  Station stationC = basic_network->new_station("Station C", {stopC});
  Station stationD = basic_network->new_station("Station D", {stopD});

  // Print the network
  basic_network->print();

  // Calculate Dijkstra's shortest path from Stop A to Stop C
  basic_network->print_route(basic_network->basic_DSP(stationA, stationC));
}

void toy_data_tiny_city() {
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
  
  // Make stations
  Station hospital_station = tiny_city->new_station("Hospital Station", {hospital});
  Station airport_station = tiny_city->new_station("Airport Station", {airport});
  Station west_residential_station = tiny_city->new_station("West Residential Station", {west_residential});
  Station city_hall_station = tiny_city->new_station("City Hall Station", {city_hall});
  Station east_residential_station = tiny_city->new_station("East Residential Station", {east_residential});
  Station park_station = tiny_city->new_station("Park Station", {park});
  Station mall_station = tiny_city->new_station("Mall Station", {mall});
  Station seaport_station = tiny_city->new_station("Seaport Station", {seaport});

  // Print the network
  tiny_city->print();

  // Calculate Dijkstra's shortest path from the park to the airport
  tiny_city->print_route(tiny_city->basic_DSP(park_station, airport_station));
}

void toy_data_long_cheap_way() {
  // Make a network
  auto cost_test_railway = std::make_unique<Network>();

  // Make a long, cheap line
  auto savings_line = std::make_shared<Line>(Line{"Savings Line", 0.75f, 0.12f});
  std::shared_ptr<Stop> savings_A = cost_test_railway->new_stop("Savings A", savings_line);
  std::shared_ptr<Stop> savings_B = cost_test_railway->new_stop("Savings B", savings_line);
  std::shared_ptr<Stop> savings_C = cost_test_railway->new_stop("Savings C", savings_line);
  std::shared_ptr<Stop> savings_D = cost_test_railway->new_stop("Savings D", savings_line);
  std::shared_ptr<Stop> savings_E = cost_test_railway->new_stop("Savings E", savings_line);
  std::shared_ptr<Stop> savings_F = cost_test_railway->new_stop("Savings F", savings_line);
  cost_test_railway->new_track(savings_A, savings_B, 1.1f);
  cost_test_railway->new_track(savings_B, savings_C, 3.3f);
  cost_test_railway->new_track(savings_C, savings_D, 4.1f);
  cost_test_railway->new_track(savings_D, savings_E, 4.3f);
  cost_test_railway->new_track(savings_E, savings_F, 0.9f);

  // Make a short, expensive line
  auto express_line = std::make_shared<Line>(Line{"Express Line", 1.80f, 0.41f});
  std::shared_ptr<Stop> express_B = cost_test_railway->new_stop("Express B", express_line);
  std::shared_ptr<Stop> express_D = cost_test_railway->new_stop("Express D", express_line);
  std::shared_ptr<Stop> express_E = cost_test_railway->new_stop("Express E", express_line);
  cost_test_railway->new_track(express_B, express_D, 1.9f);
  cost_test_railway->new_track(express_D, express_E, 2.1f);

  // Make stations (this sets transfers)
  Station stationA = cost_test_railway->new_station("Station A", {savings_A});
  Station stationB = cost_test_railway->new_station("Station B", {savings_B, express_B});
  Station stationC = cost_test_railway->new_station("Station C", {savings_C});
  Station stationD = cost_test_railway->new_station("Station D", {savings_D, express_D});
  Station stationE = cost_test_railway->new_station("Station E", {savings_E, express_E});
  Station stationF = cost_test_railway->new_station("Station F", {savings_F});

  // Print the network
  cost_test_railway->print();

  // Find the path from A to F with the shortest distance, which is more expensive
  cost_test_railway->print_route(cost_test_railway->basic_DSP(stationA, stationF));

  // Find the cheapest path from A to F, even though it is longer
  cost_test_railway->print_route(cost_test_railway->cost_DSP(stationA, stationF));
}
