# DSA_Project_3
This program is based off of a SNAP (Stanford Network Analysis Project) dataset. This dataset
is a social network of twitch users, implemented as a graph where each node is a reference to 
a user ID and each edge is a mutual follower. It can be found here: 
https://snap.stanford.edu/data/twitch_gamers.html. 

The purpose of this program is to compare BFS and DFS in a graph. With this dataset, the graph 
has over 160,000 nodes and over 6,000,000 edges. The nodes are numbered 0-168112, though these 
are not the actual user IDs, only placeholder or reference values.

The user inputs a start node and a destination, or target node. The program will then execute
by performing both bfs and dfs, starting with the start node, in search of the target node.
It tracks both how much time each algorithm takes and how many nodes it must iterate through
before finding the target.
