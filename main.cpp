#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include "AdjacencyList.h"
using namespace std;

int main() {

	cout << "Project 3" << endl << "Name: Jacob Pena" << endl << endl;

	cout << "This program uses a SNAP dataset with 168,113 nodes and 6,797,557"
		<< "\nedges. Each node corresponds to a User ID on twitch.tv, a popular"
		<< "\nstreaming website. Each edge corresponds to a mutual follow relationship"
		<< "\nbetween those nodes." << endl << endl;

	cout << "The purpose of this program is to compare BFS and DFS traversal algorithms."
		<< "\nThe user inputs a starting node and a destination node. Afterwards, the"
		<< "\nprogram will search for the destination node, beginning from the start"
		<< "\nnode, through both BFS and DFS. It will then compare the two search"
		<< "\nmethods in terms of time and number of nodes iterated through before"
		<< "\nthe destination was found." << endl << endl;

	AdjacencyList graph;
	graph.loadGraph("twitch.txt");
	int start, destination;
	string loop = "y";

	while (loop == "y") {

		string input1, input2;

		// input validation for starting node
		while (true) {
			bool valid1 = true;
			cout << "Please enter a start ID (ranging from 0 to 168112): ";
			getline(cin, input1);
			for (int i = 0; i < input1.length(); i++) {
				if (!isdigit(input1[i]))
					valid1 = false;
			}
			if (valid1 && stoi(input1) >= 0 && stoi(input1) <= 168112) {
				start = stoi(input1);
				break;
			}
			cout << "Start ID invalid. Please try again." << endl;
		}

		// input validation for target node
		while (true) {
			bool valid2 = true;
			cout << "Please enter a destination ID (ranging from 0 to 168112): ";
			getline(cin, input2);
			for (int i = 0; i < input2.length(); i++) {
				if (!isdigit(input2[i]))
					valid2 = false;
			}
			if (valid2 && stoi(input2) >= 0 && stoi(input2) <= 168112) {
				destination = stoi(input2);
				break;
			}
			cout << "Destination ID invalid. Please try again." << endl;
		}

		unordered_map<int, bool> visited;
		int bfsNodes = 0, dfsNodes = 0;

		// performs bfs, tracks time elapsed
		auto bfsStart = chrono::high_resolution_clock::now();
		bool bfsSearch = graph.bfs(start, destination, visited, bfsNodes);
		auto bfsDone = chrono::high_resolution_clock::now();
		auto bfsTime = chrono::duration_cast<chrono::milliseconds>(bfsDone - bfsStart);

		visited.clear();

		// performs dfs, tracks time elapsed
		auto dfsStart = chrono::high_resolution_clock::now();
		bool dfsSearch = graph.dfs(start, destination, visited, dfsNodes);
		auto dfsDone = chrono::high_resolution_clock::now();
		auto dfsTime = chrono::duration_cast<chrono::milliseconds>(dfsDone - dfsStart);

		// output bfs results
		cout << endl << "BFS:" << endl;
		if (bfsSearch) {
			cout << "\tDestination found!" << endl;
		}
		else {
			cout << "\tDesination not found." << endl;
		}
		cout << "\tTime elapsed: " << bfsTime.count() << " milliseconds" << endl
			<< "\tNumber of nodes iterated through: " << bfsNodes << endl << endl;

		// output dfs results
		cout << "DFS:" << endl;
		if (dfsSearch) {
			cout << "\tDestination found!" << endl;
		}
		else {
			cout << "\tDesination not found." << endl;
		}
		cout << "\tTime elapsed: " << dfsTime.count() << " milliseconds" << endl
			<< "\tNumber of nodes iterated through: " << dfsNodes << endl << endl;

		// outputs time comparison between bfs and dfs
		if (bfsTime.count() < dfsTime.count()) {
			cout << "BFS completed the search " << dfsTime.count() - bfsTime.count()
				<< " milliseconds quicker than DFS" << endl;
		}
		else if (bfsTime.count() > dfsTime.count()) {
			cout << "DFS completed the search " << bfsTime.count() - dfsTime.count()
				<< " milliseconds quicker than BFS" << endl;
		}
		else {
			cout << "BFS and DFS took the same amount of time" << endl;
		}

		// outputs comparison between number of nodes passed through
		if (bfsNodes < dfsNodes) {
			cout << "BFS completed the search in " << dfsNodes - bfsNodes
				<< " fewer node visitations than DFS" << endl;
		}
		else if (bfsNodes > dfsNodes) {
			cout << "DFS completed the search in " << bfsNodes - dfsNodes
				<< " fewer node visitations than BFS" << endl;
		}
		else
			cout << "BFS and DFS completed the search with the same number of node visitations." << endl;

		cout << endl << "Would you like to continue? Input 'y' to continue or any other character to quit.\n";
		getline(cin, loop);
		cout << endl << endl;

	}

	return 0;
}
