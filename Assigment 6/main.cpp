#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;


void readGraph (const string& filename , vector<vector<int>>& graph , int& N) {
    ifstream file (filename);
    string line;
    vector<vector<int>> tempGraph;
    string dummy;
    getline (file , dummy);
    getline (file , dummy);
    while (getline (file , line)) {
        stringstream ss (line);
        string value;
        vector<int> row;
        ss.ignore (2); // Skip the first character in the string stream
        while (getline (ss , value , ',')) {
            if (value == "0") {
                row.push_back (0);
            }
            else {
                row.push_back (stoi (value));
            }
        }
        tempGraph.push_back (row);
    }

    N = tempGraph.size ();
    graph = tempGraph;
}

void printGraph (const vector<vector<int>>& graph) {
    int N = graph.size ();
    int edgeCount = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (graph[i][j] != 0) {
                ++edgeCount;
            }
        }
    }
    edgeCount /= 2; // Since the graph is undirected

    cout << "Number of Vertices = " << N << endl;
    cout << "Number of Edges = " << edgeCount << endl;

    cout << "\nAdjacency Matrix" << endl;
    for (const auto& row : graph) {
        for (int val : row) {

            cout << setw (3) << val;
        }
        cout << endl;
    }

    cout << "\nGraph Edges" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (graph[i][j] != 0) {
                cout << char ('A' + i) << " " << char ('A' + j) << " " << graph[i][j] << endl;
            }
        }
    }
}

void DFSUtil (int v , vector<bool>& visited , const vector<vector<int>>& graph , vector<int>& result) {
    visited[v] = true;
    result.push_back (v + 1);

    for (int i = 0; i < graph.size (); ++i) {
        if (graph[v][i] != 0 && !visited[i]) {
            DFSUtil (i , visited , graph , result);
        }
    }
}

void DFS (const vector<vector<int>>& graph , vector<int>& result) {
    int N = graph.size ();
    vector<bool> visited (N , false);

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            DFSUtil (i , visited , graph , result);
        }
    }
}

void floydWarshall(const vector<vector<int>>& graph, vector<vector<int>>& dist, vector<vector<int>>& next) {
    int N = graph.size();

    // Initialize dist and next matrices
    dist = graph;
    next.resize(N, vector<int>(N, -1));

    // Update dist and next matrices
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (dist[i][k] != 0 && dist[k][j] != 0 && (dist[i][j] == 0 || dist[i][k] + dist[k][j] < dist[i][j])) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = k;
                }
                if(i==j){
                    dist[i][j] = 0;
                }
            }
        }
    }
    cout << "\nDistance Matrix" << endl;
    for (const auto& row : dist) {
        for (int val : row) {
            cout << setw(3) << val;
        }
        cout << endl;
    }
}



void printShortestPathsFromNode (int start , const vector<vector<int>>& dist , const vector<vector<int>>& next) {
    int N = dist.size ();
    cout << "\nShortest Paths from Node " << char ('A' + start) << endl;
    for (int i = 0; i < N; ++i) {
            cout << setw (5) << dist[start][i] << " ";
            cout << endl;
    }
}

int main () {


    vector<vector<int>> graph;
    int N;
    readGraph ("Cities14.csv" , graph , N);

    printGraph (graph);

    vector<int> dfsResult;
    DFS (graph , dfsResult);

    cout << "\nDFS Traversal\nval =";
    for (int val : dfsResult) {
        cout << setw (5) << val;
    }
    cout << endl;

    vector<vector<int>> dist , next;
    floydWarshall (graph , dist , next);

    printShortestPathsFromNode (0 , dist , next);

    return 0;
}