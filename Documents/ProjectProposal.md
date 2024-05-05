## Leading Question 

Our project is inspired by a famous game called WikiRace, where we’re given a selected starting Wikipedia page and a destination Wikipedia page. The goal is to navigate from the starting page to the destination page solely by clicking the links embedded within each page using the fewest clicks. In our project, we’ll solve the following challenges:

1) Given a starting page and a destination page, is it possible to navigate using the above rules? We’ll solve this problem by using our Breadth-First-Search (BFS) traversal algorithm. We choose this algorithm because we just want to check if the walk to the destination page exists or not, so BFS and DFS are good choices. However, since we have a big and complex graph, DFS might took too long and run out of memory, so we’ll use BFS.

2) Given a starting page and a destination page. What is the fewest clicks that we can use to navigate to that destination page? This means that, using graph terminology, we’re trying to find the shortest distance from the starting node to the destination node. We’ll solve tis problem by using a shortest path algorithm covered in class called “Dijkstra’s Algorithm”. We choose this algorithm simply because it is sufficient and efficient. Each outgoing edge in the entire directed graph has an associated weight/cost that is linearly associated with its distance from the top of the page. For simplicity, the first outgoing edge (first wiki hyperlink on a page) will have the lowest associated cost, and is located furthest to the top, given in the dataset. Specifically, we are assuming that it takes twice as lonk to "read and proccess" a link, compared to a word. A human can read and process a word in 250 milliseconds. Therfore, the staring value will be 5 units of time, the cost increasing by 5 for the next outgoing edge (next link in the wiki article.) For example, if a wiki article had 3 embeded hyper links, the cost for each one, in order would be: 5, 10, 15. 

3) Given all Wikipedia pages in our data set, can we expand the competition by changing from just having one destination page to having a list of destination pages? The challenge or constraint of this is to make a list of destination pages which guarantees that no matter what order a participant visits the destination pages, he/she would never be stuck at a point where there’s a page that they cannot visit and can’t recover (and thus can’t enjoy the competition). We’ll solve this by categorizing pages into groups such that in each group, all pages in each group are reachable from each other, or using graph terminology, we’ll divide nodes into strongly connected components (since this is a directed graph). This can be achieved by using a strongly connected components’ algorithm named Kosaraju’s algorithm.




## Dataset Acquisition and Processing

### Data Format
Given our dataset of Wikipedia Hyperlinks provided by Stanford:

http://snap.stanford.edu/data/wiki-topcats.html

We have three given files, for which we will only consider the first two.
Wikipedia Page number to another Wikipedia Page 
Wikipedia Page number to Page Name 

The first file needs some explanation. Each line in the .txt file contains a vertex (page #), and a child vertex (another page #). For almost all vertex’s, it contains multiple neighboring vertices. Such that the subsequent line would also start with the same starting vertex, in ascending order. The second file is a one-to-one mapping between Wikipedia Page number and its respective Page Name also in ascending order, along with that pages respective weight. The dataset includes ~1.8 million unique Wikipedia Pages, we will refer to this as V, the number of vertices. Currently, we plan to take only a subset of the V, vertices. We predict that V is approximately 100,000, N. However, we will take the maximum number our computer can handle. Therefore we will define the subset, currently to only include a vertex V, such that its Wikipedia Number <= 100,000.


### Data Correction

Based on the two files above, we are given a directed graph. Therefore all vertices V that are chosen must obey the strict cap we impose (N). Therefore we should have exactly (N) vertices, meaning we will have to check that in each line we are getting either the same Wikipedia Number, or we moved onto the very next (Wikipedia Number + 1) starting vertex. If the case happens that we miss a Wikipedia Number, we will include that as a vertex, such that it has no outgoing edges (based on the definition of our input.) 

We should also handle the case that the second data file does not contain a Wikipedia Page number, nor the Name, or both. Under the circumstance a Wikipedia page number is missing, we will fill it in (since it is already sorted in ascending order) with the correct number, and its corresponding Wikipedia page name. If the name does not exist, or both do not, we will follow the same procedure above however with a miscellaneous string of text for the name. This renders the current Wikipedia page as garbage, much like a dead end, since this is a directed graph. If and only if it has an associated edge, then would we adjust the weight/cost associated with travelling through to that node.


### Data Storage

We will not be using an adjacency matrix to store the graph. If we did, it would be of size (N x N), where 99% of the values in each row would be 0. Meaning we would be storing a ridiculously large number of zeros, such that the matrix would be very sparse.

We plan to store our representation of the graph in an adjacency list, where we store the Wikipedia Page Numbers only. If the average number of outgoing edges of any given vertex was M. Then our adjacency list would hold O(N*M) Wikipedia Page numbers. We plan to store the mapping between Wikipedia Page number and the Wikipedia page name in a STL Map. Such that it would be of the size O(N).

Overall the space complexity can be represented as O(N*M + N), or O(N*M). Where N ~ 100,000 and M is the average number of outgoing edges for any vertex V.


## Algorithm 

- Constructor(int size): 
Takes in one argument “size”, which indicate the number of wikipedia page should be considered. It should take O(V+E) time complexity and O(V+E) space complexity.

- Constructor(string csv, int num):
Takes in a csv dataset. “num” indicates the number of parameters each data can possibly have.
It should take O(V+E) time complexity and O(V+E) space complexity.

- bool IsAccessible(string link_1, string link_2):
Inputs are two wikipedia links, and the output is whether link_2 is accessible from link_1. 
It would use the basic breadth first search(BFS) on link_1, and check whether link_2 can be found. This would take O(V+E) time complexity and O(V+E) space complexity.

- int ShortestPath(string link_1, string link_2):
Inputs are two wikipedia links, and the output is the shortest path between link_1 and link_2. If the link_2 is not accessible from link_1, it would return -1.
It would pick link_1 as the starting node, run Dijkstra’s Algorithm. If link_2 at the end is still infinity, then it indicates that link_2 is inaccessible, or it would return the shortest distance from link_2 and link_1. This would take O(V+ElogV) time complexity and O(V) space complexity.

- int Components():
There would be no input parameter, and the function would return the strongly connected components in the graph. It would implement by Kosaraju’s Algorithm (DFS → G^T → DFS(G^T)). Totally it would take O(V+E) time complexity and O(V+E) space complexity.