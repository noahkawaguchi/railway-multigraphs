#include <gtest/gtest.h>

#include "../include/Network.h"

TEST(TestNetwork, GetAdjacentTracks) {
  // Create network
  auto transfer_network = std::make_unique<Network>();

  // Add Red Line stops to network
  auto red_line = std::make_shared<Line>(Line{"Red Line"});
  std::shared_ptr<Stop> R1 = transfer_network->new_stop("R1", red_line);
  std::shared_ptr<Stop> R2 = transfer_network->new_stop("R2", red_line);
  std::shared_ptr<Stop> R3 = transfer_network->new_stop("R3", red_line);
  std::shared_ptr<Stop> R4 = transfer_network->new_stop("R4", red_line);

  // Connect Red Line stops with tracks
  transfer_network->new_track(R1, R2, 2);
  transfer_network->new_track(R2, R3, 3);
  transfer_network->new_track(R3, R4, 2);

  // Add Blue Line stops to network
  auto blue_line = std::make_shared<Line>(Line{"Blue Line"});
  std::shared_ptr<Stop> B1 = transfer_network->new_stop("B1", blue_line);
  std::shared_ptr<Stop> B2 = transfer_network->new_stop("B2", blue_line);
  std::shared_ptr<Stop> B3 = transfer_network->new_stop("B3", blue_line);
  std::shared_ptr<Stop> B4 = transfer_network->new_stop("B4", blue_line);

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
  std::unordered_set<std::shared_ptr<Track>> R2_adj_tracks = transfer_network->get_adjacent_tracks(R2);
  std::unordered_set<std::shared_ptr<Stop>> R2_adj_stops;
  for (const auto& track : R2_adj_tracks) {
    R2_adj_stops.insert(track->other_stop);
  }
  EXPECT_TRUE(R2_adj_stops.contains(R1));
  EXPECT_TRUE(R2_adj_stops.contains(R3));
  EXPECT_FALSE(R2_adj_stops.contains(B2));
  EXPECT_FALSE(R2_adj_stops.contains(B4));
  EXPECT_FALSE(R2_adj_stops.contains(R4));
  EXPECT_FALSE(R2_adj_stops.contains(B1));

  std::unordered_set<std::shared_ptr<Track>> B2_adj_tracks = transfer_network->get_adjacent_tracks(B2);
  std::unordered_set<std::shared_ptr<Stop>> B2_adj_stops;
  for (const auto& track : B2_adj_tracks) {
    B2_adj_stops.insert(track->other_stop);
  }
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
  transfer_network->set_transfer(R2, B3);
  transfer_network->set_transfer(R3, B2);

  // Getting adjacent tracks for the transfer stops should now return tracks from both lines
  std::unordered_set<std::shared_ptr<Track>> R2_adj_tracks_tf = transfer_network->get_adjacent_tracks(R2);
  std::unordered_set<std::shared_ptr<Stop>> R2_adj_stops_tf;
  for (const auto& track : R2_adj_tracks_tf) {
    R2_adj_stops_tf.insert(track->other_stop);
  }
  EXPECT_TRUE(R2_adj_stops_tf.contains(R1));
  EXPECT_TRUE(R2_adj_stops_tf.contains(R3));
  EXPECT_TRUE(R2_adj_stops_tf.contains(B2));
  EXPECT_TRUE(R2_adj_stops_tf.contains(B4));
  EXPECT_FALSE(R2_adj_stops_tf.contains(R4));
  EXPECT_FALSE(R2_adj_stops_tf.contains(B1));

  std::unordered_set<std::shared_ptr<Track>> B2_adj_tracks_tf = transfer_network->get_adjacent_tracks(B2);
  std::unordered_set<std::shared_ptr<Stop>> B2_adj_stops_tf;
  for (const auto& track : B2_adj_tracks_tf) {
    B2_adj_stops_tf.insert(track->other_stop);
  }
  EXPECT_TRUE(B2_adj_stops_tf.contains(B1));
  EXPECT_TRUE(B2_adj_stops_tf.contains(B3));
  EXPECT_TRUE(B2_adj_stops_tf.contains(R2));
  EXPECT_TRUE(B2_adj_stops_tf.contains(R4));
  EXPECT_FALSE(B2_adj_stops_tf.contains(B4));
  EXPECT_FALSE(B2_adj_stops_tf.contains(R1));
}

