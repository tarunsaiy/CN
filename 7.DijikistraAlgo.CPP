#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Define a pair to represent a node and its distance
typedef pair<int, int> Node;

// Dijkstra's Algorithm Function
void dijkstra(const vector<vector<Node>> &graph, int source) {
    int n = graph.size(); // Number of nodes in the graph
    vector<int> dist(n, numeric_limits<int>::max()); // Initialize distances to infinity
    dist[source] = 0; // Distance to the source is 0

    // Min-heap priority queue (distance, node)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        // Skip if the current distance is not optimal
        if (currentDist > dist[currentNode]) continue;

        // Relax all neighbors
        for (const auto &neighbor : graph[currentNode]) {
            int nextNode = neighbor.first;
            int weight = neighbor.second;

            if (dist[currentNode] + weight < dist[nextNode]) {
                dist[nextNode] = dist[currentNode] + weight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    // Print shortest distances
    cout << "Shortest distances from node " << source << ":\n";
    for (int i = 0; i < n; ++i) {
        if (dist[i] == numeric_limits<int>::max()) {
            cout << "Node " << i << ": Unreachable\n";
        } else {
            cout << "Node " << i << ": " << dist[i] << "\n";
        }
    }
}

int main() {
    int nodes, edges;

    // Input number of nodes and edges
    cout << "Enter the number of nodes: ";
    cin >> nodes;
    cout << "Enter the number of edges: ";
    cin >> edges;

    // Graph representation as an adjacency list
    vector<vector<Node>> graph(nodes);

    cout << "Enter the edges (start end weight):\n";
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // Uncomment this line for undirected graph
    }

    int source;
    cout << "Enter the source node: ";
    cin >> source;

    if (source >= 0 && source < nodes) {
        dijkstra(graph, source);
    } else {
        cout << "Invalid source node!" << endl;
    }

    return 0;
}
// INPUT
// Enter the number of nodes: 5
// Enter the number of edges: 6
// Enter the edges (start end weight):
// 0 1 2
// 0 3 6
// 1 2 3
// 1 3 8
// 1 4 5
// 2 4 7
// Enter the source node: 0

// OUTPUT
// Enter the number of nodes: 5
// Enter the number of edges: 6
// Enter the edges (start end weight):
// 0 1 2
// 0 3 6
// 1 2 3
// 1 3 8
// 1 4 5
// 2 4 7
// Enter the source node: 0
