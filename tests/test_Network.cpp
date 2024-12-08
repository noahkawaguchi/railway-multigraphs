#include <gtest/gtest.h>

#include "../include/Network.h"

TEST(TestNetwork, GetAdjacentTracks) {
  // Create network
  std::unique_ptr<Network> transfer_network = std::make_unique<Network>();

  // Add Red Line stations to network
  std::shared_ptr<Station> R1 = transfer_network->new_station("R1");
  std::shared_ptr<Station> R2 = transfer_network->new_station("R2");
  std::shared_ptr<Station> R3 = transfer_network->new_station("R3");
  std::shared_ptr<Station> R4 = transfer_network->new_station("R4");

  // Connect Red Line stations with tracks
  transfer_network->new_track(R1, R2, 2);
  transfer_network->new_track(R2, R3, 3);
  transfer_network->new_track(R3, R4, 2);

  // Add Blue Line stations to network
  std::shared_ptr<Station> B1 = transfer_network->new_station("B1");
  std::shared_ptr<Station> B2 = transfer_network->new_station("B2");
  std::shared_ptr<Station> B3 = transfer_network->new_station("B3");
  std::shared_ptr<Station> B4 = transfer_network->new_station("B4");

  // Connect Blue Line stations with tracks
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
  std::unordered_set<std::shared_ptr<Station>> R2_adj_stations;
  for (const auto& track : R2_adj_tracks) {
    R2_adj_stations.insert(track->other_station);
  }
  ASSERT_EQ(R2_adj_stations.contains(R1), true);
  ASSERT_EQ(R2_adj_stations.contains(R3), true);
  ASSERT_EQ(R2_adj_stations.contains(B2), false);
  ASSERT_EQ(R2_adj_stations.contains(B4), false);
  ASSERT_EQ(R2_adj_stations.contains(R4), false);
  ASSERT_EQ(R2_adj_stations.contains(B1), false);

  std::unordered_set<std::shared_ptr<Track>> B2_adj_tracks = transfer_network->get_adjacent_tracks(B2);
  std::unordered_set<std::shared_ptr<Station>> B2_adj_stations;
  for (const auto& track : B2_adj_tracks) {
    B2_adj_stations.insert(track->other_station);
  }
  ASSERT_EQ(B2_adj_stations.contains(B1), true);
  ASSERT_EQ(B2_adj_stations.contains(B3), true);
  ASSERT_EQ(B2_adj_stations.contains(R2), false);
  ASSERT_EQ(B2_adj_stations.contains(R4), false);
  ASSERT_EQ(B2_adj_stations.contains(B4), false);
  ASSERT_EQ(B2_adj_stations.contains(R1), false);
  
  /*
    Now add transfers. The Red Line and the Blue Line run in opposite 
    directions with their middle two stations overlapping.
    
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

  // Getting adjacent tracks for the transfer stations should now return tracks from both lines
  std::unordered_set<std::shared_ptr<Track>> R2_adj_tracks_tf = transfer_network->get_adjacent_tracks(R2);
  std::unordered_set<std::shared_ptr<Station>> R2_adj_stations_tf;
  for (const auto& track : R2_adj_tracks_tf) {
    R2_adj_stations_tf.insert(track->other_station);
  }
  ASSERT_EQ(R2_adj_stations_tf.contains(R1), true);
  ASSERT_EQ(R2_adj_stations_tf.contains(R3), true);
  ASSERT_EQ(R2_adj_stations_tf.contains(B2), true);
  ASSERT_EQ(R2_adj_stations_tf.contains(B4), true);
  ASSERT_EQ(R2_adj_stations_tf.contains(R4), false);
  ASSERT_EQ(R2_adj_stations_tf.contains(B1), false);

  std::unordered_set<std::shared_ptr<Track>> B2_adj_tracks_tf = transfer_network->get_adjacent_tracks(B2);
  std::unordered_set<std::shared_ptr<Station>> B2_adj_stations_tf;
  for (const auto& track : B2_adj_tracks_tf) {
    B2_adj_stations_tf.insert(track->other_station);
  }
  ASSERT_EQ(B2_adj_stations_tf.contains(B1), true);
  ASSERT_EQ(B2_adj_stations_tf.contains(B3), true);
  ASSERT_EQ(B2_adj_stations_tf.contains(R2), true);
  ASSERT_EQ(B2_adj_stations_tf.contains(R4), true);
  ASSERT_EQ(B2_adj_stations_tf.contains(B4), false);
  ASSERT_EQ(B2_adj_stations_tf.contains(R1), false);
}

TEST(BasicDSP, ToyDataABCD) {
  // Make network
  std::unique_ptr<Network> ABCD = std::make_unique<Network>();

  // Add stations to network
  std::shared_ptr<Station> stationA = ABCD->new_station("Station A");
  std::shared_ptr<Station> stationB = ABCD->new_station("Station B");
  std::shared_ptr<Station> stationC = ABCD->new_station("Station C");
  std::shared_ptr<Station> stationD = ABCD->new_station("Station D");

  // Connect stations with tracks
  ABCD->new_track(stationA, stationB, 3);
  ABCD->new_track(stationA, stationC, 7);
  ABCD->new_track(stationB, stationC, 5);
  ABCD->new_track(stationB, stationD, 1);
  ABCD->new_track(stationC, stationD, 2);

  // Find the shortest path from A to C
  std::shared_ptr<Route> AC_route = ABCD->basic_DSP(stationA, stationC);
  std::vector<std::shared_ptr<Station>> correct_path_AC = {stationA, stationB, stationD, stationC};
  ASSERT_EQ(AC_route->stations, correct_path_AC);

  // Find the shortest path from D to A
  std::shared_ptr<Route> DA_route = ABCD->basic_DSP(stationD, stationA);
  std::vector<std::shared_ptr<Station>> correct_path_DA = {stationD, stationB, stationA};
  ASSERT_EQ(DA_route->stations, correct_path_DA);

}

TEST(BasicDSP, ToyDataTinyCity) {
  // Make network
  std::unique_ptr<Network> tiny_city = std::make_unique<Network>();

  // Add stations to network
  std::shared_ptr<Station> hospital = tiny_city->new_station("Hospital");
  std::shared_ptr<Station> airport = tiny_city->new_station("Airport");
  std::shared_ptr<Station> west_residential = tiny_city->new_station("West Residential");
  std::shared_ptr<Station> city_hall = tiny_city->new_station("City Hall");
  std::shared_ptr<Station> east_residential = tiny_city->new_station("East Residential");
  std::shared_ptr<Station> park = tiny_city->new_station("Park");
  std::shared_ptr<Station> mall = tiny_city->new_station("Mall");
  std::shared_ptr<Station> seaport = tiny_city->new_station("Seaport");

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

  // Find the shortest path from the park to the airport
  std::shared_ptr<Route> park_airport_route = tiny_city->basic_DSP(park, airport);
  std::vector<std::shared_ptr<Station>> correct_path_park_airport = {
    park, west_residential, hospital, city_hall, airport
  };
  ASSERT_EQ(park_airport_route->stations, correct_path_park_airport);

  // Find the shortest path from East Residential to West Residential
  std::shared_ptr<Route> east_west_route = tiny_city->basic_DSP(east_residential, west_residential);
  std::vector<std::shared_ptr<Station>> correct_path_east_west = {
    east_residential, airport, city_hall, hospital, west_residential
  };
  ASSERT_EQ(east_west_route->stations, correct_path_east_west);

  // Find the shortest path from the seaport to the hospital
  std::shared_ptr<Route> seaport_hospital_route = tiny_city->basic_DSP(seaport, hospital);
  std::vector<std::shared_ptr<Station>> correct_path_seaport_hospital = {
    seaport, mall, city_hall, hospital
  };
  ASSERT_EQ(seaport_hospital_route->stations, correct_path_seaport_hospital);

}
