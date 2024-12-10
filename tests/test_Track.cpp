#include <gtest/gtest.h>

#include "../include/Track.h"

TEST(TestTrack, InitTrack) {
  // Create a line and the station on the other side
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto test_station = std::make_shared<Station>("Test Station", test_line);
  // Create track
  auto test_track = std::make_shared<Track>(test_station, 5.4f);
  // Make sure data members were set correctly
  EXPECT_EQ(test_track->other_station, test_station);
  EXPECT_FLOAT_EQ(test_track->distance, 5.4f);
  EXPECT_EQ(test_track->other_station->line->name, "Test Line");
}

TEST(TestTrack, GetCost) {
  // Create the Red Line with three stations connected with tracks
  auto red_line = std::make_shared<Line>(Line{"Red Line", 1.60f, 0.32f});
  auto A = std::make_shared<Station>("A", red_line);
  auto B = std::make_shared<Station>("B", red_line);
  auto C = std::make_shared<Station>("C", red_line);
  auto A_B = std::make_shared<Track>(B, 3.2f);
  auto B_C = std::make_shared<Track>(C, 4.9f);

  // Case where all tracks and stations are on the same line
  A->set_path_cost(0.0f);
  B->set_path_cost(A_B->get_cost_from(A));
  // $1.60 base fare + $0.32 * 3.2 mi, rounded to cents
  EXPECT_FLOAT_EQ(B->get_path_cost(), 2.62f); 
  C->set_path_cost(B->get_path_cost() + B_C->get_cost_from(B));
  // Previous fare of $2.62 + $0.32 * 4.9 mi (not adding $1.60 base fare again), rounded to cents
  EXPECT_FLOAT_EQ(C->get_path_cost(), 4.19f);

  // Case where there is a transfer between lines
  auto blue_line = std::make_shared<Line>(Line{"Blue Line", 1.40f, 0.38f});
  C->line = blue_line;

  A->set_path_cost(0.0f);
  B->set_path_cost(A_B->get_cost_from(A));
  EXPECT_FLOAT_EQ(B->get_path_cost(), 2.62f); // Should be the same as above
  C->set_path_cost(B->get_path_cost() + B_C->get_cost_from(B));
  // Previous fare of $2.62 + $1.40 base fare due to transfer + $0.38 * 4.9 mi, rounded to cents
  EXPECT_FLOAT_EQ(C->get_path_cost(), 5.88f);

}
