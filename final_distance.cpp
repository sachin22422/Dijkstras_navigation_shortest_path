#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream> // Include this header for ifstream
#include <limits>

using namespace std;

class Edge {
public:
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

map<string, int> nodeIDs; // Map to store hardcoded node names and their corresponding IDs

void initializeNodeIDs() {
    // Add more node names and IDs here
    nodeIDs["Karnataka"] = 1;
    nodeIDs["Andhra_Pradesh"] = 2;
    nodeIDs["Goa"] = 3;
    nodeIDs["Kerala"] = 4;
    nodeIDs["Telangana"] = 5;
    nodeIDs["Tamil_Nadu"] = 6;
    nodeIDs["Maharashtra"] = 7;
    nodeIDs["Delhi"] = 8;
    nodeIDs["Haryana"] = 9;
    nodeIDs["Uttar_Pradesh"] = 10;
    nodeIDs["Uttarakhand"] = 11;
    nodeIDs["Punjab"] = 12;
    nodeIDs["Rajasthan"] = 13;
    nodeIDs["Himachal_Pradesh"] = 14;
    nodeIDs["Manipur"] = 15;
    nodeIDs["Mizoram"] = 16;
    nodeIDs["Nagaland"] = 17;
    nodeIDs["Assam"] = 18;
    nodeIDs["Odisha"] = 19;
    nodeIDs["Jharkhand"] = 20;
    nodeIDs["Chhattisgarh"] = 21;
    nodeIDs["West_Bengal"] = 22;
    nodeIDs["Jammu_and_Kashmir"] = 23;
    nodeIDs["Ladakh"] = 24;
    nodeIDs["Arunachal Pradesh"] = 25;
    nodeIDs["Tripura"] = 26;
    nodeIDs["Lakshadweep"] = 27;
    nodeIDs["Gujarat"] = 28;
    nodeIDs["Dadra_and_Nagar_Haveli_and_Daman_and_Diu"] = 29;
    nodeIDs["Meghalaya"] = 30;
    nodeIDs["Bihar"] = 31;
    nodeIDs["Puducherry"] = 32;
    nodeIDs["Andaman_and_Nicobar_Islands"] = 33;
    nodeIDs["Sikkim"] = 34;
    nodeIDs["Madhya_Pradesh"] = 35;
}

// ... The rest of your code remains unchanged ...


vector<Edge> getHardcodedEdges() {
    vector<Edge> edges;
    // Hardcode edge data from "edges.csv" here
    edges.emplace_back(1, 2, 436);
    edges.emplace_back(1, 3, 170);
    edges.emplace_back(1, 4, 500);
    edges.emplace_back(1, 5, 423);
    edges.emplace_back(1, 6, 564);
    edges.emplace_back(1, 7, 493);
    edges.emplace_back(8, 9, 120);
    edges.emplace_back(8, 10, 416);
    edges.emplace_back(9, 11, 305);
    edges.emplace_back(9, 12, 242);
    edges.emplace_back(9, 13, 291);
    edges.emplace_back(9, 10, 536);
    edges.emplace_back(9, 14, 250);
    edges.emplace_back(15, 16, 193);
    edges.emplace_back(15, 17, 178);
    edges.emplace_back(15, 18, 196);
    edges.emplace_back(19, 20, 296);
    edges.emplace_back(19, 21, 337);
    edges.emplace_back(19, 2, 795);
    edges.emplace_back(19, 22, 363);
    edges.emplace_back(2, 5, 146);
    edges.emplace_back(2, 6, 544);
    edges.emplace_back(2, 21, 637);
    edges.emplace_back(23, 12, 314);
    edges.emplace_back(23, 14, 302);
    edges.emplace_back(23, 24, 168);
    edges.emplace_back(25, 18, 120);
    edges.emplace_back(25, 17, 140);
    edges.emplace_back(11, 10, 404);
    edges.emplace_back(11, 14, 211);
    edges.emplace_back(20, 21, 436);
    edges.emplace_back(20, 31, 165);
    edges.emplace_back(20, 22, 271);
    edges.emplace_back(20, 10, 565);
    edges.emplace_back(12, 14, 174);
    edges.emplace_back(12, 13, 471);
    edges.emplace_back(26, 16, 129);
    edges.emplace_back(26, 18, 268);
    edges.emplace_back(27, 4, 397);
    edges.emplace_back(28, 35, 724);
    edges.emplace_back(28, 29, 298);
    edges.emplace_back(28, 13, 611);
    edges.emplace_back(28, 7, 545);
    edges.emplace_back(3, 7, 522);
    edges.emplace_back(24, 14, 370);
    edges.emplace_back(7, 21, 662);
    edges.emplace_back(7, 35, 497);
    edges.emplace_back(7, 29, 285);
    edges.emplace_back(7, 5, 470);
    edges.emplace_back(13, 10, 667);
    edges.emplace_back(13, 35, 543);
    edges.emplace_back(30, 18, 177);
    edges.emplace_back(10, 31, 477);
    edges.emplace_back(10, 35, 456);
    edges.emplace_back(10, 21, 626);
    edges.emplace_back(21, 35, 466);
    edges.emplace_back(21, 22, 645);
    edges.emplace_back(21, 5, 539);
    edges.emplace_back(17, 16, 371);
    edges.emplace_back(17, 18, 162);
    edges.emplace_back(31, 22, 348);
    edges.emplace_back(16, 18, 337);
    edges.emplace_back(18, 22, 625);
    edges.emplace_back(32, 6, 154);
    edges.emplace_back(32, 33, 1398);
    edges.emplace_back(34, 22, 511);
    edges.emplace_back(4, 6, 262);
    edges.emplace_back(33, 6, 1527);
    // Add more edges as needed
    return edges;
}

void addEdge(vector<vector<Edge>>& adj, const Edge& edge) {
    adj[edge.u].push_back(edge);
    adj[edge.v].push_back(edge);
}

pair<vector<int>, vector<int>> dijkstra(const vector<vector<Edge>>& adj, int src, int dest) {
    int N = adj.size();
    vector<int> dist(N, numeric_limits<int>::max());
    vector<int> fromNode(N, -1);
    dist[src] = 0;
    fromNode[src] = src;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int distance = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (distance > dist[node]) {
            continue;
        }

        for (const Edge& edge : adj[node]) {
            int other = (edge.u == node) ? edge.v : edge.u;
            int w = edge.w;

            if (dist[node] + w < dist[other]) {
                dist[other] = dist[node] + w;
                pq.push({dist[other], other});
                fromNode[other] = node;
            }
        }
    }

