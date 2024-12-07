#include <gtest/gtest.h>

#include "../include/Network.h"

TEST(BasicDSP, ToyDataABCD) {
  // Make network
  std::unique_ptr<Network> ABCD = std::make_unique<Network>();

  // Add stations to network
  std::shared_ptr<Station> stationA = ABCD->new_station("Station A");
  std::shared_ptr<Station> stationB = ABCD->new_station("Station B");
  std::shared_ptr<Station> stationC = ABCD->new_station("Station C");
  std::shared_ptr<Station> stationD = ABCD->new_station("Station D");

  // Connect stations with tracks
  ABCD->new_track(stationA, stationB, 3);
  ABCD->new_track(stationA, stationC, 7);
  ABCD->new_track(stationB, stationC, 5);
  ABCD->new_track(stationB, stationD, 1);
  ABCD->new_track(stationC, stationD, 2);

  // Find the shortest path from A to C
  std::shared_ptr<Route> AC_route = ABCD->basic_DSP(stationA, stationC);
  std::vector<std::shared_ptr<Station>> correct_path_AC = {stationA, stationB, stationD, stationC};
  ASSERT_EQ(AC_route->stations, correct_path_AC);

  // Find the shortest path from D to A
  std::shared_ptr<Route> DA_route = ABCD->basic_DSP(stationD, stationA);
  std::vector<std::shared_ptr<Station>> correct_path_DA = {stationD, stationB, stationA};
  ASSERT_EQ(DA_route->stations, correct_path_DA);

}

TEST(BasicDSP, ToyDataTinyCity) {
  // Make network
  std::unique_ptr<Network> tiny_city = std::make_unique<Network>();

  // Add stations to network
  std::shared_ptr<Station> hospital = tiny_city->new_station("Hospital");
  std::shared_ptr<Station> airport = tiny_city->new_station("Airport");
  std::shared_ptr<Station> west_residential = tiny_city->new_station("West Residential");
  std::shared_ptr<Station> city_hall = tiny_city->new_station("City Hall");
  std::shared_ptr<Station> east_residential = tiny_city->new_station("East Residential");
  std::shared_ptr<Station> park = tiny_city->new_station("Park");
  std::shared_ptr<Station> mall = tiny_city->new_station("Mall");
  std::shared_ptr<Station> seaport = tiny_city->new_station("Seaport");

  // Connect stations with tracks
  tiny_city->new_track(hospital, west_residential, 2);
  tiny_city->new_track(hospital, city_hall, 3);
  tiny_city->new_track(airport, city_hall, 10);
  tiny_city->new_track(airport, east_residential, 7);
  tiny_city->new_track(west_residential, city_hall, 7);
  tiny_city->new_track(west_residential, park, 1);
  tiny_city->new_track(city_hall, mall, 2);
  tiny_city->new_track(east_residential, seaport, 8);
  tiny_city->new_track(park, mall, 7);
  tiny_city->new_track(mall, seaport, 8);

  // Find the shortest path from the park to the airport
  std::shared_ptr<Route> park_airport_route = tiny_city->basic_DSP(park, airport);
  std::vector<std::shared_ptr<Station>> correct_path_park_airport = {
    park, west_residential, hospital, city_hall, airport
  };
  ASSERT_EQ(park_airport_route->stations, correct_path_park_airport);

  // Find the shortest path from East Residential to West Residential
  std::shared_ptr<Route> east_west_route = tiny_city->basic_DSP(east_residential, west_residential);
  std::vector<std::shared_ptr<Station>> correct_path_east_west = {
    east_residential, airport, city_hall, hospital, west_residential
  };

  for (const auto& station : east_west_route->stations) {
    std::cout << station->get_name() << std::endl;
  }

  std::cout << std::endl;

  for (const auto& station : correct_path_east_west) {
    std::cout << station->get_name() << std::endl;
  }

  ASSERT_EQ(east_west_route->stations, correct_path_east_west);

}
