#include <gtest/gtest.h>

#include "../include/Station.h"
#include "../include/Track.h"
#include "../include/Route.h"
#include "../include/Network.h"

TEST(TestTesting, TrivialEquality) {
  ASSERT_EQ(2+2, 4);
}

TEST(TestStation, InitStation) {
  std::shared_ptr<Station> test_station = std::make_shared<Station>("Test Station");
  ASSERT_EQ(test_station->get_name(), "Test Station");
}

TEST(HelperDSP, SimplestToyData) {
  // Make network
  std::unique_ptr<Network> basic_network = std::make_unique<Network>();

  // Add stations to network
  std::shared_ptr<Station> stationA = basic_network->new_station("Station A");
  std::shared_ptr<Station> stationB = basic_network->new_station("Station B");
  std::shared_ptr<Station> stationC = basic_network->new_station("Station C");
  std::shared_ptr<Station> stationD = basic_network->new_station("Station D");

  // Connect stations with tracks
  basic_network->new_track(stationA, stationB, 3);
  basic_network->new_track(stationA, stationC, 7);
  basic_network->new_track(stationB, stationC, 5);
  basic_network->new_track(stationB, stationD, 1);
  basic_network->new_track(stationC, stationD, 2);

  std::shared_ptr<Route> shortest_path = basic_network->helper_DSP(stationA, stationC);
  ASSERT_EQ(shortest_path->stations[0]->get_name(), "Station A");
  ASSERT_EQ(shortest_path->stations[1]->get_name(), "Station B");
  ASSERT_EQ(shortest_path->stations[2]->get_name(), "Station D");
  ASSERT_EQ(shortest_path->stations[3]->get_name(), "Station C");

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
