#include <gtest/gtest.h>

#include "../include/Station.h"

TEST(TestStation, InitStation) {
  // Create line and station
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto test_station = std::make_shared<Station>("Test Station", test_line);
  // Make sure names are set correctly
  ASSERT_EQ(test_station->name, "Test Station");
  ASSERT_EQ(test_station->line->name, "Test Line");
  // Make sure default path values are set correctly
  ASSERT_EQ(test_station->path_distance, 1.70141173e+38f);
  ASSERT_EQ(test_station->path_predecessor->name, "No Predecessor");
}

TEST(TestStation, SetPathStats) {
  // Create line and station
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto test_station = std::make_shared<Station>("Test Station", test_line);
  // Set shortest path stats
  test_station->path_distance = 5.3f;
  auto predecessor_station = std::make_shared<Station>("Predecessor Station", test_line);
  test_station->path_predecessor = predecessor_station;
  // Make sure shortest path stats are set properly
  ASSERT_EQ(test_station->path_distance, 5.3f);
  ASSERT_EQ(test_station->path_predecessor, predecessor_station);
}

TEST(TestStation, ResetPathStats) {
  // Create line and station
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto test_station = std::make_shared<Station>("Test Station", test_line);
  // Set shortest path stats
  test_station->path_distance = 10.2f;
  auto predecessor_station = std::make_shared<Station>("This Should Not Show", test_line);
  test_station->path_predecessor = predecessor_station;
  // Reset path stats
  test_station->path_reset();
  // Make sure path stats are back to their default values
  ASSERT_EQ(test_station->path_distance, 1.70141173e+38f);
  ASSERT_EQ(test_station->path_predecessor->name, "No Predecessor");
}

TEST(TestStation, Transfers) {
  // Create line and station
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto test_station = std::make_shared<Station>("Test Station", test_line);

  // Test getting transfers when there are none
  ASSERT_EQ(test_station->transfers.size(), 0);
  ASSERT_EQ(test_station->transfers.empty(), true);

  // Create and add transfers
  auto transfer1 = std::make_shared<Station>("Transfer 1", test_line);
  test_station->transfers.insert(transfer1);
  auto transfer2 = std::make_shared<Station>("Transfer 2", test_line);
  test_station->transfers.insert(transfer2);

  // Now we should be able to get these transfers and check membership
  ASSERT_EQ(test_station->transfers.contains(transfer1), true);
  ASSERT_EQ(test_station->transfers.contains(transfer2), true);
  ASSERT_EQ(test_station->transfers.contains(test_station), false);
}
