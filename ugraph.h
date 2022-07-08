#include<string>
#include<iostream>
#include <vector>
using namespace std;

#include "timestamp.h"
#ifndef UGRAPH_H
#define UGRAPH_H

struct edge{
	int neighbor; // adjacent node
	int w;
	edge(){
		neighbor = 0;
		w = 0;
    }
	edge(int i, int j){
		neighbor = i;
		w = j;
    }
};

class Ugraph{
public:
	Ugraph(int N);
	void bfs(int s);
	void dfs();
	void dfsVisit(int u, int &t);
	void printGraph();
	void addEdge(int u, int v);
	void addEdge(int u, int v, int weight);
	// for Project 3
	void removeEdge(int u, int v);
	bool distinctPaths(int u,int v);
	void printBridges();
	void printCC();
	bool twoColoring();

	//Problem 1
	bool sameCycle(int s, int r);
	
    //Problem 2.
	int longestCycle(int s);
    void longestDfs(int u, int& max, int sourceV);
	
    //Problem 3
	bool twoPaths(int s, int r);
	
    //Problem 4
	bool isOnPath(int s, int r, int q);//returns true if q is on the shortest path from s to r

private:
    void bfsAvoidPrint(int s);
    void dfsPrintBridges(int v, int& timer, int p = -1);
    void dfsForPrintCC(int &currentID,vector<int>&ID);
    bool bfsForTwoColoring(int pos);
    void dfsForVisitCC(int u, int &t, vector<int>&ID, int &currentID);

private:
	vector< vector<edge> > Adj; //adjacency lists of the graph 
	vector<int> distance; //for BFS and DFS
	vector<int> parents; //for BFS and DFS
	vector<char> colors; //for DFS
	vector<TimeStamp> stamps; //for DFS: stamps[v].d returns discovery time of v, and stamps[v].f finishing time.
    int size;
};

#endif
