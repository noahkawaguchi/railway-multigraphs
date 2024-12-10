#include <memory>
#include <iostream>

#include "Network.h"

int main() {

  // *** TOY DATA ABCD *** //

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

  // *** TOY DATA TINY CITY *** //

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

  // *** TOY DATA LONG CHEAP WAY ** //

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

  // Set transfers at B, D, and E
  cost_test_railway->set_transfer(savings_B, express_B);
  cost_test_railway->set_transfer(savings_D, express_D);
  cost_test_railway->set_transfer(savings_E, express_E);

  // Print the network
  cost_test_railway->print();

  // Find the path from A to F with the shortest distance, which is more expensive
  cost_test_railway->print_route(cost_test_railway->basic_DSP(savings_A, savings_F));

  // Find the cheapest path from A to F, even though it is longer
  cost_test_railway->print_route(cost_test_railway->cost_DSP(savings_A, savings_F));

  return 0;
}
