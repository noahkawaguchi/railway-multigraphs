#include <gtest/gtest.h>

#include "../include/Station.h"

TEST(TestStation, InitStation) {
  // Create station
  std::shared_ptr<Station> test_station = std::make_shared<Station>("Test Station");
  // Make sure name is set correctly
  ASSERT_EQ(test_station->get_name(), "Test Station");
  // Make sure default values are set correctly
  ASSERT_EQ(test_station->get_path_minutes(), 1073741823);
  ASSERT_EQ(test_station->get_path_predecessor()->get_name(), "No Predecessor");
  ASSERT_EQ(test_station->get_path_processed(), false);
}

TEST(TestStation, SetPathStats) {
  // Create station
  std::shared_ptr<Station> test_station = std::make_shared<Station>("Test Station");
  // Set shortest path stats
  test_station->set_path_minutes(15);
  std::shared_ptr<Station> predecessor_station = std::make_shared<Station>("Predecessor Station");
  test_station->set_path_predecessor(predecessor_station);
  test_station->set_path_processed(true);
  // Make sure shortest path stats are set properly
  ASSERT_EQ(test_station->get_path_minutes(), 15);
  ASSERT_EQ(test_station->get_path_predecessor(), predecessor_station);
  ASSERT_EQ(test_station->get_path_processed(), true);
}

TEST(TestStation, ResetPathStats) {
  // Create station
  std::shared_ptr<Station> test_station = std::make_shared<Station>("Test Station");
  // Set shortest path stats
  test_station->set_path_minutes(10);
  std::shared_ptr<Station> predecessor_station = std::make_shared<Station>("This Should Not Show");
  test_station->set_path_predecessor(predecessor_station);
  test_station->set_path_processed(true);
  // Reset path stats
  test_station->path_reset();
  // Make sure path stats are back to their default values
  ASSERT_EQ(test_station->get_path_minutes(), 1073741823);
  ASSERT_EQ(test_station->get_path_predecessor()->get_name(), "No Predecessor");
  ASSERT_EQ(test_station->get_path_processed(), false);
}
