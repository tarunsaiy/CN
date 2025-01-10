#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#define INF numeric_limits<int>::max()

struct Node {
    vector<int> distance; // Distance vector
    vector<int> nextHop;  // Next hop for each destination
};

void initializeRoutingTable(vector<Node> &nodes, int numNodes) {
    for (int i = 0; i < numNodes; ++i) {
        nodes[i].distance.resize(numNodes, INF);
        nodes[i].nextHop.resize(numNodes, -1);

        // Distance to itself is 0
        nodes[i].distance[i] = 0;
        nodes[i].nextHop[i] = i;
    }
}

void updateRoutingTable(vector<Node> &nodes, int numNodes, const vector<vector<int>> &graph) {
    bool updated;

    do {
        updated = false;

        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                for (int k = 0; k < numNodes; ++k) {
                    if (graph[i][k] != INF && nodes[k].distance[j] != INF) {
                        int newDist = graph[i][k] + nodes[k].distance[j];
                        if (newDist < nodes[i].distance[j]) {
                            nodes[i].distance[j] = newDist;
                            nodes[i].nextHop[j] = k;
                            updated = true;
                        }
                    }
                }
            }
        }
    } while (updated);
}

void printRoutingTable(const vector<Node> &nodes, int numNodes) {
    for (int i = 0; i < numNodes; ++i) {
        cout << "Routing table for node " << i << ":\n";
        cout << "Destination\tDistance\tNext Hop\n";

        for (int j = 0; j < numNodes; ++j) {
            if (nodes[i].distance[j] == INF) {
                cout << j << "\t\tINF\t\t-\n";
            } else {
                cout << j << "\t\t" << nodes[i].distance[j] << "\t\t" << nodes[i].nextHop[j] << "\n";
            }
        }
        cout << "\n";
    }
}

int main() {
    int numNodes;

    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    vector<vector<int>> graph(numNodes, vector<int>(numNodes, INF));
    vector<Node> nodes(numNodes);

    // Input graph as an adjacency matrix
    cout << "Enter the adjacency matrix (use " << INF << " for no connection):\n";
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            cin >> graph[i][j];
            if (i == j) graph[i][j] = 0; // Distance to self is 0
        }
    }

    // Initialize and update the routing table
    initializeRoutingTable(nodes, numNodes);
    updateRoutingTable(nodes, numNodes, graph);

    // Print the routing table
    printRoutingTable(nodes, numNodes);

    return 0;
}

// INPUT
// Enter the number of nodes: 4
// Enter the adjacency matrix (use 2147483647 for no connection):
// 0 1 4 2147483647
// 1 0 2 6
// 4 2 0 3
// 2147483647 6 3 0

// OUTPUT
// Routing table for node 0:
// Destination     Distance        Next Hop
// 0               0               0
// 1               1               1
// 2               3               1
// 3               6               2

// Routing table for node 1:
// Destination     Distance        Next Hop
// 0               1               0
// 1               0               1
// 2               2               2
// 3               5               2

// Routing table for node 2:
// Destination     Distance        Next Hop
// 0               3               1
// 1               2               1
// 2               0               2
// 3               3               3

// Routing table for node 3:
// Destination     Distance        Next Hop
// 0               6               2
// 1               5               2
// 2               3               2
// 3               0               3
