#include <gtest/gtest.h>

#include "../include/track.hpp"

TEST(TestTrack, InitTrack) {
  // Create a line and the stop on the other side
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
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
  auto red_line = std::make_shared<Line>(Line{"Red Line", 1.60, 0.32});
  auto A = std::make_shared<Stop>("A", red_line);
  auto B = std::make_shared<Stop>("B", red_line);
  auto C = std::make_shared<Stop>("C", red_line);
  auto A_B = std::make_shared<Track>(B, 3.2);
  auto B_C = std::make_shared<Track>(C, 4.9);

  // Case where all tracks and stops are on the same line
  A->set_path_cost(0.0);
  B->set_path_cost(A_B->get_cost_from(A));
  // $1.60 base fare + $0.32 * 3.2 mi, rounded to cents
  EXPECT_DOUBLE_EQ(B->get_path_cost(), 2.62);
  C->set_path_cost(B->get_path_cost() + B_C->get_cost_from(B));
  // Previous fare of $2.62 + $0.32 * 4.9 mi (not adding $1.60 base fare again), rounded to cents
  EXPECT_DOUBLE_EQ(C->get_path_cost(), 4.19);

  // Case where there is a transfer between lines
  auto blue_line = std::make_shared<Line>(Line{"Blue Line", 1.40, 0.38});
  C->line = blue_line;

  A->set_path_cost(0.0);
  B->set_path_cost(A_B->get_cost_from(A));
  EXPECT_DOUBLE_EQ(B->get_path_cost(), 2.62); // Should be the same as above
  C->set_path_cost(B->get_path_cost() + B_C->get_cost_from(B));
  // Previous fare of $2.62 + $1.40 base fare due to transfer + $0.38 * 4.9 mi, rounded to cents
  EXPECT_DOUBLE_EQ(C->get_path_cost(), 5.88);
}
