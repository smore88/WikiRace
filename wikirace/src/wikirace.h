#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <queue>

#include "heap.h"

#include <set>
#include <stack>

using namespace std;

class Wikirace {
    public:
        /**
        * Constructor for the graph
        *
        * @param file_data     File containing connections between pages ID
        * @param file_name     File containing pages's name and ID
        */
        Wikirace(const string& file_data, const string& file_name);

        /**
        * Function for finding the shortest path from one page to another page, and write to the file file_path
        *
        * @param file_path     A path that indicate where the output will be written
        * @param src           The origin or source page (as a string)
        * @param dest          The destination or goal page (as a string)
        * @return              The shortest path from src to dest as a vector of pages' names (as strings)
        */
        vector<string> shortest_path(const string& file_path, const string src, const string dest);

        /**
        * Function for finding the shortest path from one page to another page, and write to the file file_path
        *
        * @param file_path     A path that indicate where the output will be written
        * @param src           The origin or source page (as an int)
        * @param dest          The destination or goal page (as an int)
        * @return              The shortest path from src to dest as a vector of pages' names (as strings)
        */
        vector<string> shortest_path(const string& file_path, const int src, const int dest);

        /**
        * Checks whether there is a path from one link to another link.
        * 
        * @param file_path     A path that indicate where the output will be written
        * @param startLink     Starting node name to begin BFS.
        * @param endLink       Ending node name to end BFS.   
        * @return              Boolean value of true or false if a path is found from startLink to endLink.
        */
        bool isAccessibleString(const string& file_path, string startLink, string endLink);
        
        /**
        * Checks whether there is a path from one link to another link.
        * 
        * @param file_path     A path that indicate where the output will be written
        * @param startVertex   Starting node ID to begin BFS.
        * @param endVertex     Ending node ID to end BFS.   
        * @return              Boolean value of true or false if a path is found from startLink to endLink.
        */
        bool isAccessible(const string& file_path, int startVertex, int endVertex);
        
        /**
        * Perform Kosaraju's Algorithm, and return a vector of set of integers.
        * Each set indicate a strongly connected component.
        * NOTE: The algorithm has limit approxmiately 65000 nodes or approximately around 800000 edges
        * However, variation depends on the density of the graph
        * 
        * @param file_path     A path that indicate where the output will be written
        * @return              A vector of sets, each of which is a strongly connected component
        */
        vector<set<int>> Components(const string& file_path);

        /**
        * Getter function for the graph (stored as adjacency list)
        * 
        * @return              Our graph (stored as adjacency list)
        */
        const map<int, vector<pair<int, int>>>& get_graph() { return adj_; }

        /**
        * Getter function for the map from pages name to pages ID
        * 
        * @return              A map from pages name to pages ID
        */
        const map<int, string>& get_name_map() { return name_; }
        
        /**
        * Getter function for the map from pages ID to pages name
        * 
        * @return              A map from pages ID to pages name
        */
        const map<string, int>& get_ID_map() { return id_; }

    private:
        // Store the graph as adjacency list
        map<int, vector<pair<int, int>>> adj_; // starting vertex, outgoing vertex, weight

        // Store the map of Node ID to Node name
        map<int, string> name_;

        // Store the map of Node name to Node ID
        map<string, int> id_;

        /** A  map to store the shortest paths from each node to all other nodes
        * i.e. store the result of calling Dijkstra's on each node,
        * so we don't have to perform the algorithm again if it is called
        */ 
        map<int, map<int, std::pair<int, int>>> shortest_paths_; // src : [ (dest : predecessor and distance of dest in src's Dijkstra), ... ]
        
        /**
        * Helper function to perform Dijkstra's on the src node
        * 
        * @param src             Node to start Dijkstra's algorithm
        */
        void dijkstra(const int src);
        
        /**
        * Helper function of Components() for depth-first traversing on graph
        * Build the stack of nodes finished visiting step by step
        * 
        * @param node            Current visiting node
        * @param adj             The adjacency list of Graph G
        * @param visited         The set of nodes already visited
        * @param s               The stack of nodes finished visiting
        */
        void DFS(int node, map<int, vector<pair<int, int>>>& adj, set<int>& visited, stack<int>& s);

        /**
        * Helper function of Components() for depth-first traversing on graph's transpose
        * Build up one strongly connected component each time
        * 
        * @param node            Current visiting node
        * @param adj             The adjacency list of Graph G transpose
        * @param visited         The set of nodes already visited
        * @param local           The set of nodes in a single strongly connected component
        */
        void DFS(int node, map<int, vector<pair<int, int>>>& adj, set<int>& visited, set<int>& local);
};

