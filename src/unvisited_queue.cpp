#include "unvisited_queue.hpp"

#include <utility>

void UnvisitedQueue::push(std::shared_ptr<Stop> stop, double priority) {
  this->pq.emplace(std::move(stop), priority);
}

auto UnvisitedQueue::empty() -> bool {
  // Pop any processed stops off the top
  while (!this->pq.empty() && this->processed.contains(this->pq.top().stop)) { this->pq.pop(); }
  // Now either the top stop is unprocessed, or there are none at all
  return this->pq.empty();
}

auto UnvisitedQueue::top_unprocessed() -> std::shared_ptr<Stop> {
  // Clear processed stops off the top of the queue. Return a dummy stop if this function
  // has been mistakenly called on an empty queue or one with all processed stops.
  if (this->empty()) { return std::make_shared<Stop>("Dummy Stop", nullptr); }

  // If the function did not return above, the top stop must be unprocessed
  const QueueStop qs{this->pq.top()};
  this->pq.pop();

  // Mark the stop as being processed now
  this->processed.insert(qs.stop);

  return qs.stop;
}
