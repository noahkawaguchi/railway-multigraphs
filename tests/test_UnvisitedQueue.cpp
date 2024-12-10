#include <gtest/gtest.h>

#include "../include/UnvisitedQueue.h"

TEST(TestUQ, Top) {
  // Create line and stations
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto station1 = std::make_shared<Station>("Station 1", test_line);
  auto station2 = std::make_shared<Station>("Station 2", test_line);
  auto station3 = std::make_shared<Station>("Station 3", test_line);
  auto station4 = std::make_shared<Station>("Station 4", test_line);

  // Set priorities
  station1->path_distance = 5;
  station2->path_distance = 10;
  // (leave Station 3 as default)
  station4->path_distance = 2;

  // Create UnvisitedQueue and insert
  UnvisitedQueue uq;
  uq.push(station1, station1->path_distance);
  uq.push(station2, station2->path_distance);
  uq.push(station3, station3->path_distance);
  uq.push(station4, station4->path_distance);

  // Make sure top returns the correct station
  EXPECT_EQ(uq.top_unprocessed(), station4);
  EXPECT_EQ(uq.top_unprocessed(), station1);
  EXPECT_EQ(uq.top_unprocessed(), station2);
  EXPECT_EQ(uq.top_unprocessed(), station3);

}

TEST(TestUQ, Empty) {
  // Create UnvisitedQueue, which should start empty
  UnvisitedQueue uq;
  EXPECT_TRUE(uq.empty());

  // Create line and stations 
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto station1 = std::make_shared<Station>("Station 1", test_line);
  auto station2 = std::make_shared<Station>("Station 2", test_line);
  auto station3 = std::make_shared<Station>("Station 3", test_line);

  // Set priorities
  station1->path_distance = 7;
  station2->path_distance = 3;
  // (leave Station 3 as default)

  // Insert into queue
  uq.push(station1, station1->path_distance);
  uq.push(station2, station2->path_distance);
  uq.push(station3, station3->path_distance);

  // Now the queue should not be empty
  EXPECT_FALSE(uq.empty());

  // Update priority, reinsert, and process, leaving a processed duplicate in the queue
  station3->path_distance = 2;
  uq.push(station3, station3->path_distance);
  uq.top_unprocessed();

  // Remove both remaining processed stations
  uq.top_unprocessed();
  uq.top_unprocessed();

  // Now it should be empty again
  EXPECT_TRUE(uq.empty());
}

TEST(TestUQ, TopReinsertion) {
  // Create line and stations
  auto test_line = std::make_shared<Line>(Line{"Test Line"});
  auto A = std::make_shared<Station>("A", test_line);
  auto B = std::make_shared<Station>("B", test_line);
  auto C = std::make_shared<Station>("C", test_line);
  auto D = std::make_shared<Station>("D", test_line);
  auto E = std::make_shared<Station>("E", test_line);
  auto F = std::make_shared<Station>("F", test_line);

  // Set priority of C, leave the rest as infinity
  C->path_distance = 0;

  // Create UnvisitedQueue and insert
  UnvisitedQueue uq;
  uq.push(A, A->path_distance);
  uq.push(B, B->path_distance);
  uq.push(C, C->path_distance);
  uq.push(D, D->path_distance);
  uq.push(E, E->path_distance);
  uq.push(F, F->path_distance);

  // Make sure top returns the correct station
  EXPECT_EQ(uq.top_unprocessed(), C);

  // Now we should have A,B,D,E,F - all the same priority

  // Modify some of the priorities and reinsert, resulting in duplicates
  D->path_distance = 2;
  uq.push(D, D->path_distance);
  F->path_distance = 14;
  uq.push(F, F->path_distance);
  B->path_distance = 10;
  uq.push(B, B->path_distance);
  E->path_distance = 7;
  uq.push(E, E->path_distance);

  // Now we should have D-2, E-7, B-10, F-14, A-inf, along with duplicates

  // Make sure top returns the correct station, ignoring already processed stations
  EXPECT_EQ(uq.top_unprocessed(), D);
  EXPECT_EQ(uq.top_unprocessed(), E);
  EXPECT_EQ(uq.top_unprocessed(), B);
  EXPECT_EQ(uq.top_unprocessed(), F);
  EXPECT_EQ(uq.top_unprocessed(), A);

  // Any number of further calls should get dummy station
  EXPECT_EQ(uq.top_unprocessed()->name, "Dummy Station");
  EXPECT_EQ(uq.top_unprocessed()->name, "Dummy Station");

}
