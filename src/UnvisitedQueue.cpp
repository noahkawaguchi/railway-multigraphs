#include "UnvisitedQueue.h"

std::shared_ptr<Station> UnvisitedQueue::QueueStation::dummy_station = std::make_shared<Station>("Dummy Station");

UnvisitedQueue::UnvisitedQueue() {}

void UnvisitedQueue::push(std::shared_ptr<Station> station) {
  QueueStation qs(station, station->get_path_minutes());
  this->pq.push(qs);
}

std::shared_ptr<Station> UnvisitedQueue::top_unprocessed() {
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

bool UnvisitedQueue::empty() {
  // Pop any processed stations off the top
  while (!pq.empty() && processed.find(pq.top().station) != processed.end()) {
    pq.pop();
  }
  // Now either the top element is unprocessed, or there are no elements at all
  if (pq.empty()) { return true; }
  else { return false; }
}
