#include <memory>

#include "network.hpp"

namespace {

void toy_data_abcd();
void toy_data_tiny_city();
void toy_data_long_cheap_way();
void toy_data_real_multigraph_city();

} // namespace

auto main() -> int {
  toy_data_abcd();
  toy_data_tiny_city();
  toy_data_long_cheap_way();
  toy_data_real_multigraph_city();
}

namespace {

void toy_data_abcd() {
  // Make network
  auto basic_network = std::make_unique<Network>();

  // Add line and stops to network
  auto abcd_line = std::make_shared<Line>(Line{.name = "ABCD Line"});
  auto stopA = basic_network->new_stop("Stop A", abcd_line);
  auto stopB = basic_network->new_stop("Stop B", abcd_line);
  auto stopC = basic_network->new_stop("Stop C", abcd_line);
  auto stopD = basic_network->new_stop("Stop D", abcd_line);

  // Connect stops with tracks
  basic_network->new_track(stopA, stopB, 3);
  basic_network->new_track(stopA, stopC, 7);
  basic_network->new_track(stopB, stopC, 5);
  basic_network->new_track(stopB, stopD, 1);
  basic_network->new_track(stopC, stopD, 2);

  // Make stations
  Station stationA = Network::new_station("Station A", {stopA});
  Station stationB = Network::new_station("Station B", {stopB});
  Station stationC = Network::new_station("Station C", {stopC});
  Station stationD = Network::new_station("Station D", {stopD});

  // Calculate Dijkstra's shortest path from Stop A to Stop C
  Network::print_route(basic_network->distance_DSP({.start = stationA, .dest = stationC}));
}

void toy_data_tiny_city() {
  // Make network
  auto tiny_city = std::make_unique<Network>();

  // Add line and stops to network
  auto tiny_city_railway = std::make_shared<Line>(Line{.name = "Tiny City Railway"});
  auto hospital = tiny_city->new_stop("Hospital", tiny_city_railway);
  auto airport = tiny_city->new_stop("Airport", tiny_city_railway);
  auto west_residential = tiny_city->new_stop("West Residential", tiny_city_railway);
  auto city_hall = tiny_city->new_stop("City Hall", tiny_city_railway);
  auto east_residential = tiny_city->new_stop("East Residential", tiny_city_railway);
  auto park = tiny_city->new_stop("Park", tiny_city_railway);
  auto mall = tiny_city->new_stop("Mall", tiny_city_railway);
  auto seaport = tiny_city->new_stop("Seaport", tiny_city_railway);

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
  Station hospital_station = Network::new_station("Hospital Station", {hospital});
  Station airport_station = Network::new_station("Airport Station", {airport});
  Station west_residential_station =
      Network::new_station("West Residential Station", {west_residential});
  Station city_hall_station = Network::new_station("City Hall Station", {city_hall});
  Station east_residential_station =
      Network::new_station("East Residential Station", {east_residential});
  Station park_station = Network::new_station("Park Station", {park});
  Station mall_station = Network::new_station("Mall Station", {mall});
  Station seaport_station = Network::new_station("Seaport Station", {seaport});

  // Calculate Dijkstra's shortest path from the park to the airport
  Network::print_route(tiny_city->distance_DSP({.start = park_station, .dest = airport_station}));
}

void toy_data_long_cheap_way() {
  // Make a network
  auto cost_test_railway = std::make_unique<Network>();

  // Make a long, cheap line
  auto savings_line = std::make_shared<Line>(
      Line{.name = "Savings Line", .base_cost = 0.75, .cost_per_mile = 0.12});
  auto savings_A = cost_test_railway->new_stop("Savings A", savings_line);
  auto savings_B = cost_test_railway->new_stop("Savings B", savings_line);
  auto savings_C = cost_test_railway->new_stop("Savings C", savings_line);
  auto savings_D = cost_test_railway->new_stop("Savings D", savings_line);
  auto savings_E = cost_test_railway->new_stop("Savings E", savings_line);
  auto savings_F = cost_test_railway->new_stop("Savings F", savings_line);
  cost_test_railway->new_track(savings_A, savings_B, 1.1);
  cost_test_railway->new_track(savings_B, savings_C, 3.3);
  cost_test_railway->new_track(savings_C, savings_D, 4.1);
  cost_test_railway->new_track(savings_D, savings_E, 4.3);
  cost_test_railway->new_track(savings_E, savings_F, 0.9);

  // Make a short, expensive line
  auto express_line = std::make_shared<Line>(
      Line{.name = "Express Line", .base_cost = 1.80, .cost_per_mile = 0.41});
  auto express_B = cost_test_railway->new_stop("Express B", express_line);
  auto express_D = cost_test_railway->new_stop("Express D", express_line);
  auto express_E = cost_test_railway->new_stop("Express E", express_line);
  cost_test_railway->new_track(express_B, express_D, 1.9);
  cost_test_railway->new_track(express_D, express_E, 2.1);

  // Make stations (this sets transfers)
  Station stationA = Network::new_station("Station A", {savings_A});
  Station stationB = Network::new_station("Station B", {savings_B, express_B});
  Station stationC = Network::new_station("Station C", {savings_C});
  Station stationD = Network::new_station("Station D", {savings_D, express_D});
  Station stationE = Network::new_station("Station E", {savings_E, express_E});
  Station stationF = Network::new_station("Station F", {savings_F});

  // Find the path from A to F with the shortest distance, which is more expensive
  Network::print_route(cost_test_railway->distance_DSP({.start = stationA, .dest = stationF}));

  // Find the cheapest path from A to F, even though it is longer
  Network::print_route(cost_test_railway->cost_DSP({.start = stationA, .dest = stationF}));
}

void toy_data_real_multigraph_city() {
  // Make network
  auto real_multigraph_city = std::make_unique<Network>();

  // Make the Main Line
  auto main_line =
      std::make_shared<Line>(Line{.name = "Main Line", .base_cost = 1.50, .cost_per_mile = 0.25});
  auto m1 = real_multigraph_city->new_stop("M1", main_line);
  auto m2 = real_multigraph_city->new_stop("M2", main_line);
  auto m3 = real_multigraph_city->new_stop("M3", main_line);
  auto m4 = real_multigraph_city->new_stop("M4", main_line);
  real_multigraph_city->new_track(m1, m2, 7.0);
  real_multigraph_city->new_track(m2, m3, 4.4);
  real_multigraph_city->new_track(m3, m4, 3.5);

  // Make the Underground Loop
  auto underground_loop = std::make_shared<Line>(
      Line{.name = "Underground Loop", .base_cost = 1.75, .cost_per_mile = 0.35});
  auto u1 = real_multigraph_city->new_stop("U1", underground_loop);
  auto u2 = real_multigraph_city->new_stop("U2", underground_loop);
  auto u3 = real_multigraph_city->new_stop("U3", underground_loop);
  real_multigraph_city->new_track(u1, u2, 3.1);
  real_multigraph_city->new_track(u2, u3, 4.2);
  real_multigraph_city->new_track(u3, u1, 5.2);

  // Make the Commuter Local
  auto commuter_local = std::make_shared<Line>(
      Line{.name = "Commuter Local", .base_cost = 1.25, .cost_per_mile = 0.20});
  auto c1 = real_multigraph_city->new_stop("L1", commuter_local);
  auto c2 = real_multigraph_city->new_stop("L2", commuter_local);
  auto c3 = real_multigraph_city->new_stop("L3", commuter_local);
  auto c4 = real_multigraph_city->new_stop("L4", commuter_local);
  auto c5 = real_multigraph_city->new_stop("L5", commuter_local);
  real_multigraph_city->new_track(c1, c2, 4.3);
  real_multigraph_city->new_track(c2, c3, 2.7);
  real_multigraph_city->new_track(c3, c4, 2.2);
  real_multigraph_city->new_track(c4, c5, 6.2);

  // Make the Commuter Special
  auto commuter_special = std::make_shared<Line>(
      Line{.name = "Commuter Special", .base_cost = 2.00, .cost_per_mile = 0.30});
  auto s1 = real_multigraph_city->new_stop("S1", commuter_special);
  auto s2 = real_multigraph_city->new_stop("S2", commuter_special);
  auto s3 = real_multigraph_city->new_stop("S3", commuter_special);
  auto s4 = real_multigraph_city->new_stop("S4", commuter_special);
  real_multigraph_city->new_track(s1, s2, 4.3);
  real_multigraph_city->new_track(s2, s3, 3.9);
  real_multigraph_city->new_track(s3, s4, 7.5);

  // Make stations (this also sets transfers)
  Station seaport = Network::new_station("Seaport Station", {m1});
  Station south = Network::new_station("South Station", {m2, c5, u2});
  Station north = Network::new_station("North Station", {m3, s4, u1});
  Station airport = Network::new_station("Airport Station", {m4});
  Station city_center = Network::new_station("City Center Station", {c4, s3, u3});
  Station residential_east = Network::new_station("Residential East Station", {c3});
  Station commercial_center = Network::new_station("Commercial Center Station", {c2, s2});
  Station residential_west = Network::new_station("Residential West Station", {c1, s1});

  // Find the shortest path from Seaport Station to City Center Station
  Network::print_route(real_multigraph_city->distance_DSP({.start = seaport, .dest = city_center}));

  // Find the cheapest path from Seaport Station to City Center Station
  Network::print_route(real_multigraph_city->cost_DSP({.start = seaport, .dest = city_center}));

  // Find the shortest path from South Station to Airport Station
  Network::print_route(real_multigraph_city->distance_DSP({.start = south, .dest = airport}));

  // Find the cheapest path from South Station to Airport Station
  Network::print_route(real_multigraph_city->cost_DSP({.start = south, .dest = airport}));

  // Find the shortest path from Residential West Station to North Station
  Network::print_route(
      real_multigraph_city->distance_DSP({.start = residential_west, .dest = north}));

  // Find the cheapest path from Residential West Station to North Station
  Network::print_route(real_multigraph_city->cost_DSP({.start = residential_west, .dest = north}));
}

} // namespace
