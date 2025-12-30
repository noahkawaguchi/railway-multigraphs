#include <gtest/gtest.h>

#include "../src/track.hpp"

TEST(TestTrack, InitTrack) {
  // Create a line and the stop on the other side
  auto test_line = std::make_shared<Line>(Line{.name = "Test Line"});
  auto test_stop = std::make_shared<Stop>("Test Stop", test_line);
  // Create track
  auto test_track = std::make_shared<Track>(test_stop, 5.4);
  // Make sure data members were set correctly
  EXPECT_EQ(test_track->other_stop, test_stop);
  EXPECT_DOUBLE_EQ(test_track->distance, 5.4);
  EXPECT_EQ(test_track->other_stop->line->name, "Test Line");
}

TEST(TestTrack, GetCost) {
  // Create the Red Line with three stops connected with tracks
  auto red_line =
      std::make_shared<Line>(Line{.name = "Red Line", .base_cost = 1.60, .cost_per_mile = 0.32});
  auto a = std::make_shared<Stop>("A", red_line);
  auto b = std::make_shared<Stop>("B", red_line);
  auto c = std::make_shared<Stop>("C", red_line);
  auto a_b = std::make_shared<Track>(b, 3.2);
  auto b_c = std::make_shared<Track>(c, 4.9);

  // Case where all tracks and stops are on the same line
  a->set_path_cost(0.0);
  b->set_path_cost(a_b->get_cost_from(a));
  // $1.60 base fare + $0.32 * 3.2 mi, rounded to cents
  EXPECT_DOUBLE_EQ(b->get_path_cost(), 2.62);
  c->set_path_cost(b->get_path_cost() + b_c->get_cost_from(b));
  // Previous fare of $2.62 + $0.32 * 4.9 mi (not adding $1.60 base fare again), rounded to cents
  EXPECT_DOUBLE_EQ(c->get_path_cost(), 4.19);

  // Case where there is a transfer between lines
  auto blue_line =
      std::make_shared<Line>(Line{.name = "Blue Line", .base_cost = 1.40, .cost_per_mile = 0.38});
  c->line = blue_line;

  a->set_path_cost(0.0);
  b->set_path_cost(a_b->get_cost_from(a));
  EXPECT_DOUBLE_EQ(b->get_path_cost(), 2.62); // Should be the same as above
  c->set_path_cost(b->get_path_cost() + b_c->get_cost_from(b));
  // Previous fare of $2.62 + $1.40 base fare due to transfer + $0.38 * 4.9 mi, rounded to cents
  EXPECT_DOUBLE_EQ(c->get_path_cost(), 5.88);
}
