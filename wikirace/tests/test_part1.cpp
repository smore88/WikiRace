#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>
# include <fstream>

#include "../src/wikirace.h"

using std::cout;
using std::endl;
using std::string;

TEST_CASE("small test constructor1", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", 
                        "../test_data/test_name_small.txt");

    REQUIRE(wikirace.get_name_map().at(0) == "Chiasmal syndrome");

    REQUIRE(wikirace.get_name_map().at(2) == "Pinakion");

    REQUIRE(wikirace.get_name_map().at(4) == "Zariski's main theorem");

    vector<pair<int,int>> vect1{std::make_pair(1,5)};
    REQUIRE(wikirace.get_graph().at(0) == vect1);

    vector<pair<int,int>> vect2{std::make_pair(2,5), std::make_pair(3,10)};
    REQUIRE(wikirace.get_graph().at(1) == vect2);

    vector<pair<int,int>> vect3{std::make_pair(4,5), std::make_pair(1,10)};
    REQUIRE(wikirace.get_graph().at(2) == vect3);
}

TEST_CASE("medium test constructor1", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");

    REQUIRE(wikirace.get_name_map().at(0) == "A");

    REQUIRE(wikirace.get_name_map().at(2) == "C");

    REQUIRE(wikirace.get_name_map().at(9) == "J");

    vector<pair<int,int>> vect1{std::make_pair(1,5), std::make_pair(5,10)};
    REQUIRE(wikirace.get_graph().at(0) == vect1);

    vector<pair<int,int>> vect2{std::make_pair(0,5)};
    REQUIRE(wikirace.get_graph().at(3) == vect2);

    vector<pair<int,int>> vect3{std::make_pair(11,5)};
    REQUIRE(wikirace.get_graph().at(10) == vect3);
}


TEST_CASE("full-data test constructor1", "[weight=10]")
{
    Wikirace wikirace("../data/wiki-topcats.txt", 
                        "../data/wiki-topcats-page-names.txt");

    REQUIRE(wikirace.get_name_map().at(3) == "LyndonHochschildSerre spectral sequence");

    REQUIRE(wikirace.get_name_map().at(374) == "Araucariana");

    REQUIRE(wikirace.get_name_map().at(1050349) == "Glenn Holtzman");

    vector<pair<int,int>> vect1{std::make_pair(82313,5), std::make_pair(82636,10),  std::make_pair(1457593,15),  std::make_pair(1458832,20),  std::make_pair(1458840,25),  std::make_pair(1458844,30),  std::make_pair(1459102,35)};
    REQUIRE(wikirace.get_graph().at(1460174) == vect1);

    vector<pair<int,int>> vect2{std::make_pair(10,5) , std::make_pair(1101496,10) ,  std::make_pair(1102709,15)};
    REQUIRE(wikirace.get_graph().at(9) == vect2);

    vector<pair<int,int>> vect3{std::make_pair(10772,5)};
    REQUIRE(wikirace.get_graph().at(0) == vect3);
}

TEST_CASE("test Dijkstra - small dataset", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", 
                        "../test_data/test_name_small.txt");

    vector<string> vect1{"Pinakion", "Kleroterion"};
    REQUIRE(wikirace.shortest_path("./output.txt", 2, 1) == vect1);

    vector<string> vect2{"Chiasmal syndrome", "Kleroterion", "Pinakion", "Zariski's main theorem"};
    REQUIRE(wikirace.shortest_path("./output.txt", 0, 4) == vect2);

    vector<string> vect3{};
    REQUIRE(wikirace.shortest_path("./output.txt", 3, 4) == vect3);
}

TEST_CASE("test Dijkstra - medium dataset - simple", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");

    vector<string> vect1{"B", "D", "A", "F"};
    REQUIRE(wikirace.shortest_path("./output.txt", 1, 5) == vect1);

    vector<string> vect2{"A", "F", "E"};
    REQUIRE(wikirace.shortest_path("./output.txt", 0, 4) == vect2);

    vector<string> vect3{"D", "A", "F", "E"};
    REQUIRE(wikirace.shortest_path("./output.txt", 3, 4) == vect3);
}



