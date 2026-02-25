+++
title = "Assignment on Search Strategies"
date = 2026-02-25T16:44:32+05:45
tags = ["Travelling Salesman", "Nearest Neighbour", "2-Opt"]
math = true
description = "Assignment on Search Strategies"
+++


## Assignment

A traveling salesman has to travel through a bunch of cities, in such a way that the expenses on traveling
are minimized. This assignment is related to finding to the route that starts at city 0, then visits each other
city exactly once and then ends up in city 0 such that the total distance is minimised.

| Cities | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 |
|--------|----|----|----|----|----|----|----|----|----|----|----|----|
| 0      | 0  |    |    |    |    |    |    |    |    |    |    |    |
| 1      | A  | 0  |    |    |    |    |    |    |    |    |    |    |
| 2      | 10 | 23 | 0  |    |    |    |    |    |    |    |    |    |
| 3      | 12 | 45 | 34 | 0  |    |    |    |    |    |    |    |    |
| 4      | 5  | B  | 22 | 12 | 0  |    |    |    |    |    |    |    |
| 5      | 4  | 45 | 12 | 13 | 25 | 0  |    |    |    |    |    |    |
| 6      | 19 | 24 | C  | 26 | 21 | 11 | 0  |    |    |    |    |    |
| 7      | 14 | 9  | 23 | 43 | 5  | 22 | 20 | 0  |    |    |    |    |
| 8      | 3  | 34 | 22 | 33 | 7  | 12 | 33 | 6  | 0  |    |    |    |
| 9      | 18 | 12 | 21 | 21 | 22 | 10 | 11 | 23 | 17 | 0  |    |    |
| 12     | 20 | D  | 4  | 17 | 17 | 12 | 24 | 10 | 20 | 21 | 0  |    |
| 11     | 28 | 21 | 12 | 10 | 22 | 3  | 11 | 32 | 17 | E  | F  | 0  |


Notes
- Use A = (10 + 2 * your 3rd last digit in your student ID).
- Use B = (27 + your 2nd last student ID digit).
- Use C = (5 + 3 * your last student ID digit).
- Use D = (15 + your last student ID digit).
- Use E = (5 + 4 * your 2nd last student ID digit).
- Use F = (7 + 5 * your 3rd last student ID digit).

> [E.g. if your student ID is B00012345 use A = (10+ 2*3) = 16; B = (27+4) = 31, C = (5 + 3*5) = 20]
> D = (15+ 5) = 20; E = (5+4*4) = 21, F = (7 + 5*3) = 22].

Develop and analyse TSP routes using the following algorithms. Along with your model, you should also submit a brief 3-page
report answering the following tasks (maximum 3 pages including all diagrams).

1) Derive correct parameters for the TSP problem using your student numbers, describe the problem briefly and develop excel or another model.
2) Construct an initial route using the nearest neighbour (NN) algorithm as the construction algorithm. Show the path costs at each stage of
the solution development. Also show the constructed complete solution in a diagram.
3) With the initial route constructed in 2), demonstrate one hundred further iterations using an iterative improvement.
Discuss the improvement (if any) over the iterations.
4) Analyse the results obtained with a graph showing total distance of progressing solution found and best current solution against iterations
and also show the best solution as and a paragraph discussion.


## Deriving Parameters

We are given a adjacency matrix as the graph representation. The lower triangle in the given matrix is identical to upper triangle because 
each vertex is connected to all other vertices and the edges are bi-directional.

Since we are not assigned a student ID yet, lets generate a 10 digit student ID randomly. I will seed the random engine for reproducibility.
```cpp
uint64_t generateStudentID(size_t seed = 0b01110110101010111)
{
    static std::minstd_rand eng(seed);
    eng.discard(97);
    static std::uniform_int_distribution<uint64_t> dist(1'000'000'000, 9'999'999'999);
    static auto generator = std::bind(dist, eng);

    return generator();
}
```

Calling `generateStudentID` first time with default seed, we get student ID $d = 8624912239$. Lets number the digit position increasingly from right to left like
$d = d_{10}d_9d_8d_7d_6d_5d_4d_3d_2d_1$. This gives us:

$d_1 = 9$  
$d_2 = 3$  
$d_3 = 2$

$A = 10 + 2 * d_3 = 10 + 2 * 2 = 14 $  
$B = 27 + d_2     = 27 + 3     = 30 $  
$C = 5 + 3 * d_1  = 5 + 3 * 9  = 32 $  
$D = 15 + d_1     = 15 + 9     = 24 $  
$E = 5 + 4 * d_2  = 5 + 4 * 3  = 17 $  
$F = 7 + 5 * d_3  = 7 + 5 * 2  = 17 $  


Then our weighted graph becomes:

