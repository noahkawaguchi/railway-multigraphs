#ifndef UNVISITED_QUEUE_H
#define UNVISITED_QUEUE_H

#include <memory>
#include <queue>
#include <unordered_set>
#include <limits>

#include "Station.h"

// Dummy station to point to by default for safety
static std::shared_ptr<Station> dummy_station = std::make_shared<Station>("No Predecessor");

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

  // Initialize a QueueStation and push into internal priority queue
  void push(std::shared_ptr<Station> station) {
    QueueStation qs(station, station->get_path_minutes());
    this->pq.push(qs);
  }

  // Remove the top unprocessed element (the station with the minimum 
  // path minutes), mark it as processed, and return it
  std::shared_ptr<Station> top_unprocessed() {
    QueueStation qs;
    do {
      qs = this->pq.top();
      this->pq.pop();
    } while (processed.find(qs.station) != processed.end());

    this->processed.insert(qs.station);

    return qs.station;
  }

  std::priority_queue<QueueStation> pq;
  std::unordered_set<std::shared_ptr<Station>> processed;
};





#endif // UNVISITED_QUEUE_H