TEST_CASE("test Dijkstra - medium dataset - disconnected", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");

    vector<string> vect1{};
    REQUIRE(wikirace.shortest_path("./output.txt", 1, 8) == vect1);
}

TEST_CASE("test Dijkstra - medium dataset - cycles", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");


    vector<string> vect1{"I", "L"};
    REQUIRE(wikirace.shortest_path("./output.txt", 8, 11) == vect1);
    
    vector<string> vect2{"J", "K", "L", "I"};
    REQUIRE(wikirace.shortest_path("./output.txt", 9, 8) == vect2);

    vector<string> vect3{"D", "A", "F", "G"};
    REQUIRE(wikirace.shortest_path("./output.txt", 3, 6) == vect3);
}

TEST_CASE("test Dijkstra - full dataset", "[weight=10]")
{
    Wikirace wikirace("../data/wiki-topcats.txt", 
                        "../data/wiki-topcats-page-names.txt");

    vector<string> vect1{"Kleroterion", "Pinakion"};
    REQUIRE(wikirace.shortest_path("./output.txt", 1, 2) == vect1);

    vector<string> vect2{"Chiasmal syndrome", "Optic chiasm"};
    REQUIRE(wikirace.shortest_path("./output.txt", 0, 10772) == vect2);

    // (732528) 732422 1791471 
    // (732528) 732477 1791471
    vector<string> vect3{"Professional video over IP", "Resource reservation protocol", "Next Steps in Signaling"};
    REQUIRE(wikirace.shortest_path("./output.txt", 732528, 1791471) == vect3);

    vector<string> vect4{"Spermatophore", "Portable Document Format", "Universal 3D", "ArchiCAD", "Cinema 4D"};
    REQUIRE(wikirace.shortest_path("./output.txt", "Spermatophore", "Cinema 4D") == vect4);
    
}

TEST_CASE("test Dijkstra - using name", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", 
                        "../test_data/test_name_small.txt");

    vector<string> vect1{"Pinakion", "Kleroterion"};
    REQUIRE(wikirace.shortest_path("./output.txt", "Pinakion", "Kleroterion") == vect1);

    vector<string> vect2{"Chiasmal syndrome", "Kleroterion", "Pinakion", "Zariski's main theorem"};
    REQUIRE(wikirace.shortest_path("./output.txt", "Chiasmal syndrome", "Zariski's main theorem") == vect2);

    vector<string> vect3{};
    REQUIRE(wikirace.shortest_path("./output.txt", "LyndonHochschildSerre spectral sequence", "Zariski's main theorem") == vect3);
}

TEST_CASE("test BFS IsAccessible - small dataset - simple", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", "../test_data/test_name_small.txt");
    
    // startVertex & endVertex are just one node apart or the same node
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 0) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 1) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 3) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 2) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 4) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 1, 3) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 1, 2) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 1, 4) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 2, 1) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 2, 4) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 2, 3) == true);

    REQUIRE(wikirace.isAccessible("./output.txt", 1, 0) == false);
    REQUIRE(wikirace.isAccessible("./output.txt", 4, 0) == false);

    // startVertex & endVertex are multiple nodes apart
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 4) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 2, 3) == true);
}

TEST_CASE("test IsAccessibleString - small dataset - simple", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", "../test_data/test_name_small.txt");

    // startVertex & endVertex are just one node apart or the same node
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Chiasmal syndrome", "Kleroterion") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Kleroterion", "Pinakion") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Kleroterion", "LyndonHochschildSerre spectral sequence") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Pinakion", "Zariski's main theorem") == true);

    REQUIRE(wikirace.isAccessibleString("./output.txt", "Zariski's main theorem", "Chiasmal syndrome") == false);

    // startVertex & endVertex are multiple nodes apart
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Chiasmal syndrome", "LyndonHochschildSerre spectral sequence") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Kleroterion", "Zariski's main theorem") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Pinakion", "LyndonHochschildSerre spectral sequence") == true);

    REQUIRE(wikirace.isAccessibleString("./output.txt", "LyndonHochschildSerre spectral sequence", "Chiasmal syndrome") == false);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Zariski's main theorem", "Chiasmal syndrome") == false);
}

