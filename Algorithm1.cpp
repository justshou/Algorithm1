#include <iostream>
#include <vector>
#include <string>

void removeEdge(std::vector<std::vector<std::pair<int,int>>>& adjMatrix, int u, int v) // pass by reference so it'll actually delete
{
    // pair between letter and the weight to get there
    // example is how I put below A -> (B, 18)
    auto& row = adjMatrix[u];

    // go through edges from u (current) and v (next)
    for (auto i = row.begin(); i != row.end(); ++i) {
        if (i->first == v) {  // find the one we gotta remove
            row.erase(i);     // remove it
            break;
        }
    }
}

void printMatrix(const std::vector<std::vector<std::pair<int,int>>> adjMatrix, const std::vector<std::string> vertices)
{
    int size = adjMatrix.size();
    for (int i = 0; i < size; ++i) { // count as O(n) where N is the size
        std::cout << vertices[i] << " -> "; // A ->
        for (const auto edge : adjMatrix[i]) { // count as O(n) where N is the number of edges from vertex i
            std::cout << "(" << vertices[edge.first] << ", " << edge.second << ") "; // the rest
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::string> vertices = {"A", "B", "C", "D", "E"};
    // A = 0, B = 1, C = 2, D = 3, E = 4
    int size = vertices.size();
    
    std::vector<std::vector<std::pair<int, int>>> adjMatrix(size);

    adjMatrix[0].push_back({1, 18}); // A -> (B, 18)
    adjMatrix[0].push_back({2, 14}); // A -> (C, 14)
    adjMatrix[0].push_back({4, 16}); // A -> (E, 16)

    adjMatrix[1].push_back({2, 2}); // B -> (C, 2)
    adjMatrix[1].push_back({3, 10}); // B -> (D, 10)

    adjMatrix[2].push_back({4, 6}); // C -> (E, 6)

    adjMatrix[3].push_back({0, 3}); // D -> (A, 3)
    adjMatrix[3].push_back({2, 15}); // D -> (C, 15)
    adjMatrix[3].push_back({4, 11}); // D -> (E, 11)

    adjMatrix[4].push_back({2, 17}); // E -> (C, 17)

    std::vector<std::vector<int>> cycles = {
        {0, 1, 3},
        {2, 4}
    };

    printMatrix(adjMatrix, vertices);

    
    int size_cycles = cycles.size();
    int smallestCycleIndex = 0;
    for (int i = 0; i < size_cycles; ++i) {
        if(cycles[i].size() < cycles[smallestCycleIndex].size()) { // counts as O(n) here
            smallestCycleIndex = i;
        }
    }
    //std::cout << "Smallest cycle: " << smallestCycleIndex + 1 << std::endl;


    for (int i = 0; i < size_cycles; ++i) { // count as O(n) here as well

        // skip smallest since we already found it above
        if (i == smallestCycleIndex)
            continue;

        std::vector<int> cyc = cycles[i];
        int size2 = cyc.size(); // get the size of the cycle we are removing

        // Remove each edge (u -> v) in this cycle
        for (int j = 0; j < size2; ++j) { // count as O(?) here
            // std::cout << "test remove " << vertices[cyc[j]] << " -> " << vertices[cyc[(j + 1) % size2]] << std::endl;
            int u = cyc[j];                      // current vertex
            int v = cyc[(j + 1) % size2];        // next vertex since we gotta reappend them

            removeEdge(adjMatrix, u, v);
        }
    }

    std::cout << "\n";
    printMatrix(adjMatrix, vertices);
    
}