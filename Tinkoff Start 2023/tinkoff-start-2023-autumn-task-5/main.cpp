#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <valarray>
#include <limits>

using std::cin;
using std::cout;
using std::vector;
using std::priority_queue;
using std::unordered_set;
using std::set;
using std::abs;
using std::min;
using std::endl;
using std::numeric_limits;

struct Edge {
    int to;
    int weight;

    Edge(int to, int weight) : to(to), weight(weight) {}

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int getMinMaxWeight(vector<priority_queue<Edge>>& edges, unordered_set<int>& visited, unordered_set<int>& unvisited) {
    int minMaxWeight = numeric_limits<int>::max();

    while (!unvisited.empty())
    {
        Edge maxWeightEdge(0, 0);

        for (int from : visited)
        {
            while (!edges[from].empty() && visited.count(edges[from].top().to))
                edges[from].pop();

            if (!edges[from].empty() && edges[from].top().weight > maxWeightEdge.weight)
            {
                maxWeightEdge = edges[from].top();
                edges[from].pop();
            }
        }

        if (maxWeightEdge.weight < minMaxWeight)
            minMaxWeight = maxWeightEdge.weight;

        unvisited.erase(maxWeightEdge.to);
        visited.insert(maxWeightEdge.to);
    }

    return minMaxWeight;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<priority_queue<Edge>> edges(n);
    vector<vector<bool>> adj(n, vector<bool>(n, false));

    for (int i = 0, v, u, w; i < m; i++)
    {
        cin >> v >> u >> w;
        edges[v - 1].emplace(u - 1, w);
        edges[u - 1].emplace(v - 1, w);
        adj[v - 1][u - 1] = true;
        adj[u - 1][v - 1] = true;
    }

    vector<unordered_set<int>> states;
    unordered_set<int> withoutState;
    for (int i = 0; i < n; i++)
        withoutState.insert(i);

    while (!withoutState.empty())
    {
        unordered_set<int> state;

        int city = *withoutState.begin();
        state.insert(city);
        withoutState.erase(city);

        for (int i = 0; i < n; ++i)
        {
            if (adj[city][i] && city != i)
            {
                state.insert(i);
                withoutState.erase(i);
            }
        }

        states.emplace_back(state);
    }

    int result = numeric_limits<int>::max();

    for (const auto& state : states)
    {
        if (state.size() < 2)
            continue;

        unordered_set<int> visited, unvisited;
        for (auto city : state)
            unvisited.insert(city);
        int city = *unvisited.begin();
        unvisited.erase(city);
        visited.insert(city);

        result = min(result, getMinMaxWeight(edges, visited, unvisited));
    }

    cout << result - 1 << endl;
    return EXIT_SUCCESS;
}