TEST_CASE("test BFS IsAccessible - medium dataset - simple", "[weight=10]") 
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");

    // startVertex & endVertex are just one node apart or the same node
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 0) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 1) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 5) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 1, 2) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 1, 3) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 2, 7) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 3, 0) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 4, 2) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 5, 4) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 5, 6) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 6, 4) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 7, 4) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 7, 6) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 8, 9) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 8, 11) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 9, 10) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 10, 11) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 11, 8) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 8, 8) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 9, 9) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 11, 11) == true);

    REQUIRE(wikirace.isAccessible("./output.txt", 5, 0) == false);

    // startVertex & endVertex are multiple nodes apart
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 3) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 1, 6) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 5, 7) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 6, 2) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 4, 6) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 7, 4) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 3, 5) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 8, 10) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 9, 11) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 9, 8) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 11, 10) == true);

    REQUIRE(wikirace.isAccessible("./output.txt", 6, 0) == false);
    REQUIRE(wikirace.isAccessible("./output.txt", 2, 0) == false);
    REQUIRE(wikirace.isAccessible("./output.txt", 7, 5) == false);
}

TEST_CASE("test IsAccessibleString - medium dataset - simple", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");

    // startLink & endLink are just one node apart
    REQUIRE(wikirace.isAccessibleString("./output.txt", "A", "B") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "C", "H") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "F", "E") == true);

    REQUIRE(wikirace.isAccessibleString("./output.txt", "E", "A") == false);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "E", "F") == false);

    // startLink & endLink are multiple nodes apart
    REQUIRE(wikirace.isAccessibleString("./output.txt", "A", "D") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "B", "G") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "G", "C") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "D", "F") == true);

    REQUIRE(wikirace.isAccessibleString("./output.txt", "G", "A") == false);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "H", "F") == false);
}

TEST_CASE("test BFS IsAccessible - medium dataset - disconnected", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");
    
    /*
        In medium dataset there are 2 disconnected major components when you draw the graph
        by hand. I am just checking here if nodes from those components are actually disconnected in my code
    */
    REQUIRE(wikirace.isAccessible("./output.txt", 8, 7) == false);
    REQUIRE(wikirace.isAccessible("./output.txt", 9, 4) == false);
    REQUIRE(wikirace.isAccessible("./output.txt", 11, 0) == false);
}

TEST_CASE("test IsAccessibleString - medium dataset - disconnected", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");
    
    REQUIRE(wikirace.isAccessibleString("./output.txt", "I", "H") == false);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "J", "E") == false);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "L", "A") == false);
}

TEST_CASE("test BFS IsAccessible - medium dataset - cycles", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");

    // Nodes 8 and 11 are cylic so just checking here if they are connected in the medium dataset
    REQUIRE(wikirace.isAccessible("./output.txt", 8, 11) == true);
}

TEST_CASE("test IsAccessibleString - medium dataset - cycles", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");

    // Nodes 8 : "I" and 11 : "L" are cylic so just checking here if they are connected in the medium dataset
    REQUIRE(wikirace.isAccessibleString("./output.txt", "I", "L") == true);
}

TEST_CASE("test BFS IsAccessible - wiki-topcats full dataset", "[weight=10]") 
{
    Wikirace wikirace("../data/wiki-topcats.txt", "../data/wiki-topcats.txt");

    // startVertex & endVertex are just one node apart or the same node
    REQUIRE(wikirace.isAccessible("./output.txt", 0, 10772) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 1, 170193) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 3, 1101724) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 4, 1103745) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 58, 1492353) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 144, 599070) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 204, 1595907) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 250, 813722) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 161, 788483) == true);


    // startVertex & endVertex are multiple nodes apart
    REQUIRE(wikirace.isAccessible("./output.txt", 161, 1101062) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 166935, 1702611) == true);
    REQUIRE(wikirace.isAccessible("./output.txt", 1756954, 28509) == true);
}

