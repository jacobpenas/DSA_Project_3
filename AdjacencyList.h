#pragma once
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

class AdjacencyList
{
private:

	unordered_map<int, vector<int>> adjacencyList;

public:

    AdjacencyList() {}

// inserts start and destination into each others vectors to create an edge
	void addEdge(int start, int destination) {
        adjacencyList[start].push_back(destination);
        adjacencyList[destination].push_back(start);
	}

// gathers data from twitch.txt, the file containing the program's dataset
	void loadGraph(const string& filename) {
		ifstream inputFile(filename);
        string line;
        while (getline(inputFile, line)) {
            int start = stoi(line.substr(0, line.find(",")));
            int destination = stoi(line.substr(line.find(",") + 1, line.length() - to_string(start).length() - 1));
            addEdge(start, destination);
        }

        inputFile.close();
	}

// uses a queue to perform bfs, tracks number of nodes visited
    bool bfs(int start, int target, unordered_map<int, bool>& visited, int& nodesIterated) {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            nodesIterated++;
            if (current == target) {
                return true;
            }
            for (int neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        return false;
    }

// uses a stack to perform dfs, tracks number of nodes visited
    bool dfs(int start, int target, unordered_map<int, bool>& visited, int& nodesIterated) {
        stack<int> s;
        s.push(start);
        visited[start] = true;
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            nodesIterated++;
            if (current == target) {
                return true;
            }
            for (int neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        return false;
    }
};

