#include <gtest/gtest.h>

#include "../include/UnvisitedQueue.h"

TEST(TestUQ, Top) {
  // Create stations 
  std::shared_ptr<Station> station1 = std::make_shared<Station>("Station 1");
  std::shared_ptr<Station> station2 = std::make_shared<Station>("Station 2");
  std::shared_ptr<Station> station3 = std::make_shared<Station>("Station 3");
  std::shared_ptr<Station> station4 = std::make_shared<Station>("Station 4");

  // Set priorities
  station1->set_path_distance(5);
  station2->set_path_distance(10);
  // (leave Station 3 as default)
  station4->set_path_distance(2);

  // Create UnvisitedQueue and insert
  UnvisitedQueue uq;
  uq.push(station1);
  uq.push(station2);
  uq.push(station3);
  uq.push(station4);

  // Make sure top returns the correct station
  ASSERT_EQ(uq.top_unprocessed(), station4);
  ASSERT_EQ(uq.top_unprocessed(), station1);
  ASSERT_EQ(uq.top_unprocessed(), station2);
  ASSERT_EQ(uq.top_unprocessed(), station3);

}

TEST(TestUQ, Empty) {
  // Create UnvisitedQueue, which should start empty
  UnvisitedQueue uq;
  ASSERT_EQ(uq.empty(), true);

  // Create stations 
  std::shared_ptr<Station> station1 = std::make_shared<Station>("Station 1");
  std::shared_ptr<Station> station2 = std::make_shared<Station>("Station 2");
  std::shared_ptr<Station> station3 = std::make_shared<Station>("Station 3");

  // Set priorities
  station1->set_path_distance(7);
  station2->set_path_distance(3);
  // (leave Station 3 as default)

  // Insert into queue
  uq.push(station1);
  uq.push(station2);
  uq.push(station3);

  // Now the queue should not be empty
  ASSERT_EQ(uq.empty(), false);

  // Update priority, reinsert, and process, leaving a processed duplicate in the queue
  station3->set_path_distance(2);
  uq.push(station3);
  uq.top_unprocessed();

  // Remove both remaining processed stations
  uq.top_unprocessed();
  uq.top_unprocessed();

  // Now it should be empty again
  ASSERT_EQ(uq.empty(), true);
}

TEST(TestUQ, TopReinsertion) {
  // Create stations 
  std::shared_ptr<Station> A = std::make_shared<Station>("A");
  std::shared_ptr<Station> B = std::make_shared<Station>("B");
  std::shared_ptr<Station> C = std::make_shared<Station>("C");
  std::shared_ptr<Station> D = std::make_shared<Station>("D");
  std::shared_ptr<Station> E = std::make_shared<Station>("E");
  std::shared_ptr<Station> F = std::make_shared<Station>("F");

  // Set priority of C, leave the rest as infinity
  C->set_path_distance(0);

  // Create UnvisitedQueue and insert
  UnvisitedQueue uq;
  uq.push(A);
  uq.push(B);
  uq.push(C);
  uq.push(D);
  uq.push(E);
  uq.push(F);

  // Make sure top returns the correct station
  ASSERT_EQ(uq.top_unprocessed(), C);

  // Now we should have A,B,D,E,F - all the same priority

  // Modify some of the priorities and reinsert, resulting in duplicates
  D->set_path_distance(2);
  uq.push(D);
  F->set_path_distance(14);
  uq.push(F);
  B->set_path_distance(10);
  uq.push(B);
  E->set_path_distance(7);
  uq.push(E);

  // Now we should have D-2, E-7, B-10, F-14, A-inf, along with duplicates

  // Make sure top returns the correct station, ignoring already processed stations
  ASSERT_EQ(uq.top_unprocessed(), D);
  ASSERT_EQ(uq.top_unprocessed(), E);
  ASSERT_EQ(uq.top_unprocessed(), B);
  ASSERT_EQ(uq.top_unprocessed(), F);
  ASSERT_EQ(uq.top_unprocessed(), A);

  // Any number of further calls should get dummy station
  ASSERT_EQ(uq.top_unprocessed()->get_name(), "Dummy Station");
  ASSERT_EQ(uq.top_unprocessed()->get_name(), "Dummy Station");

}