| Cities | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 |
|--------|----|----|----|----|----|----|----|----|----|----|----|----|
| 0      | 0  |    |    |    |    |    |    |    |    |    |    |    |
| 1      | 14 | 0  |    |    |    |    |    |    |    |    |    |    |
| 2      | 10 | 23 | 0  |    |    |    |    |    |    |    |    |    |
| 3      | 12 | 45 | 34 | 0  |    |    |    |    |    |    |    |    |
| 4      | 5  | 30 | 22 | 12 | 0  |    |    |    |    |    |    |    |
| 5      | 4  | 45 | 12 | 13 | 25 | 0  |    |    |    |    |    |    |
| 6      | 19 | 24 | 32 | 26 | 21 | 11 | 0  |    |    |    |    |    |
| 7      | 14 | 9  | 23 | 43 | 5  | 22 | 20 | 0  |    |    |    |    |
| 8      | 3  | 34 | 22 | 33 | 7  | 12 | 33 | 6  | 0  |    |    |    |
| 9      | 18 | 12 | 21 | 21 | 22 | 10 | 11 | 23 | 17 | 0  |    |    |
| 12     | 20 | 24 | 4  | 17 | 17 | 12 | 24 | 10 | 20 | 21 | 0  |    |
| 11     | 28 | 21 | 12 | 10 | 22 | 3  | 11 | 32 | 17 | 17 | 17 | 0  |

## Nearest Neighbour Algorithm

Greedy things are simple and so is nearest neighbour algorithm. It simply looks for the edge with smallest weight going out from current vertex and chooses that edge.
The caveat is that if the edge leads to a vertex (city) already visited, we are not allowed to take that edge (path) since we are working the travelling
salesman problem hence allowed to visit a city only once.

```cpp
std::vector<int> nearestNeighbour()
{
    std::vector<int> route;
    std::vector<bool> visited(N, false);

    int current = 0;
    route.push_back(current);
    visited[current] = true;

    int runningTotal = 0;
    for (int step = 1; step < N; ++step) {
        int nearest = -1;
        int minDist = std::numeric_limits<int>::max();

        // find nearest unvisited city
        for (int j = 0; j < N; ++j) {
            if (!visited[j] && graph[current][j] < minDist) {
                minDist = graph[current][j];
                nearest = j;
            }
        }

        runningTotal += minDist;

        visited[nearest] = true;
        route.push_back(nearest);
        current = nearest;
    }

    // return to starting city
    int returnCost = graph[current][0];
    runningTotal += returnCost;
    route.push_back(0); // close the loop

    return route;
}
```

Path chosen by the nearest neighbour algorithm is: 0 → 8 → 7 → 4 → 3 → 11 → 5 → 9 → 6 → 1 → 2 → 10 → 0.  
Total Cost = $131$.

## 2-Opt Heuristic Algorithm

Gist of this algorithm is to pick any two edges in the tour, remove them, and reconnect the cities in the only other way possible.
If the new tour is shorter, keep it. Repeat.

{{< callout type="tip" title="Key things to understand" >}}
- A 2-opt swap always reverses a segment of the route between the two chosen edges.
- Try every possible pair of edges in one iteration.
- If any swap improves the distance, update the route and keep going.
{{< /callout >}}

```cpp
// Reverses the segment in range [i + 1, j]
std::vector<int> twoOptSwap(std::vector<int> const& route, int i, int j)
{
    std::vector<int> result(route);
    std::reverse(result.begin() + i + 1, result.begin() + j + 1);
    return result;
}

void twoOpt(std::vector<int>& route, size_t maxIterations)
{
    int bestDistance = computePathCost(route);

    for (int iter = 1; iter <= maxIterations; ++iter) {
        bool improved = false;
        
        // try every pair of edges
        for (int i = 0; i < route.size() - 2; ++i) {
            for (int j = i + 2; j < route.size() - 1; ++j) {

                std::vector<int> newRoute = twoOptSwap(route, i, j);
                int distance = computePathCost(newRoute);

                if (distance < bestDistance) {
                    route = std::move(newRoute);
                    bestDistance = distance;
                    improved = true;
                }
            }
        }

        if (!improved)
            break;
    }
}
```

## Analysis

|       | route | distance                                            |
|-------|-------|-----------------------------------------------------|
| NN    | 131   | 0 → 8 → 7 → 4 → 3 → 11 → 5 → 9 → 6 → 1 → 2 → 10 → 0 |
| 2-Opt | 110   | 0 → 8 → 7 → 10 → 2 → 1 → 9 → 6 → 5 → 11 → 3 → 4 → 0 |

The nearest neighbour algorithm gave the total distance of 131.
Upon further improvement using the 2-opt algorithm, after just 2nd iteration the algorithm converges on
total distance of 110.

The 2-opt algorithm converged very quickly because:

- nearest neighbour already gives a fairly compact route for this dataset
- there are no major crossing edges left after the first improvements
- graph is relatively structured (not random), so local optimum is reached fast.


**Output of Program:**

{{< callout type="tip" title="Source Code File" >}}
[View full Source Code](SearchStrategies.cpp)
{{< /callout >}}

{{< fig src="program-output.png" alt="Output generated by running the program" class="fig--full">}}

