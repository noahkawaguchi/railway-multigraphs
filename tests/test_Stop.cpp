#include <gtest/gtest.h>

#include "../include/Stop.h"

TEST(TestStop, InitStop) {
  // Create line and stop
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto test_stop = std::make_shared<Stop>("Test Stop", test_line);
  // Make sure names are set correctly
  EXPECT_EQ(test_stop->name, "Test Stop");
  EXPECT_EQ(test_stop->line->name, "Test Line");
  // Make sure default path values are set correctly
  EXPECT_EQ(test_stop->path_distance, 1.70141173e+38f);
  EXPECT_EQ(test_stop->path_predecessor->name, "No Predecessor");
}

TEST(TestStop, SetPathStats) {
  // Create line and stop
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto test_stop = std::make_shared<Stop>("Test Stop", test_line);
  // Set shortest path stats
  test_stop->path_distance = 5.3f;
  auto predecessor_stop = std::make_shared<Stop>("Predecessor Stop", test_line);
  test_stop->path_predecessor = predecessor_stop;
  // Make sure shortest path stats are set properly
  EXPECT_FLOAT_EQ(test_stop->path_distance, 5.3f);
  EXPECT_EQ(test_stop->path_predecessor, predecessor_stop);
}

TEST(TestStop, ResetPathStats) {
  // Create line and stop
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto test_stop = std::make_shared<Stop>("Test Stop", test_line);
  // Set shortest path stats
  test_stop->path_distance = 10.2f;
  auto predecessor_stop = std::make_shared<Stop>("This Should Not Show", test_line);
  test_stop->path_predecessor = predecessor_stop;
  // Reset path stats
  test_stop->path_reset();
  // Make sure path stats are back to their default values
  EXPECT_FLOAT_EQ(test_stop->path_distance, 1.70141173e+38f);
  EXPECT_EQ(test_stop->path_predecessor->name, "No Predecessor");
}

TEST(TestStop, Transfers) {
  // Create line and stop
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto test_stop = std::make_shared<Stop>("Test Stop", test_line);

  // Test getting transfers when there are none
  EXPECT_EQ(test_stop->transfers.size(), 0);
  EXPECT_TRUE(test_stop->transfers.empty());

  // Create and add transfers
  auto transfer1 = std::make_shared<Stop>("Transfer 1", test_line);
  test_stop->transfers.insert(transfer1);
  auto transfer2 = std::make_shared<Stop>("Transfer 2", test_line);
  test_stop->transfers.insert(transfer2);

  // Now we should be able to get these transfers and check membership
  EXPECT_TRUE(test_stop->transfers.contains(transfer1));
  EXPECT_TRUE(test_stop->transfers.contains(transfer2));
  EXPECT_FALSE(test_stop->transfers.contains(test_stop));
}
