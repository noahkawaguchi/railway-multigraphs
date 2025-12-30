#include <gtest/gtest.h>

#include "../src/network.hpp"

TEST(TestNetwork, GetAdjacentTracks) {
  // Create network
  auto transfer_network = std::make_unique<Network>();

  // Add Red Line stops to network
  auto red_line = std::make_shared<Line>(Line{.name = "Red Line"});
  auto R1 = transfer_network->new_stop("R1", red_line);
  auto R2 = transfer_network->new_stop("R2", red_line);
  auto R3 = transfer_network->new_stop("R3", red_line);
  auto R4 = transfer_network->new_stop("R4", red_line);

  // Connect Red Line stops with tracks
  transfer_network->new_track(R1, R2, 2);
  transfer_network->new_track(R2, R3, 3);
  transfer_network->new_track(R3, R4, 2);

  // Add Blue Line stops to network
  auto blue_line = std::make_shared<Line>(Line{.name = "Blue Line"});
  auto B1 = transfer_network->new_stop("B1", blue_line);
  auto B2 = transfer_network->new_stop("B2", blue_line);
  auto B3 = transfer_network->new_stop("B3", blue_line);
  auto B4 = transfer_network->new_stop("B4", blue_line);

  // Connect Blue Line stops with tracks
  transfer_network->new_track(B1, B2, 4);
  transfer_network->new_track(B2, B3, 3);
  transfer_network->new_track(B3, B4, 4);

  /*
    At this point, the only adjacent tracks are those in the same line.

                 B4
    R1          /
      \        /
       R2    B3
       |      |
       R3    B2
      /        \
    R4          \
                 B1

  */
  auto R2_adj_tracks = transfer_network->get_adjacent_tracks(R2);
  std::unordered_set<std::shared_ptr<Stop>> R2_adj_stops;
  for (const auto &track : R2_adj_tracks) { R2_adj_stops.insert(track->other_stop); }
  EXPECT_TRUE(R2_adj_stops.contains(R1));
  EXPECT_TRUE(R2_adj_stops.contains(R3));
  EXPECT_FALSE(R2_adj_stops.contains(B2));
  EXPECT_FALSE(R2_adj_stops.contains(B4));
  EXPECT_FALSE(R2_adj_stops.contains(R4));
  EXPECT_FALSE(R2_adj_stops.contains(B1));

  std::unordered_set<std::shared_ptr<Track>> B2_adj_tracks =
      transfer_network->get_adjacent_tracks(B2);
  std::unordered_set<std::shared_ptr<Stop>> B2_adj_stops;
  for (const auto &track : B2_adj_tracks) { B2_adj_stops.insert(track->other_stop); }
  EXPECT_TRUE(B2_adj_stops.contains(B1));
  EXPECT_TRUE(B2_adj_stops.contains(B3));
  EXPECT_FALSE(B2_adj_stops.contains(R2));
  EXPECT_FALSE(B2_adj_stops.contains(R4));
  EXPECT_FALSE(B2_adj_stops.contains(B4));
  EXPECT_FALSE(B2_adj_stops.contains(R1));

  /*
    Now add transfers. The Red Line and the Blue Line run in opposite
    directions with their middle two stops overlapping.

              B4
    R1       /
      \     /
       R2=B3
        ||
       R3=B2
      /     \
    R4       \
              B1

  */
  Network::new_station("R2-B3", {R2, B3});
  Network::new_station("R3-B2", {R3, B2});

  // Getting adjacent tracks for the transfer stops should now return tracks from both lines
  auto R2_adj_tracks_tf = transfer_network->get_adjacent_tracks(R2);
  std::unordered_set<std::shared_ptr<Stop>> R2_adj_stops_tf;
  for (const auto &track : R2_adj_tracks_tf) { R2_adj_stops_tf.insert(track->other_stop); }
  EXPECT_TRUE(R2_adj_stops_tf.contains(R1));
  EXPECT_TRUE(R2_adj_stops_tf.contains(R3));
  EXPECT_TRUE(R2_adj_stops_tf.contains(B2));
  EXPECT_TRUE(R2_adj_stops_tf.contains(B4));
  EXPECT_FALSE(R2_adj_stops_tf.contains(R4));
  EXPECT_FALSE(R2_adj_stops_tf.contains(B1));

  auto B2_adj_tracks_tf = transfer_network->get_adjacent_tracks(B2);
  std::unordered_set<std::shared_ptr<Stop>> B2_adj_stops_tf;
  for (const auto &track : B2_adj_tracks_tf) { B2_adj_stops_tf.insert(track->other_stop); }
  EXPECT_TRUE(B2_adj_stops_tf.contains(B1));
  EXPECT_TRUE(B2_adj_stops_tf.contains(B3));
  EXPECT_TRUE(B2_adj_stops_tf.contains(R2));
  EXPECT_TRUE(B2_adj_stops_tf.contains(R4));
  EXPECT_FALSE(B2_adj_stops_tf.contains(B4));
  EXPECT_FALSE(B2_adj_stops_tf.contains(R1));
}

