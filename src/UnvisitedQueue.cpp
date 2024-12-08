#include "UnvisitedQueue.h"

std::shared_ptr<Station> UnvisitedQueue::QueueStation::dummy_station = std::make_shared<Station>("Dummy Station");

UnvisitedQueue::UnvisitedQueue() {}

void UnvisitedQueue::push(std::shared_ptr<Station> station) {
  QueueStation qs(station, station->get_path_distance());
  this->pq.push(qs);
}

bool UnvisitedQueue::empty() {
  // Pop any processed stations off the top
  while (!this->pq.empty() && this->processed.contains(this->pq.top().station)) {
    this->pq.pop();
  }
  // Now either the top element is unprocessed, or there are no elements at all
  if (this->pq.empty()) { return true; }
  else { return false; }
}

std::shared_ptr<Station> UnvisitedQueue::top_unprocessed() {
  // Clear processed stations off the top of the queue. Return the dummy station if this function 
  // has been mistakenly called on an empty queue or one with all processed stations.
  if (this->empty()) { return UnvisitedQueue::QueueStation::dummy_station; }

  // If the function did not return above, the top station must be unprocessed
  QueueStation qs = this->pq.top();
  this->pq.pop();

  // Mark the station as being processed now
  this->processed.insert(qs.station);

  return qs.station;
}
