#ifndef UNVISITED_QUEUE_H
#define UNVISITED_QUEUE_H

#include <memory>
#include <queue>
#include <unordered_set>
#include <limits>

#include "Station.h"


class UnvisitedQueue {
public:
  UnvisitedQueue();
  ~UnvisitedQueue() = default;

  // Initialize a QueueStation and push it into the internal min-heap using the given priority
  void push(std::shared_ptr<Station> station, float priority);

  // Clear any processed stations off the top of the internal priority queue. If no 
  // stations remain, return true. If an unprocessed station remains, return false.
  bool empty();

  // Remove the top unprocessed station, mark it as processed, and return it
  std::shared_ptr<Station> top_unprocessed();

private:
  // Representation of stations specifically for use in the priority queue
  struct QueueStation {
    std::shared_ptr<Station> station;
    float priority;

    // 2-arg constructor to ensure data members are not left uninitialized
    QueueStation(std::shared_ptr<Station> station, float priority)
                 : station(station), priority(priority) {}

    // Overload < operator for priority queue comparisons
    bool operator<(const QueueStation& other) const {
      return this->priority > other.priority;
    }
  };

  std::priority_queue<QueueStation> pq;
  std::unordered_set<std::shared_ptr<Station>> processed;

};


#endif // UNVISITED_QUEUE_H