    vector<int> shortestPath;
    while (dest != fromNode[dest]) {
        shortestPath.push_back(dest);
        dest = fromNode[dest];
    }
    shortestPath.push_back(src);
    reverse(shortestPath.begin(), shortestPath.end());

    return {dist, shortestPath};
}

int main() {
    initializeNodeIDs(); // Initialize hardcoded node names and IDs

    vector<Edge> edges = getHardcodedEdges(); // Get hardcoded edge data

    int maxNode = 0;
    for (const Edge& edge : edges) {
        maxNode = max(maxNode, max(edge.u, edge.v));
    }
    int N = maxNode + 1;

    vector<vector<Edge>> adj(N);
    for (const Edge& edge : edges) {
        addEdge(adj, edge);
    }

    string srcName, destName;
    cout << "Type_your_Starting_State: ";
    cin >> srcName;
    cout << "Type_your_Destination_State: ";
    cin >> destName;

    int src, dest;

    // Assign IDs from the hardcoded data
    if (nodeIDs.find(srcName) != nodeIDs.end()) {
        src = nodeIDs[srcName];
    } else {
        cout << "Invalid_source_state_name." << endl;
        return 1;
    }

    if (nodeIDs.find(destName) != nodeIDs.end()) {
        dest = nodeIDs[destName];
    } else {
        cout << "Invalid_destination_state_name." << endl;
        return 1;
    }

    auto result = dijkstra(adj, src, dest);
    vector<int> distances = result.first;
    vector<int> path = result.second;

    cout << "Shortest_Distance: " << srcName << " -> " << destName << " : " << distances[dest] << "km" << endl;

    cout << "Shortest_Path: ";
    for (int i = 0; i < path.size(); ++i) {
        // Reverse lookup node names from IDs
        for (const auto& pair : nodeIDs) {
            if (pair.second == path[i]) {
                cout << pair.first;
                break;
            }
        }
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    return 0;
}