TEST(BasicDSP, ToyDataABCD) {
  // Make network
  auto ABCD = std::make_unique<Network>();

  // Add line and stops to network
  auto ABCD_line = std::make_shared<Line>(Line{"ABCD Line"});
  std::shared_ptr<Stop> stopA = ABCD->new_stop("Station A", ABCD_line);
  std::shared_ptr<Stop> stopB = ABCD->new_stop("Station B", ABCD_line);
  std::shared_ptr<Stop> stopC = ABCD->new_stop("Station C", ABCD_line);
  std::shared_ptr<Stop> stopD = ABCD->new_stop("Station D", ABCD_line);

  // Connect stops with tracks
  ABCD->new_track(stopA, stopB, 3);
  ABCD->new_track(stopA, stopC, 7);
  ABCD->new_track(stopB, stopC, 5);
  ABCD->new_track(stopB, stopD, 1);
  ABCD->new_track(stopC, stopD, 2);

  // Find the shortest path from A to C
  Route AC_route = ABCD->basic_DSP(stopA, stopC);
  Route correct_path_AC = {stopA, stopB, stopD, stopC};
  EXPECT_EQ(AC_route, correct_path_AC);

  // Find the shortest path from D to A
  Route DA_route = ABCD->basic_DSP(stopD, stopA);
  Route correct_path_DA = {stopD, stopB, stopA};
  EXPECT_EQ(DA_route, correct_path_DA);

}

TEST(BasicDSP, ToyDataTinyCity) {
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

  // Find the shortest path from the park to the airport
  Route park_airport_route = tiny_city->basic_DSP(park, airport);
  Route correct_path_park_airport = {park, west_residential, hospital, city_hall, airport};
  EXPECT_EQ(park_airport_route, correct_path_park_airport);

  // Find the shortest path from East Residential to West Residential
  Route east_west_route = tiny_city->basic_DSP(east_residential, west_residential);
  Route correct_path_east_west = {east_residential, airport, city_hall, hospital, west_residential};
  EXPECT_EQ(east_west_route, correct_path_east_west);

  // Find the shortest path from the seaport to the hospital
  Route seaport_hospital_route = tiny_city->basic_DSP(seaport, hospital);
  Route correct_path_seaport_hospital = {seaport, mall, city_hall, hospital};
  EXPECT_EQ(seaport_hospital_route, correct_path_seaport_hospital);

}

TEST(CostDSP, ToyDataLongCheapWay) {
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

  // Basic DSP should find the path with the shortest distance, which is more expensive
  Route basic_DSP_route = cost_test_railway->basic_DSP(savings_A, savings_F);
  Route correct_expensive_route = {savings_A, savings_B, express_D, express_E, savings_F};
  EXPECT_EQ(basic_DSP_route, correct_expensive_route);
  // 1.1 + 1.9 + 2.1 + 0.9 = 6 mi
  EXPECT_FLOAT_EQ(basic_DSP_route.back()->path_distance, 6.0f);
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
  EXPECT_FLOAT_EQ(basic_DSP_route.back()->get_path_cost(), 5.18f);

  // Cost DSP should find the cheapest path, even though it is longer
  Route cost_DSP_route = cost_test_railway->cost_DSP(savings_A, savings_F);
  Route correct_cheap_route = {savings_A, savings_B, savings_C, savings_D, savings_E, savings_F};
  EXPECT_EQ(cost_DSP_route, correct_cheap_route);
  // 1.1 + 3.3 + 4.1 + 4.3 + 0.9 = 13.7 mi
  EXPECT_FLOAT_EQ(cost_DSP_route.back()->path_distance, 13.7f);
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
  EXPECT_FLOAT_EQ(cost_DSP_route.back()->get_path_cost(), 2.40f);

}
