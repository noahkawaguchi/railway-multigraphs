#include "../src/unvisited_queue.hpp"

#include <gtest/gtest.h>

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
  std::ignore = uq.top_unprocessed();

  // Remove both remaining processed stops
  std::ignore = uq.top_unprocessed();
  std::ignore = uq.top_unprocessed();

  // Now it should be empty again
  EXPECT_TRUE(uq.empty());
}

TEST(TestUQ, TopReinsertion) {
  // Create line and stops
  auto test_line = std::make_shared<Line>(Line{.name = "Test Line"});
  auto a = std::make_shared<Stop>("A", test_line);
  auto b = std::make_shared<Stop>("B", test_line);
  auto c = std::make_shared<Stop>("C", test_line);
  auto d = std::make_shared<Stop>("D", test_line);
  auto e = std::make_shared<Stop>("E", test_line);
  auto f = std::make_shared<Stop>("F", test_line);

  // Set priority of C, leave the rest as infinity
  c->path_distance = 0;

  // Create UnvisitedQueue and insert
  UnvisitedQueue uq;
  uq.push(a, a->path_distance);
  uq.push(b, b->path_distance);
  uq.push(c, c->path_distance);
  uq.push(d, d->path_distance);
  uq.push(e, e->path_distance);
  uq.push(f, f->path_distance);

  // Make sure top returns the correct stop
  EXPECT_EQ(uq.top_unprocessed(), c);

  // Now we should have A,B,D,E,F - all the same priority

  // Modify some of the priorities and reinsert, resulting in duplicates
  d->path_distance = 2;
  uq.push(d, d->path_distance);
  f->path_distance = 14;
  uq.push(f, f->path_distance);
  b->path_distance = 10;
  uq.push(b, b->path_distance);
  e->path_distance = 7;
  uq.push(e, e->path_distance);

  // Now we should have D-2, E-7, B-10, F-14, A-inf, along with duplicates

  // Make sure top returns the correct stop, ignoring already processed stops
  EXPECT_EQ(uq.top_unprocessed(), d);
  EXPECT_EQ(uq.top_unprocessed(), e);
  EXPECT_EQ(uq.top_unprocessed(), b);
  EXPECT_EQ(uq.top_unprocessed(), f);
  EXPECT_EQ(uq.top_unprocessed(), a);

  // Any number of further calls should get dummy stop
  EXPECT_EQ(uq.top_unprocessed()->get_id(), "Dummy Stop");
  EXPECT_EQ(uq.top_unprocessed()->get_id(), "Dummy Stop");
}
