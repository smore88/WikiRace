#include "wikirace.h"
#include "heap.h"

#include <cmath>
#include <bits/stdc++.h>
#include <map>
#include <vector>
#include <iostream>
#include <utility>

using namespace std;

int main(int argc,char* argv[])
{
    if (argc != 4) {
        std::cout << "Uses : ./main (pages connection file) (pages name file) (output file)" << std::endl;
        return 0;
    }

    std::cout << "Start building graph..." << std::endl;
    Wikirace wikirace(argv[1], argv[2]);
    std::cout << "Finished building graph..." << std::endl;

    bool correct_input = false;
    while (!correct_input) {
        std::cout << "\nWhich function do you want to run? \n [1] isAccessible \n [2] shortest_path \n [3] Components \n Please type '1', '2', or '3' :" << std::endl;
        std::string choice;
        std::cin >> choice;

        if (choice == "1") {
            std::cout << "\n Select your input type: \n [1] Node's ID (int) \n [2] Node's name (string) \n Please type '1' or '2' :" << std::endl;
            string type;
            std::cin >> type;
            if (type == "1") {
                std::cout << "\n Input your source node's ID :" << std::endl;
                int src_id;
                std::cin >> src_id;
                std::cout << "\n Input your destination node's ID :" << std::endl;
                int dest_id;
                std::cin >> dest_id;

                correct_input = true;
                wikirace.isAccessible(argv[3], src_id, dest_id);
                std::cout << "\n Successfully write the result to the output file" << std::endl;
            } else if (type == "2") {
                std::cout << "\n Input your source node's name :" << std::endl;
                string src_name;
                std::cin.ignore();
                std::getline(std::cin, src_name);
                std::cout << "\n Input your destination node's name :" << std::endl;
                string dest_name;
                std::getline(std::cin, dest_name);

                correct_input = true;
                wikirace.isAccessibleString(argv[3], src_name, dest_name);
                std::cout << "\n Successfully write the result to the output file" << std::endl;
            }

        } else if (choice == "2") {
            std::cout << "\n Select your input type: \n [1] Node's ID (int) \n [2] Node's name (string) \n Please type '1' or '2' :" << std::endl;
            string type;
            std::cin >> type;
            if (type == "1") {
                std::cout << "\n Input your source node's ID :" << std::endl;
                int src_id;
                std::cin >> src_id;
                std::cout << "\n Input your destination node's ID :" << std::endl;
                int dest_id;
                std::cin >> dest_id;

                correct_input = true;
                wikirace.shortest_path(argv[3], src_id, dest_id);
                std::cout << "\n Successfully write the result to the output file" << std::endl;
            } else if (type == "2") {
                std::cout << "\n Input your source node's name :" << std::endl;
                string src_name;
                std::cin.ignore();
                std::getline(std::cin, src_name);
                std::cout << "\n Input your destination node's name :" << std::endl;
                string dest_name;
                std::getline(std::cin, dest_name);

                correct_input = true;
                wikirace.shortest_path(argv[3], src_name, dest_name);
                std::cout << "\n Successfully write the result to the output file" << std::endl;
            }
        } else if (choice == "3") {
            correct_input = true;
            wikirace.Components(argv[3]);
            std::cout << "\n Successfully write the result to the output file" << std::endl;
        }
    }
    
    return 0;
}
