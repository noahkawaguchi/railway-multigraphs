#include <gtest/gtest.h>

#include "../include/Track.h"

TEST(TestTrack, InitTrack) {
  // Create the station on the other side
  auto test_station = std::make_shared<Station>("Test Station");
  // Create track
  auto test_track = std::make_shared<Track>(test_station, 5.4f);
  // Make sure data members were set correctly
  ASSERT_EQ(test_track->other_station, test_station);
  ASSERT_EQ(test_track->distance, 5.4f);
  ASSERT_EQ(test_track->line->name, "");
}

TEST(TestTrack, GetCost) {
  // Create the three stations and connect them with tracks
  auto A = std::make_shared<Station>("A");
  auto B = std::make_shared<Station>("B");
  auto C = std::make_shared<Station>("C");
  auto A_B = std::make_shared<Track>(B, 3.2f);
  auto B_C = std::make_shared<Track>(C, 4.9f);

  // Case where all tracks and stations are on the same line
  auto red_line = std::make_shared<Line>(Line{"Red Line", 1.60f, 0.32f});
  A->line = red_line;
  B->line = red_line;
  C->line = red_line;
  A_B->line = red_line;
  B_C->line = red_line;

  A->path_cost = 0.0f;
  B->path_cost = A_B->get_cost_from(A);
  // $1.60 base fare + $0.32 * 3.2 mi, rounded to cents
  ASSERT_EQ(B->path_cost, 2.62f); 
  C->path_cost = B->path_cost + B_C->get_cost_from(B);
  // Previous fare of $2.62 + $0.32 * 4.9 mi (not adding $1.60 base fare again), rounded to cents
  ASSERT_EQ(C->path_cost, 4.19f);

  // Case where there is a transfer between lines
  auto blue_line = std::make_shared<Line>(Line{"Blue Line", 1.40f, 0.38f});
  C->line = blue_line;
  B_C->line = blue_line;

  A->path_cost = 0.0f;
  B->path_cost = A_B->get_cost_from(A);
  ASSERT_EQ(B->path_cost, 2.62f); // Should be the same as above
  C->path_cost = B->path_cost + B_C->get_cost_from(B);
  // Previous fare of $2.62 + $1.40 base fare due to transfer + $0.38 * 4.9 mi, rounded to cents
  ASSERT_EQ(C->path_cost, 5.88f);

}
