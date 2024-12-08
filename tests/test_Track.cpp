#include <gtest/gtest.h>

#include "../include/Track.h"

TEST(TestTrack, InitTrack) {
  // Create the station on the other side
  std::shared_ptr<Station> test_station = std::make_shared<Station>("Test Station");
  // Create Track
  std::shared_ptr<Track> test_track = std::make_shared<Track>(test_station, 5.4f);
  // Make sure data members were set correctly
  ASSERT_EQ(test_track->other_station, test_station);
  ASSERT_EQ(test_track->distance, 5.4f);
}
