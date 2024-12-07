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

  // Initialize a QueueStation and push it into the internal priority queue
  void push(std::shared_ptr<Station> station);

  // Remove the top unprocessed element (the station with the minimum 
  // path minutes), mark it as processed, and return it
  std::shared_ptr<Station> top_unprocessed();

  // Check if the UnvisitedQueue is empty. "Empty" means it contains no unprocessed stations.
  bool empty();

private:
  // Representation of stations specifically for use in the priority queue
  struct QueueStation {
    // Dummy station for all instances of QueueStation to point to by default for safety
    static std::shared_ptr<Station> dummy_station;

    std::shared_ptr<Station> station = dummy_station;
    int minutes = std::numeric_limits<int>::max() / 2; // "Infinity"

    QueueStation() {}
    QueueStation(std::shared_ptr<Station> station, int minutes)
                : station(station), minutes(minutes) {}
    
    // Overload < operator for priority queue comparisons
    bool operator<(const QueueStation& other) const {
      return this->minutes > other.minutes;
    }
  };

  std::priority_queue<QueueStation> pq;
  std::unordered_set<std::shared_ptr<Station>> processed;

};


#endif // UNVISITED_QUEUE_H