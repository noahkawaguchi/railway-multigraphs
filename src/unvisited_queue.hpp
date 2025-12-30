#pragma once

#include <memory>
#include <queue>
#include <unordered_set>
#include <utility>

#include "stop.hpp"

class UnvisitedQueue {
public:
  // Initialize a QueueStop and push it into the internal min-heap using the given priority
  void push(std::shared_ptr<Stop> stop, double priority);

  // Clear any processed stops off the top of the internal priority queue. If no
  // stops remain, return true. If an unprocessed stop remains, return false.
  auto empty() -> bool;

  // Remove the top unprocessed stop, mark it as processed, and return it
  auto top_unprocessed() -> std::shared_ptr<Stop>;

private:
  // Representation of stops specifically for use in the priority queue
  struct QueueStop {
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes,
    // cppcoreguidelines-non-private-member-variables-in-classes)

    std::shared_ptr<Stop> stop;
    double priority;

    // NOLINTEND(misc-non-private-member-variables-in-classes,
    // cppcoreguidelines-non-private-member-variables-in-classes)

    // 2-arg constructor to ensure data members are not left uninitialized
    QueueStop(std::shared_ptr<Stop> stop, double priority)
        : stop(std::move(stop)), priority(priority) {}

    // Overload < operator for priority queue comparisons
    auto operator<(const QueueStop &other) const -> bool { return this->priority > other.priority; }
  };

  std::priority_queue<QueueStop> pq;
  std::unordered_set<std::shared_ptr<Stop>> processed;
};
