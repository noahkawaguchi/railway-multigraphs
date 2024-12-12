# Railway Multigraphs

### ⏯️ [Walkthrough Video Here](https://drive.google.com/file/d/1qoTRlBQVEEgGOc9ejq7KGE4S4ALFrXVR/view?usp=sharing)

### Data Structure: Multigraph

A multigraph is a graph that can have parallel edges, or in other words, multiple edges that connect the same two nodes. Doing the graph assignment in class, I liked how versatile it seemed, and it reminded me of passenger rail networks. These are the main abstract considerations I had:

- Parallel edges (use a multigraph instead of a graph): Different rail lines can connect the same two stations.
- All weighted edges: The distance traversed between stations is fundamental to creating an itinerary.
- All undirected edges: While I'm sure single-direction railways exist somewhere, the ones I have in mind always have service in both directions.
- No self-loops: It wouldn't make sense to leave and come back to the same station.
- Cyclic: There can be circle routes or other cycles achievable through transfers.

### Algorithm: Dijkstra's Shortest Path

Dijkstra's shortest path finds the shortest path from a starting node to all other nodes, or to a specific destination node, as I implement here. In other words, considering the weights of the edges, it finds which path would result in the minimum sum of edge weights. I have both a distance version, where each edge has a fixed weight, and a cost version, where the weight of the edge depends on the fare structure of the rail line and transfers between them.

### Running the Project

Please see the walkthrough video for a more detailed explanation of the project and a recording of me running it myself locally. However, if you want to try to run it as well, this is what works for me. The project requires C++20.

```zsh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug # Or just `cmake ..` for no debugging
make
./railway_multigraphs # To print some of the toy data results
ctest --verbose # To see the tests pass for more cases than are printed
```

### Toy Data Example 

I made this visualization using [graphonline.top](https://graphonline.top). The other toy data images can be found in the `toy_data_viz` folder along with `.graphml` files that can be opened and edited on the website.

![multigraph_city](./toy_data_viz/real_multigraph_city.png)

### Terminal Output

Here is the terminal output I show in the video when I run ./railway_multigraphs

```

--------------------

Seaport Station connections:
  7 mi to South Station

South Station connections:
  4.4 mi to North Station
  7 mi to Seaport Station

North Station connections:
  3.5 mi to Airport Station
  4.4 mi to South Station

Airport Station connections:
  3.5 mi to North Station

North Station connections:
  5.2 mi to City Center Station
  3.1 mi to South Station

South Station connections:
  4.2 mi to City Center Station
  3.1 mi to North Station

City Center Station connections:
  5.2 mi to North Station
  4.2 mi to South Station

Residential West Station connections:
  4.3 mi to Commercial Center Station

Commercial Center Station connections:
  2.7 mi to Residential East Station
  4.3 mi to Residential West Station

Residential East Station connections:
  2.2 mi to City Center Station
  2.7 mi to Commercial Center Station

City Center Station connections:
  6.2 mi to South Station
  2.2 mi to Residential East Station

South Station connections:
  6.2 mi to City Center Station

Residential West Station connections:
  4.3 mi to Commercial Center Station

Commercial Center Station connections:
  3.9 mi to City Center Station
  4.3 mi to Residential West Station

City Center Station connections:
  7.5 mi to North Station
  3.9 mi to Commercial Center Station

North Station connections:
  7.5 mi to City Center Station

--------------------


--------------------

Here is your route from Seaport Station to City Center Station:

  Start: Seaport Station
  -> Go to South Station via the Main Line
  -> Go to City Center Station via the Underground Loop

  Total distance: 11.2 mi
  Total cost: $6.47

--------------------


--------------------

Here is your route from Seaport Station to City Center Station:

  Start: Seaport Station
  -> Go to South Station via the Main Line
  -> Go to City Center Station via the Commuter Local

  Total distance: 13.2 mi
  Total cost: $5.74

--------------------


--------------------

Here is your route from South Station to Airport Station:

  Start: South Station
  -> Go to North Station via the Underground Loop
  -> Go to Airport Station via the Main Line

  Total distance: 6.6 mi
  Total cost: $5.22

--------------------


--------------------

Here is your route from South Station to Airport Station:

  Start: South Station
  -> Go to North Station via the Main Line
  -> Go to Airport Station via the Main Line

  Total distance: 7.9 mi
  Total cost: $3.48

--------------------


--------------------

Here is your route from Residential West Station to North Station:

  Start: Residential West Station
  -> Go to Commercial Center Station via the Commuter Special
  -> Go to City Center Station via the Commuter Special
  -> Go to North Station via the Underground Loop

  Total distance: 13.4 mi
  Total cost: $8.03

--------------------


--------------------

Here is your route from Residential West Station to North Station:

  Start: Residential West Station
  -> Go to Commercial Center Station via the Commuter Local
  -> Go to Residential East Station via the Commuter Local
  -> Go to City Center Station via the Commuter Local
  -> Go to North Station via the Underground Loop

  Total distance: 14.4 mi
  Total cost: $6.66

--------------------

```