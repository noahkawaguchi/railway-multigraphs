#include <gtest/gtest.h>

#include "../include/Station.h"

TEST(TestStation, InitStation) {
  // Create station
  std::shared_ptr<Station> test_station = std::make_shared<Station>("Test Station");
  // Make sure name is set correctly
  ASSERT_EQ(test_station->get_name(), "Test Station");
  // Make sure default values are set correctly
  ASSERT_EQ(test_station->get_path_distance(), 1.70141173e+38f);
  ASSERT_EQ(test_station->get_path_predecessor()->get_name(), "No Predecessor");
}

TEST(TestStation, SetPathStats) {
  // Create station
  std::shared_ptr<Station> test_station = std::make_shared<Station>("Test Station");
  // Set shortest path stats
  test_station->set_path_distance(5.3f);
  std::shared_ptr<Station> predecessor_station = std::make_shared<Station>("Predecessor Station");
  test_station->set_path_predecessor(predecessor_station);
  // Make sure shortest path stats are set properly
  ASSERT_EQ(test_station->get_path_distance(), 5.3f);
  ASSERT_EQ(test_station->get_path_predecessor(), predecessor_station);
}

TEST(TestStation, ResetPathStats) {
  // Create station
  std::shared_ptr<Station> test_station = std::make_shared<Station>("Test Station");
  // Set shortest path stats
  test_station->set_path_distance(10.2f);
  std::shared_ptr<Station> predecessor_station = std::make_shared<Station>("This Should Not Show");
  test_station->set_path_predecessor(predecessor_station);
  // Reset path stats
  test_station->path_reset();
  // Make sure path stats are back to their default values
  ASSERT_EQ(test_station->get_path_distance(), 1.70141173e+38f);
  ASSERT_EQ(test_station->get_path_predecessor()->get_name(), "No Predecessor");
}

TEST(TestStation, Transfers) {
  // Create station
  std::shared_ptr<Station> test_station = std::make_shared<Station>("Test Station");

  // Test getting transfers when there are none
  std::unordered_set<std::shared_ptr<Station>> empty_transfers = test_station->get_transfers();
  ASSERT_EQ(empty_transfers.size(), 0);
  ASSERT_EQ(empty_transfers.empty(), true);

  // Create and add transfers
  std::shared_ptr<Station> transfer1 = std::make_shared<Station>("Transfer 1");
  test_station->set_transfer(transfer1);
  std::shared_ptr<Station> transfer2 = std::make_shared<Station>("Transfer 2");
  test_station->set_transfer(transfer2);

  // Now we should be able to get these transfers and check membership
  std::unordered_set<std::shared_ptr<Station>> test_transfers = test_station->get_transfers();
  ASSERT_EQ(test_transfers.contains(transfer1), true);
  ASSERT_EQ(test_transfers.contains(transfer2), true);
  ASSERT_EQ(test_transfers.contains(test_station), false);
}
