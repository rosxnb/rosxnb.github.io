// compile with c++23
// clang++ -std=c++23 SearchStartegies.cpp

#include <print>
#include <random>
#include <functional>
#include <array>
#include <vector>
#include <algorithm>


// Generates a number with 10 random digits
uint64_t generateStudentID(size_t seed = 0b01110110101010111)
{
    static std::minstd_rand eng(seed);
    eng.discard(97);
    static std::uniform_int_distribution<uint64_t> dist(1'000'000'000, 9'999'999'999);
    static auto generator = std::bind(dist, eng);

    return generator();
}

// studentID used = 8624912239
constexpr int N = 12;
std::array<std::array<int, N>, N> graph {{
    { 0, 14, 10, 12,  5,  4, 19, 14,  3, 18, 20, 28},
    {14,  0, 23, 45, 30, 45, 24,  9, 34, 12, 24, 21},
    {10, 23,  0, 34, 22, 12, 32, 23, 22, 21,  4, 12},
    {12, 45, 34,  0, 12, 13, 26, 43, 33, 21, 17, 10},
    { 5, 30, 22, 12,  0, 25, 21,  5,  7, 22, 17, 22},
    { 4, 45, 12, 13, 25,  0, 11, 22, 12, 10, 12,  3},
    {19, 24, 32, 26, 21, 11,  0, 20, 33, 11, 24, 11},
    {14,  9, 23, 43,  5, 22, 20,  0,  6, 23, 10, 32},
    { 3, 34, 22, 33,  7, 12, 33,  6,  0, 17, 20, 17},
    {18, 12, 21, 21, 22, 10, 11, 23, 17,  0, 21, 17},
    {20, 24,  4, 17, 17, 12, 24, 10, 20, 21,  0, 17},
    {28, 21, 12, 10, 22,  3, 11, 32, 17, 17, 17,  0} 
}};

template<size_t N>
void printGraph(std::array<std::array<int, N>, N> const& graph, std::vector<int> const& edges = {})
{
    std::print("\n    ");
    for (size_t i = 0; i < N; ++i) {
        std::print("{:4}", i);
    }
    std::println();
    
    std::print("   +");
    for (size_t i = 0; i < N; ++i) {
        std::print("----");
    }
    std::println();
    
    for (size_t i = 0; i < N; ++i) {
        std::print("{:2} |", i);
        
        for (size_t j = 0; j < N; ++j) {
            if (!edges.empty() && edges[i] == j) {
                std::print("\033[32m{:4}\033[0m", graph[i][j]);
            } else {
                std::print("{:4}", graph[i][j]);
            }
        }
        std::println();
    }
    std::println();
}

std::vector<int> nearestNeighbour()
{
    std::println("\n--- Nearest Neighbour Construction ---");
    std::println("{:<6} {:<15} {:<20} {:<12} {}", 
                 "Step", "Current City", "Next City (Nearest)", "Edge Cost", "Running Total");
    std::println("{:-<70}", "");

    std::vector<bool> visited(N, false);
    std::vector<int> route;

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
        std::println("{:^6} {:^15} {:^20} {:^12} {}",
                     step, current, nearest, minDist, runningTotal);

        visited[nearest] = true;
        route.push_back(nearest);
        current = nearest;
    }

    // return to starting city
    int returnCost = graph[current][0];
    runningTotal += returnCost;
    route.push_back(0); // close the loop

    std::println("{:^6} {:^15} {:^20} {:^12} {}",
                 N, current, 0, returnCost, runningTotal);

    return route;
}

int computePathCost(std::vector<int> const& route)
{
    int cost = 0;
    for (auto i = 0; i < route.size() - 1; ++i) {
        cost += graph[route[i]][route[i + 1]];
    }
    return cost;
}

std::vector<int> generateEdgeList(std::vector<int> const& route)
{
    std::vector<int> edges(route.size() - 1);
    for (auto i = 0; i < route.size() - 1; ++i) {
        edges[route[i]] = route[i + 1];
    }
    return edges;
}

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

    std::println("\n--- 2-opt Iterative Improvement ---");
    std::println("{:<12} {:<20} {}", "Iteration", "Current Distance", "Best Distance");
    std::println("{:-<45}", "");
    std::println("{:<12} {:<20} {}", 0, bestDistance, bestDistance);

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

        std::println("{:<12} {:<20} {}", iter, computePathCost(route), bestDistance);

        if (!improved)
            break;
    }
}

int main()
{
    printGraph(graph);
    std::println("Randomly Generated Student ID: {}", generateStudentID());

    std::println("\n{:-<3} NN Solution {:-<3}", "", "");
    auto route = nearestNeighbour();

    std::println("\nTotal Distance: {}", computePathCost(route));
    std::print("Route: ");
    for (size_t i = 0; i < route.size(); ++i) {
        std::print("{}{}", route[i], (i < route.size() - 1) ? " -> " : "");
    }
    std::println();

    std::vector<int> edges = generateEdgeList(route);
    printGraph(graph, edges);

    std::println("\n{:-<3} Best Solution After 2-opt {:-<3}", "", "");
    twoOpt(route, 100);

    std::println("\nTotal Distance: {}", computePathCost(route));
    std::print("Route: ");
    for (size_t i = 0; i < route.size(); ++i) {
        std::print("{}{}", route[i], (i < route.size() - 1) ? " -> " : "");
    }
    std::println();

    edges = generateEdgeList(route);
    printGraph(graph, edges);

    return 0;
}
