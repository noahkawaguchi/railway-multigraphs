#pragma once

#include <cmath>
#include <memory>
#include <utility>

#include "stop.hpp"

struct Track {
  // NOLINTBEGIN(misc-non-private-member-variables-in-classes,
  // cppcoreguidelines-non-private-member-variables-in-classes)

  std::shared_ptr<Stop> other_stop;

  // NOLINTEND(misc-non-private-member-variables-in-classes,
  // cppcoreguidelines-non-private-member-variables-in-classes)

  Track(std::shared_ptr<Stop> other_stop, double distance)
      : other_stop(std::move(other_stop)), distance(distance) {}

  [[nodiscard]] auto get_distance() const -> double { return this->distance; }

  /// Calculate the cost to go to the other stop, rounded to cents.
  [[nodiscard]] auto get_cost_from(const std::shared_ptr<Stop> &current_stop) -> double {
    double total_cost{0.0};
    // Regular cost to take this section of track
    total_cost += std::round(this->distance * this->other_stop->line->cost_per_mile * 100) / 100;
    // Additional cost to begin a new trip or transfer to a different line
    if (current_stop->get_path_cost() == 0.0 || this->other_stop->line != current_stop->line) {
      total_cost += this->other_stop->line->base_cost;
    }
    return total_cost;
  }

private:
  double distance; ///< The distance to the other stop (in miles).
};