TEST_CASE("test IsAccessibleString - wiki-topcats full dataset", "[weight=10]")
{
    Wikirace wikirace("../data/wiki-topcats.txt", "../data/wiki-topcats.txt");

    // startLink & endLink are just one node apart
    REQUIRE(wikirace.isAccessibleString("./output.txt", "LyndonHochschildSerre spectral sequence", "Homological algebra") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Zariski's main theorem", "Finite morphism") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "St Paul of the Cross Cathedral", "Pipe organ") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Philip Grosser", "Alexander Berkman") == true);

    // startLink & endLink are multiple nodes apart
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Quasiperiodicity", "PlanetMath") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Hendrik van Riessen", "Terminism") == true);
    REQUIRE(wikirace.isAccessibleString("./output.txt", "Hossein Koushki", "Wind turbine") == true);
}

void splitData(const string& input_file_data, const string& input_file_name, 
                const string& output_file_data, const string& output_file_name, int num) {
    ifstream inDataFile(input_file_data);
    ofstream outDataFile(output_file_data);
    ifstream inNameFile(input_file_name);
    ofstream outNameFile(output_file_name);

    int count = 0;
    if (inDataFile.is_open()) {
        while (count < num){
            count++;
            string str;
            getline(inDataFile, str);
            outDataFile << str << endl;
        }
    }

    count = 0;
    if (inNameFile.is_open()) {
        while (count < num){
            count++;
            string str;
            getline(inNameFile, str);
            outNameFile << str << endl;
        }
    }
}

void sortBothConnectedNodes(const string& input_file_data, const string& output_file_data) {
    ifstream inDataFile(input_file_data);
    ofstream outDataFile(output_file_data);
    map<int, set<int>> map;
    string str;

    if (inDataFile.is_open()) {
        while (getline(inDataFile, str)) {
            unsigned idx = str.find(" ");
            int first = stoi(str.substr(0, idx));
            int second = stoi(str.substr(idx));
            if (map.find(first) == map.end())
                map[first] = {second};
            else
                map[first].insert(second);
            
            if (map.find(second) == map.end())
                continue;
            if(map[second].find(first) != map[second].end())
                outDataFile << first << " " << second << endl;
        }
    }
}

TEST_CASE("test Components - small dataset", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", 
                        "../test_data/test_name_small.txt");
    
    vector<set<int>> components = wikirace.Components("./output.txt");

    set<set<int>> solution;
    solution.insert({0});
    solution.insert({1, 2});
    solution.insert({3});
    solution.insert({4});

    REQUIRE(components.size() == 4);
    for (auto set : components)
        REQUIRE(solution.find(set) != solution.end());
}


TEST_CASE("test Components - medium dataset", "[weight=10]")
{
    // Include Cycle, Isolated Components, and Connected but not Strongly Connected Component
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");
    
    vector<set<int>> components = wikirace.Components("./output.txt");

    set<set<int>> solution;
    solution.insert({0, 1, 3});
    solution.insert({2, 4, 6, 7});
    solution.insert({5});
    solution.insert({8, 9, 10, 11});

    REQUIRE(components.size() == 4);
    for (auto set : components)
        REQUIRE(solution.find(set) != solution.end());
}

TEST_CASE("test Components - full dataset", "[weight=10]")
{

    splitData("../data/wiki-topcats.txt", "../data/wiki-topcats-page-names.txt", 
                "../data/wiki-topcats-cutted.txt", "../data/wiki-topcats-page-names-cutted.txt", 800000);

    sortBothConnectedNodes("../data/wiki-topcats-cutted.txt", 
                            "../data/wiki-topcats-cutted-interconnected-nodes.txt");

    Wikirace wikirace("../data/wiki-topcats-cutted.txt", 
                        "../data/wiki-topcats-page-names-cutted.txt");

    vector<set<int>> components = wikirace.Components("./output.txt");

    string file_data = "../data/wiki-topcats-cutted-interconnected-nodes.txt";
    ifstream dataFile(file_data);
    string str;

    int num = 100;
    int count = 0;
    if(dataFile.is_open()) {
        while (count < num) {
            count++;
            getline(dataFile, str);
            unsigned idx = str.find(" ");
            int first = stoi(str.substr(0, idx));
            int second = stoi(str.substr(idx));

            // if the component contains one of the two nods, it has to contain the other as well
            for (auto component : components) {
                if (component.find(first) != component.end())
                    REQUIRE(component.find(second) != component.end());
                else
                    REQUIRE(component.find(second) == component.end());
            }
        }
    }
}