TEST(DistanceDSP, ToyDataABCD) {
  // Make network
  auto ABCD = std::make_unique<Network>();

  // Add a line and stops to the network
  auto ABCD_line = std::make_shared<Line>(Line{.name = "ABCD Line"});
  auto stopA = ABCD->new_stop("A", ABCD_line);
  auto stopB = ABCD->new_stop("B", ABCD_line);
  auto stopC = ABCD->new_stop("C", ABCD_line);
  auto stopD = ABCD->new_stop("D", ABCD_line);

  // Connect stops with tracks
  ABCD->new_track(stopA, stopB, 3);
  ABCD->new_track(stopA, stopC, 7);
  ABCD->new_track(stopB, stopC, 5);
  ABCD->new_track(stopB, stopD, 1);
  ABCD->new_track(stopC, stopD, 2);

  // Make stations
  Station stationA = Network::new_station("Station A", {stopA});
  Station stationB = Network::new_station("Station B", {stopB});
  Station stationC = Network::new_station("Station C", {stopC});
  Station stationD = Network::new_station("Station D", {stopD});

  // Find the shortest path from Station A to Station C
  Route AC_route = ABCD->distance_DSP({.start = stationA, .dest = stationC});
  Route correct_path_AC = {stopA, stopB, stopD, stopC};
  EXPECT_EQ(AC_route, correct_path_AC);

  // Find the shortest path from Station D to Station A
  Route DA_route = ABCD->distance_DSP({.start = stationD, .dest = stationA});
  Route correct_path_DA = {stopD, stopB, stopA};
  EXPECT_EQ(DA_route, correct_path_DA);
}

TEST(DistanceDSP, ToyDataTinyCity) {
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

  // Find the shortest path from the park to the airport
  Route park_airport_route =
      tiny_city->distance_DSP({.start = park_station, .dest = airport_station});
  Route correct_path_park_airport = {park, west_residential, hospital, city_hall, airport};
  EXPECT_EQ(park_airport_route, correct_path_park_airport);

  // Find the shortest path from East Residential to West Residential
  Route east_west_route = tiny_city->distance_DSP(
      {.start = east_residential_station, .dest = west_residential_station});
  Route correct_path_east_west = {east_residential, airport, city_hall, hospital, west_residential};
  EXPECT_EQ(east_west_route, correct_path_east_west);

  // Find the shortest path from the seaport to the hospital
  Route seaport_hospital_route =
      tiny_city->distance_DSP({.start = seaport_station, .dest = hospital_station});
  Route correct_path_seaport_hospital = {seaport, mall, city_hall, hospital};
  EXPECT_EQ(seaport_hospital_route, correct_path_seaport_hospital);
}

