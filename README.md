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

---

### Toy Data Example 

I made this visualization using [graphonline.top](https://graphonline.top). The other toy data images can be found in the `toy_data_viz` folder along with `.graphml` files that can be opened and edited on the website.

![multigraph_city](./toy_data_viz/real_multigraph_city.png)
