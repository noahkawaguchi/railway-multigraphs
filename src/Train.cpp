#include "Train.h"

Train::Train(std::shared_ptr<Line> line) : line(line) {}

void Train::begin_day(bool facing_forward) {
  this->facing_forward = facing_forward;
  this->current_stop = facing_forward ? this->line->get_origin() : this->line->get_terminus();
}

void Train::depart() {

  // Turn around if at the end of the line
  // THIS ISN'T THE DESIRED BEHAVIOR FOR CIRCULAR
  if ((this->facing_forward && this->current_stop == this->line->get_terminus()) ||
      (!this->facing_forward && this->current_stop == this->line->get_origin()))
  {
    this->facing_forward = !this->facing_forward;
  }

  // Move to the next stop
  // THIS IS NOT IMPLEMENTED YET
  this->current_stop = this->line->get_next_stop(this->facing_forward, this->current_stop);
}
