#include <gtest/gtest.h>

#include "../src/unvisited_queue.hpp"

TEST(TestUQ, Top) {
  // Create line and stops
  auto test_line = std::make_shared<Line>(Line{.name = "Test Line"});
  auto stop1 = std::make_shared<Stop>("Stop 1", test_line);
  auto stop2 = std::make_shared<Stop>("Stop 2", test_line);
  auto stop3 = std::make_shared<Stop>("Stop 3", test_line);
  auto stop4 = std::make_shared<Stop>("Stop 4", test_line);

  // Set priorities
  stop1->path_distance = 5;
  stop2->path_distance = 10;
  // (leave Stop 3 as default)
  stop4->path_distance = 2;

  // Create UnvisitedQueue and insert
  UnvisitedQueue uq;
  uq.push(stop1, stop1->path_distance);
  uq.push(stop2, stop2->path_distance);
  uq.push(stop3, stop3->path_distance);
  uq.push(stop4, stop4->path_distance);

  // Make sure top returns the correct stop
  EXPECT_EQ(uq.top_unprocessed(), stop4);
  EXPECT_EQ(uq.top_unprocessed(), stop1);
  EXPECT_EQ(uq.top_unprocessed(), stop2);
  EXPECT_EQ(uq.top_unprocessed(), stop3);
}

TEST(TestUQ, Empty) {
  // Create UnvisitedQueue, which should start empty
  UnvisitedQueue uq;
  EXPECT_TRUE(uq.empty());

  // Create line and stops
  auto test_line = std::make_shared<Line>(Line{.name = "Test Line"});
  auto stop1 = std::make_shared<Stop>("Stop 1", test_line);
  auto stop2 = std::make_shared<Stop>("Stop 2", test_line);
  auto stop3 = std::make_shared<Stop>("Stop 3", test_line);

  // Set priorities
  stop1->path_distance = 7;
  stop2->path_distance = 3;
  // (leave Stop 3 as default)

  // Insert into queue
  uq.push(stop1, stop1->path_distance);
  uq.push(stop2, stop2->path_distance);
  uq.push(stop3, stop3->path_distance);

  // Now the queue should not be empty
  EXPECT_FALSE(uq.empty());

  // Update priority, reinsert, and process, leaving a processed duplicate in the queue
  stop3->path_distance = 2;
  uq.push(stop3, stop3->path_distance);
  uq.top_unprocessed();

  // Remove both remaining processed stops
  uq.top_unprocessed();
  uq.top_unprocessed();

  // Now it should be empty again
  EXPECT_TRUE(uq.empty());
}

TEST(TestUQ, TopReinsertion) {
  // Create line and stops
  auto test_line = std::make_shared<Line>(Line{.name = "Test Line"});
  auto A = std::make_shared<Stop>("A", test_line);
  auto B = std::make_shared<Stop>("B", test_line);
  auto C = std::make_shared<Stop>("C", test_line);
  auto D = std::make_shared<Stop>("D", test_line);
  auto E = std::make_shared<Stop>("E", test_line);
  auto F = std::make_shared<Stop>("F", test_line);

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

  // Make sure top returns the correct stop
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

  // Make sure top returns the correct stop, ignoring already processed stops
  EXPECT_EQ(uq.top_unprocessed(), D);
  EXPECT_EQ(uq.top_unprocessed(), E);
  EXPECT_EQ(uq.top_unprocessed(), B);
  EXPECT_EQ(uq.top_unprocessed(), F);
  EXPECT_EQ(uq.top_unprocessed(), A);

  // Any number of further calls should get dummy stop
  EXPECT_EQ(uq.top_unprocessed()->id, "Dummy Stop");
  EXPECT_EQ(uq.top_unprocessed()->id, "Dummy Stop");
}