TEST(CostDSP, ToyDataLongCheapWay) {
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

  // Distance DSP should find the path with the shortest distance, which is more expensive
  Route distance_DSP_route = cost_test_railway->distance_DSP({.start = stationA, .dest = stationF});
  Route correct_expensive_route = {savings_A, savings_B, express_D, express_E, savings_F};
  EXPECT_EQ(distance_DSP_route, correct_expensive_route);
  // 1.1 + 1.9 + 2.1 + 0.9 = 6 mi
  EXPECT_DOUBLE_EQ(distance_DSP_route.back()->path_distance, 6.0);
  /*
    A->B:
      $0.75 base fare + $0.12 * 1.1 mi = $0.88 (rounded)
    B->D:
      $0.88 previous fare + $1.80 base fare for transfer + $0.41 * 1.9 mi = $3.46 (rounded)
    D->E:
      $3.46 previous fare + $0.41 * 2.1 mi = $4.32 (rounded)
    E->F:
      $4.32 previous fare + $0.75 base fare for transfer + $0.12 * 0.9 mi = $5.18 (rounded)
  */
  EXPECT_DOUBLE_EQ(distance_DSP_route.back()->get_path_cost(), 5.18);

  // Cost DSP should find the cheapest path, even though it is longer
  Route cost_DSP_route = cost_test_railway->cost_DSP({.start = stationA, .dest = stationF});
  Route correct_cheap_route = {savings_A, savings_B, savings_C, savings_D, savings_E, savings_F};
  EXPECT_EQ(cost_DSP_route, correct_cheap_route);
  // 1.1 + 3.3 + 4.1 + 4.3 + 0.9 = 13.7 mi
  EXPECT_DOUBLE_EQ(cost_DSP_route.back()->path_distance, 13.7);
  /*
    A->B:
      $0.75 base fare + $0.12 * 1.1 mi = $0.88 (rounded)
    B->C:
      $0.88 previous fare + $0.12 * 3.3 mi = $1.28 (rounded)
    C->D:
      $1.28 previous fare + $0.12 * 4.1 mi = $1.77 (rounded)
    D->E:
      $1.77 previous fare + $0.12 * 4.3 mi = $2.29 (rounded)
    E->F:
      $2.29 previous fare + $0.12 * 0.9 mi = $2.40 (rounded)
  */
  EXPECT_DOUBLE_EQ(cost_DSP_route.back()->get_path_cost(), 2.40);
}

