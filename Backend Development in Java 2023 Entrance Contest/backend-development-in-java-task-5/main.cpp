#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <valarray>

using std::cin;
using std::cout;
using std::vector;
using std::priority_queue;
using std::unordered_set;
using std::abs;
using std::endl;

typedef unsigned long long int Weight;

struct Edge {
    int to;
    Weight weight;
};

class Compare {
public:
    bool operator()(const Edge& lhs, const Edge& rhs) {
        return lhs.weight > rhs.weight;
    }
};

struct Vertex {
    int x{};
    int y{};
    std::priority_queue<Edge, std::vector<Edge>, Compare> edges;
};

Weight calculateWeight(const Vertex& v1, const Vertex& v2) {
    Weight dx = abs(v1.x - v2.x);
    Weight dy = abs(v1.y - v2.y);
    return dx * dx + dy * dy;
}

struct EdgePath {
    int from;
    int to;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Vertex> computers(n), servers(m);

    for (auto& c : computers)
        cin >> c.x >> c.y;

    for (auto& s : servers)
        cin >> s.x >> s.y;

    int centerServer = 0;
    Weight centerWeight = std::numeric_limits<Weight>::max();
    for (int i = 0; i < m; i++)
    {
        Weight currentWeight = 0;
        for (const auto& c : computers)
            currentWeight += calculateWeight(servers[i], c);

        if (currentWeight < centerWeight)
            centerWeight = currentWeight, centerServer = i;
    }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if (i != j)
                servers[i].edges.push(Edge{j, calculateWeight(servers[i], servers[j])});

    unordered_set<int> visited, unvisited;
    for (int i = 0; i < m; i++)
        unvisited.insert(i);
    unvisited.erase(centerServer);
    visited.insert(centerServer);

    vector<EdgePath> edgePaths;
    Weight treeWeight = 0;
    while (!unvisited.empty())
    {
        EdgePath edgePath{};
        Weight minWeight = std::numeric_limits<Weight>::max();

        for (auto from : visited)
        {
            auto& fromEdges = servers[from].edges;
            while (visited.find(fromEdges.top().to) != visited.end())
                fromEdges.pop();

            // fromEdges.top() - minimum-length edge going to an unvisited server
            if (fromEdges.top().weight < minWeight)
                minWeight = fromEdges.top().weight, edgePath = {from, fromEdges.top().to};
        }

        treeWeight += minWeight;
        edgePaths.emplace_back(edgePath);

        unvisited.erase(edgePath.to);
        visited.insert(edgePath.to);
    }

    cout << n + m - 1 << " " << centerWeight + treeWeight << endl;

    for (const auto& ep : edgePaths)
        cout << "s " << ep.to + 1 << " -> s " << ep.from + 1 << endl;

    for (int i = 0; i < n; i++)
        cout << "s " << centerServer + 1 << " -> c " << i + 1 << endl;

    return EXIT_SUCCESS;
}
