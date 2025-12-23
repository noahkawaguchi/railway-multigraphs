#ifndef UNVISITED_QUEUE_H
#define UNVISITED_QUEUE_H

#include <memory>
#include <queue>
#include <unordered_set>

#include "Stop.h"

class UnvisitedQueue {
public:
  UnvisitedQueue();
  ~UnvisitedQueue() = default;

  // Initialize a QueueStop and push it into the internal min-heap using the given priority
  void push(std::shared_ptr<Stop> stop, double priority);

  // Clear any processed stops off the top of the internal priority queue. If no
  // stops remain, return true. If an unprocessed stop remains, return false.
  bool empty();

  // Remove the top unprocessed stop, mark it as processed, and return it
  std::shared_ptr<Stop> top_unprocessed();

private:
  // Representation of stops specifically for use in the priority queue
  struct QueueStop {
    std::shared_ptr<Stop> stop;
    double priority;

    // 2-arg constructor to ensure data members are not left uninitialized
    QueueStop(std::shared_ptr<Stop> stop, double priority) : stop(stop), priority(priority) {}

    // Overload < operator for priority queue comparisons
    bool operator<(const QueueStop &other) const { return this->priority > other.priority; }
  };

  std::priority_queue<QueueStop> pq;
  std::unordered_set<std::shared_ptr<Stop>> processed;
};

#endif // UNVISITED_QUEUE_H
