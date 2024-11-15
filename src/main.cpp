#include "Train.h"
#include "Passenger.h"
#include "Station.h"
#include "Line.h"

#include <memory>

int main() {

  // 1. Create stations
  std::shared_ptr<Station> memoryland_city =
      std::make_shared<Station>(Station::BUSINESS);
  std::shared_ptr<Station> shopping_central =
      std::make_shared<Station>(Station::LEISURE);

  // 2. Create a line and add stations to line
  std::shared_ptr<Line> red_line = std::make_shared<Line>();
  red_line->print();
  red_line->add_station(memoryland_city);
  red_line->print();
  red_line->add_station(shopping_central);
  red_line->print();

  // 3. Create a train
  std::shared_ptr<Train> train001 = std::make_shared<Train>(red_line);
  train001->begin_day(true);

  return 0;
}