TEST(CostDSP, ToyDataRealMultigraphCity) {
  // Make network
  auto real_multigraph_city = std::make_unique<Network>();

  // Make the Main Line
  auto main_line =
      std::make_shared<Line>(Line{.name = "Main Line", .base_cost = 1.50, .cost_per_mile = 0.25});
  auto M1 = real_multigraph_city->new_stop("M1", main_line);
  auto M2 = real_multigraph_city->new_stop("M2", main_line);
  auto M3 = real_multigraph_city->new_stop("M3", main_line);
  auto M4 = real_multigraph_city->new_stop("M4", main_line);
  real_multigraph_city->new_track(M1, M2, 7.0);
  real_multigraph_city->new_track(M2, M3, 4.4);
  real_multigraph_city->new_track(M3, M4, 3.5);

  // Make the Underground Loop
  auto underground_loop = std::make_shared<Line>(
      Line{.name = "Underground Loop", .base_cost = 1.75, .cost_per_mile = 0.35});
  auto U1 = real_multigraph_city->new_stop("U1", underground_loop);
  auto U2 = real_multigraph_city->new_stop("U2", underground_loop);
  auto U3 = real_multigraph_city->new_stop("U3", underground_loop);
  real_multigraph_city->new_track(U1, U2, 3.1);
  real_multigraph_city->new_track(U2, U3, 4.2);
  real_multigraph_city->new_track(U3, U1, 5.2);

  // Make the Commuter Local
  auto commuter_local = std::make_shared<Line>(
      Line{.name = "Commuter Local", .base_cost = 1.25, .cost_per_mile = 0.20});
  auto L1 = real_multigraph_city->new_stop("L1", commuter_local);
  auto L2 = real_multigraph_city->new_stop("L2", commuter_local);
  auto L3 = real_multigraph_city->new_stop("L3", commuter_local);
  auto L4 = real_multigraph_city->new_stop("L4", commuter_local);
  auto L5 = real_multigraph_city->new_stop("L5", commuter_local);
  real_multigraph_city->new_track(L1, L2, 4.3);
  real_multigraph_city->new_track(L2, L3, 2.7);
  real_multigraph_city->new_track(L3, L4, 2.2);
  real_multigraph_city->new_track(L4, L5, 6.2);

  // Make the Commuter Special
  auto commuter_special = std::make_shared<Line>(
      Line{.name = "Commuter Special", .base_cost = 2.00, .cost_per_mile = 0.30});
  auto S1 = real_multigraph_city->new_stop("S1", commuter_special);
  auto S2 = real_multigraph_city->new_stop("S2", commuter_special);
  auto S3 = real_multigraph_city->new_stop("S3", commuter_special);
  auto S4 = real_multigraph_city->new_stop("S4", commuter_special);
  real_multigraph_city->new_track(S1, S2, 4.3);
  real_multigraph_city->new_track(S2, S3, 3.9);
  real_multigraph_city->new_track(S3, S4, 7.5);

  // Make stations (this also sets transfers)
  Station seaport = Network::new_station("Seaport Station", {M1});
  Station south = Network::new_station("South Station", {M2, L5, U2});
  Station north = Network::new_station("North Station", {M3, S4, U1});
  Station airport = Network::new_station("Airport Station", {M4});
  Station city_center = Network::new_station("City Center Station", {L4, S3, U3});
  Station residential_east = Network::new_station("Residential East Station", {L3});
  Station commercial_center = Network::new_station("Commercial Center Station", {L2, S2});
  Station residential_west = Network::new_station("Residential West Station", {L1, S1});

  // Find the shortest path from Seaport Station to City Center Station
  Route dist_DSP_sea_center =
      real_multigraph_city->distance_DSP({.start = seaport, .dest = city_center});
  Route correct_sea_center_dist = {M1, M2, U3};
  EXPECT_EQ(dist_DSP_sea_center, correct_sea_center_dist);
  EXPECT_DOUBLE_EQ(dist_DSP_sea_center.back()->path_distance, 11.2);
  EXPECT_DOUBLE_EQ(dist_DSP_sea_center.back()->get_path_cost(), 6.47);

  // Find the cheapest path from Seaport Station to City Center Station
  Route cost_DSP_sea_center =
      real_multigraph_city->cost_DSP({.start = seaport, .dest = city_center});
  Route correct_sea_center_cost = {M1, M2, L4};
  EXPECT_EQ(cost_DSP_sea_center, correct_sea_center_cost);
  EXPECT_DOUBLE_EQ(cost_DSP_sea_center.back()->path_distance, 13.2);
  EXPECT_DOUBLE_EQ(cost_DSP_sea_center.back()->get_path_cost(), 5.74);

  // Find the shortest path from South Station to Airport Station
  Route dist_DSP_south_air = real_multigraph_city->distance_DSP({.start = south, .dest = airport});
  EXPECT_TRUE(south.contains(dist_DSP_south_air.front())); // Starting Stop is arbitrary
  EXPECT_EQ(dist_DSP_south_air[1], U1);
  EXPECT_EQ(dist_DSP_south_air[2], M4);
  EXPECT_DOUBLE_EQ(dist_DSP_south_air.back()->path_distance, 6.6);
  EXPECT_DOUBLE_EQ(dist_DSP_south_air.back()->get_path_cost(), 5.22);

  // Find the cheapest path from South Station to Airport Station
  Route cost_DSP_south_air = real_multigraph_city->cost_DSP({.start = south, .dest = airport});
  EXPECT_TRUE(south.contains(cost_DSP_south_air.front())); // Starting Stop is arbitrary
  EXPECT_EQ(cost_DSP_south_air[1], M3);
  EXPECT_EQ(cost_DSP_south_air[2], M4);
  EXPECT_DOUBLE_EQ(cost_DSP_south_air.back()->path_distance, 7.9);
  EXPECT_DOUBLE_EQ(cost_DSP_south_air.back()->get_path_cost(), 3.48);

  // Find the shortest path from Residential West Station to North Station
  Route dist_DSP_res_west_north =
      real_multigraph_city->distance_DSP({.start = residential_west, .dest = north});
  // Starting Stop is arbitrary
  EXPECT_TRUE(residential_west.contains(dist_DSP_res_west_north.front()));
  EXPECT_EQ(dist_DSP_res_west_north[1], S2);
  EXPECT_EQ(dist_DSP_res_west_north[2], S3);
  EXPECT_EQ(dist_DSP_res_west_north[3], U1);
  EXPECT_DOUBLE_EQ(dist_DSP_res_west_north.back()->path_distance, 13.4);
  EXPECT_DOUBLE_EQ(dist_DSP_res_west_north.back()->get_path_cost(), 8.03);

  // Find the cheapest path from Residential West Station to North Station
  Route cost_DSP_res_west_north =
      real_multigraph_city->cost_DSP({.start = residential_west, .dest = north});
  // Starting Stop is arbitrary
  EXPECT_TRUE(residential_west.contains(cost_DSP_res_west_north.front()));
  EXPECT_EQ(cost_DSP_res_west_north[1], L2);
  EXPECT_EQ(cost_DSP_res_west_north[2], L3);
  EXPECT_EQ(cost_DSP_res_west_north[3], L4);
  EXPECT_EQ(cost_DSP_res_west_north[4], U1);
  EXPECT_DOUBLE_EQ(cost_DSP_res_west_north.back()->path_distance, 14.4);
  EXPECT_DOUBLE_EQ(cost_DSP_res_west_north.back()->get_path_cost(), 6.66);
}
