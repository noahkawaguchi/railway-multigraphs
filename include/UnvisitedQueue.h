#ifndef UNVISITED_QUEUE_H
#define UNVISITED_QUEUE_H

#include <memory>
#include <queue>
#include <unordered_set>
#include <limits>

#include "Station.h"

// Dummy station to point to by default for safety
static std::shared_ptr<Station> dummy_station = std::make_shared<Station>("Dummy Station");

// Representation of stations specifically for use in the priority queue
struct QueueStation {
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


struct UnvisitedQueue {

  // Initialize a QueueStation and push it into internal priority queue
  void push(std::shared_ptr<Station> station) {
    QueueStation qs(station, station->get_path_minutes());
    this->pq.push(qs);
  }

  // Remove the top unprocessed element (the station with the minimum 
  // path minutes), mark it as processed, and return it
  std::shared_ptr<Station> top_unprocessed() {
    QueueStation qs;

    // Return dummy station if this function is mistakenly called on an empty queue
    if (this->empty()) { return qs.station; }

    do {
      qs = this->pq.top();
      this->pq.pop();
    } while (processed.find(qs.station) != processed.end());

    this->processed.insert(qs.station);

    return qs.station;
  }

  // Check if the queue is empty. "Empty" means it contains no unprocessed stations.
  bool empty() {
    // Pop any processed stations off the top
    while (!pq.empty() && processed.find(pq.top().station) != processed.end()) {
      pq.pop();
    }
    // Now either the top element is unprocessed, or there are no elements at all
    if (pq.empty()) { return true; }
    else { return false; }
  }

  std::priority_queue<QueueStation> pq;
  std::unordered_set<std::shared_ptr<Station>> processed;
};





#endif // UNVISITED_QUEUE_H