#include <iostream>
#include <vector>
#include <string>

using namespace std;

// helper function to print the list (from Algorithm 1)
void printMatrix(const vector<vector<pair<int,int>>> adjMatrix, const vector<string> vertices)
{
    int size = adjMatrix.size();
    for (int i = 0; i < size; ++i) { // count as O(n) where N is the size
        cout << vertices[i] << " -> "; // A ->
        for (const auto edge : adjMatrix[i]) { // count as O(n) where N is the number of edges from vertex i
            cout << "(" << vertices[edge.first] << ", " << edge.second << ") "; // the rest
        }
        cout << endl;
    }
}


// remove an edge u -> v
void removeEdge(vector<vector<pair<int,int>>>& adj, int u, int v) {
    // get the list of edges for vertex u
    auto& row = adj[u];


    // iterate through the edges from vertex u
    for (auto it = row.begin(); it != row.end(); ++it) {
        if (it->first == v) { // check if the edge goes to vertex v
            row.erase(it); // remove this edge from the adjacency list
            break;
        }
    }
}

// divide & conquer: remove all edges in a cycle
void removeCycleDivideConquer(vector<vector<pair<int,int>>>& adj, const vector<int>& cycle) {

    int n = cycle.size();

    if (n <= 1) return; // nothing to remove

    if (n == 2) { // single edge: BEST CASE
        removeEdge(adj, cycle[0], cycle[1]);
        return;
    }

    int mid = n / 2;

    // divide: split into left and right halves
    vector<int> left(cycle.begin(), cycle.begin() + mid);
    vector<int> right(cycle.begin() + mid, cycle.end());

    // conquer: recursively remove edges in each half
    removeCycleDivideConquer(adj, left);
    removeCycleDivideConquer(adj, right);

    // remove bridge edge between halves
    removeEdge(adj, cycle[mid - 1], cycle[mid]);

    // remove the edge that closes the cycle 
    removeEdge(adj, cycle.back(), cycle.front());
}

int main() {

    // vertices same as project example
    vector<string> vertices = {"A", "B", "C", "D", "E"};
    int size = vertices.size();

    vector<vector<pair<int, int>>> adj(size);

    // adding all edges from the example
    adj[0].push_back({1, 18}); // A -> B
    adj[0].push_back({2, 14}); // A -> C
    adj[0].push_back({4, 16}); // A -> E

    adj[1].push_back({2, 2});  // B -> C
    adj[1].push_back({3, 10}); // B -> D

    adj[2].push_back({4, 6});  // C -> E

    adj[3].push_back({0, 3});  // D -> A
    adj[3].push_back({2, 15}); // D -> C
    adj[3].push_back({4, 11}); // D -> E

    adj[4].push_back({2, 17}); // E -> C

    // cycles given in the example
    vector<vector<int>> cycles = {
        {0, 1, 3}, // A -> B -> D
        {2, 4}     // C -> E
    };

    cout << "before removing cycle edges:\n";
    printMatrix(adj, vertices);
    cout << "\n";

    // find the smallest cycle index
    int smallestIndex = 0;
    for (int i = 1; i < cycles.size(); i++) {
        if (cycles[i].size() < cycles[smallestIndex].size()) {
            smallestIndex = i;
        }
    }

    // remove all cycles except the smallest one
    // time complexity: O(m*n) where m is the 
    // number of edges in all cycles being removed and 
    // n is the size of cycles 
    for (int i = 0; i < cycles.size(); i++) {

        if (i == smallestIndex)
            continue;

        // remove every edge in this cycle so the cycle is fully gone
        removeCycleDivideConquer(adj, cycles[i]);
    }


    cout << "after removing cycle edges:\n";
    printMatrix(adj, vertices);

    return 0;
}
