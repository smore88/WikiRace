#include "wikirace.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <limits>
#include <stack>
#include <stdexcept>

using namespace std;

Wikirace::Wikirace(const string& file_data, const string& file_name) {
    ifstream dataFile(file_data);
    ifstream nameFile(file_name);
    string str;

    if (dataFile.is_open()) {
        while (getline(dataFile, str)) {
            
            unsigned idx = str.find(" ");

            // stoi converts str to int
            int first = stoi(str.substr(0, idx));
            int second = stoi(str.substr(idx));

            if (adj_.find(first) != adj_.end()) {
                // key already found
                // assumes never adding duplicates
                adj_[first].push_back(make_pair(second, adj_[first].back().second + 5));
            } else {
                // key not found
                vector<std::pair<int,int>> vec {make_pair(second, 5)}; 
                adj_.insert({first , vec});
            }
        }
    }

    if (nameFile.is_open()) {
        while (getline(nameFile, str)) {
            unsigned idx = str.find(" ");
            string id = str.substr(0, idx);
            string name = str.substr(idx+1);

            name_.insert({stoi(id), name});
            id_.insert({name, stoi(id)});
            if (adj_.find(stoi(id)) == adj_.end()) {
                // nodes with no outbound edges
                vector<std::pair<int,int>> vec;
                adj_.insert({stoi(id) , vec});
            }
        }
    }
}

vector<string> Wikirace::shortest_path(const string& file_path, const string src, const string dest) {
    if (id_.find(src) == id_.end()) {
        throw std::invalid_argument("Shortest Path: Source node does not exist");
    }
    if (id_.find(dest) == id_.end()) {
        throw std::invalid_argument("Shortest Path: Destination node does not exist");
    }

    // Call the int version of shortest_path
    return shortest_path(file_path, id_.at(src), id_.at(dest));
}

vector<string> Wikirace::shortest_path(const string& file_path, const int src, const int dest) {
    // If Dijkstra's was never called on src, then call Dijkstra's on source
    if (shortest_paths_.find(src) == shortest_paths_.end()) {
        dijkstra(src);
    }

    // Get the stored Dijkstra's result
    const map<int, std::pair<int, int>>& src_dijkstra = shortest_paths_.at(src);

    // Feed the Dijkstra's result into "path"
    vector<string> path;

    int curr = dest;
    while (curr != -1) {
        path.insert(path.begin(), name_.at(curr));
        curr = src_dijkstra.at(curr).first;
    }

    if (path.at(0) != name_.at(src)) { // dest inaccessible from src
        path = vector<string>();
    }

    // Write the result to output file
    ofstream myfile(file_path);
    if (myfile.is_open()) {
        if (path.size() != 0) {
            for (string& name : path) {
                myfile << name << "\n";
            }
        } else {
            myfile << "Impossible to traverse to the destination node." << "\n";
        }
        myfile.close();
    } else {
        std::cout << "Unable to open the output destination file" << std::endl;
    }

    // Return the result
    return path;
}

void Wikirace::dijkstra(const int src) {
    if (name_.find(src) == name_.end())  {
        throw std::invalid_argument("Dijkstra: Source node does not exist");
    }

    // Store predecessor and distance from src
    std::map<int, std::pair<int, int>> p_and_d; // point - (its predecessor, its distance from src)

    for(std::map<int, string>::iterator it = name_.begin(); it != name_.end(); ++it) {
        p_and_d[it -> first] = std::make_pair(-1, std::numeric_limits<int>::max());
    }
    p_and_d.at(src) = std::make_pair(-1, 0);

    // Create priority queue using min-Heap
    heap<std::pair<int, int>> pq; // distance from src - Node ID
    pq.push(std::make_pair(0, src));

    while (!pq.empty()) {
        std::pair<int, int> u_pair_distfromsrc_and_ID = pq.pop();
        int u = u_pair_distfromsrc_and_ID.second; // Get the node ID

        // If the item from pq is not the most updated version, then skip
        if (u_pair_distfromsrc_and_ID.first != p_and_d.at(u).second) {
            continue;
        }
        
        for (pair<int, int> v_pair_ID_and_weight : adj_.at(u)) {
            int v = v_pair_ID_and_weight.first;
            int weight_u_to_v = v_pair_ID_and_weight.second;
            int new_dist = weight_u_to_v + p_and_d.at(u).second;

            if (new_dist < p_and_d.at(v).second) {
                p_and_d.at(v) = std::make_pair(u, new_dist);
                pq.push(std::make_pair(new_dist, v));
            }
        }
    }

    // Store the Dijkstra's result
    shortest_paths_[src] = p_and_d;
}
 
