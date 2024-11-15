#include "Passenger.h"

Passenger::Passenger(std::unique_ptr<Station> home_station, std::unique_ptr<Station> work_station)
    : home_station(std::move(home_station)), work_station(std::move(work_station))
{
  // TODO: Make these random priorities 
  this->cost_priority = 0.3f;
  this->time_priority = 0.3f;
  this->transfers_priority = 0.3f;
}





// // Testing random priorities

// #include <random>

// // TODO: 
// //   Should the three priorities add up to 1? 
// //   I'm taking too long on this step!
// std::random_device rd; // More random than std::rand()
// std::mt19937 gen(rd()); // Use rd to seed Mersenne Twister
// std::uniform_real_distribution<float> distribution(0.0f, 1.0f); // Map uniformly to desired range
// for (int i = 0; i < 3; i++) {
//   float priority = distribution(gen); // Generate float from distribution
//   std::cout << priority << std::endl;
// }