bool Wikirace::isAccessibleString(const string& file_path, string startLink, string endLink) {
    // convert startLink and endLink into their respective node ID (integerss)
    int startVertex = id_[startLink];
    int endVertex = id_[endLink];
    
    // Run the BFS algorithm isAccessible (the integer version)
    return isAccessible(file_path, startVertex, endVertex);
}

bool Wikirace::isAccessible(const string& file_path, int startVertex, int endVertex) {

    // Base case that checks if the user is going from the same node back to itself, the path must exist.
    if(startVertex == endVertex) {
        return true;
    }
    
    // Create a vector<bool> of the size of the adjacency list and set all nodes to be visited = false.
    vector<bool> visited;                          
    for(unsigned i = 0; i < adj_.size(); i++) {
        visited.push_back(false);
    }

    /*
        Steps
            1) Create an empty queue, set the startVertex visited as true, push startVertex to queue
            2) Run BFS algorithm that searches through the nodes in the adjacency list pair, if it is 
            a new node not visisted yet set it to visited and push it to the queue
            3) Check if the queue is not empty, if it is return false, else check the latest node at the front and pop it
            and repeat the entire process again until the queue is empty or until the node we reach is the endNode
    */
    queue<int> q;
    visited[startVertex] = true;
    q.push(startVertex);
    while(!q.empty()) {
        int currVertex = q.front();
        q.pop();
        for(auto& pair : adj_.at(currVertex)) {
            if(visited[pair.first] == false) {
                visited[pair.first] = true;
                q.push(pair.first);
                if (pair.first == endVertex) {
                    // Write the result to output file
                    ofstream myfile(file_path);
                    if (myfile.is_open()) {
                        myfile << "true" << "\n";
                        myfile.close();
                    } else {
                        std::cout << "Unable to open the output destination file" << std::endl;
                    }

                    return true;
                }
            }
        }
    }
    // Write the result to output file
    ofstream myfile(file_path);
    if (myfile.is_open()) {
        myfile << "false" << "\n";
        myfile.close();
    } else {
        std::cout << "Unable to open the output destination file" << std::endl;
    }
    return false;
}

void Wikirace::DFS(int node, map<int, vector<pair<int, int>>>& adj, set<int>& visited, stack<int>& s) {
    // check whether the node is already visited
    if (visited.find(node) != visited.end())
        return;
    visited.insert(node);

    // check whether the node has neighbors
    if (adj.find(node) == adj.end()) {
        s.push(node);
        return;
    }

    // Do DFS if the node has neighbors
    vector<pair<int, int>> adj_nodes = adj.find(node)->second;
    for (pair<int, int>& adj_node : adj_nodes)
        DFS(adj_node.first, adj, visited, s);
    
    // push the node to the stack
    s.push(node);
}

void Wikirace::DFS(int node, map<int, vector<pair<int, int>>>& adj, set<int>& visited, set<int>& local) {
    // check whether the node is already visited
    if (visited.find(node) != visited.end())
        return;
    visited.insert(node);
    local.insert(node);

    // check whether the node has neighbors
    if (adj.find(node) == adj.end())
        return;
    
    // Do DFS if the node has neighbors
    vector<pair<int, int>> adj_nodes = adj.find(node)->second;
    for (pair<int, int>& adj_node : adj_nodes)
        DFS(adj_node.first, adj, visited, local);
}

vector<set<int>> Wikirace::Components(const string& file_path) {
    // Do DFS on G and set up the stack
    stack<int> s;
    set<int> visited;
    for (auto it = adj_.begin(); it != adj_.end(); it++) {
        DFS(it->first, adj_, visited, s);
    }

    // Make the tranpose of the graph G
    map<int, vector<pair<int, int>>> adj_transpose;
    for (auto it = adj_.begin(); it != adj_.end(); it++) {
        for (pair<int, int> adj_node : it->second)
            adj_transpose[adj_node.first].push_back(make_pair(it->first, adj_node.second));
    }

    // Do DFS on G transpose and get local set of a strongly connected component
    vector<set<int>> to_return;
    set<int> local;
    visited.clear();
    while (!s.empty()) {
        if (visited.find(s.top()) == visited.end()) {
            DFS(s.top(), adj_transpose, visited, local);
            to_return.push_back(local);
            local.clear();
        }
        s.pop();
    }

    // Write the result to output file
    ofstream myfile(file_path);
    if (myfile.is_open()) {
        for (auto& set : to_return) {
            for (auto& integer : set)
                myfile << integer << ",";
            myfile << endl;
        }
        myfile.close();
    } else {
        std::cout << "Unable to open the output destination file" << std::endl;
    }

    return to_return;
}
