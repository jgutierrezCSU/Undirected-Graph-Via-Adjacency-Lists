#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<cmath>
using namespace std;

#include "ugraph.h"

int main(){

    int N;
	cout << "-- OPTIONS--" << endl;
	cout << "addEdge:" << endl;
	cout << "removeEdge:" << endl;
	cout << "bfs:" << endl;
	cout << "distinctPaths:" << endl;
	cout << "printBridges:" << endl;
	cout << "printCC:" << endl;
	cout << "twoColoring:" << endl;
	cout << "printGraph:" << endl;





	cout << "Enter the size of the adjacency list: " ;
	cin >> N;
	//constructor resizes Adj, parents, stamps, distance and colors to the size N
	Ugraph ag(N);
	string command;
	while(cin >> command){
		if(command == "addEdge"){
			int u, v;
			cin >> u >> v;
            ag.addEdge(u, v);

		}else if(command == "removeEdge"){
			int u, v;
			cin >> u >> v;
			ag.removeEdge(u, v);
		}else if(command == "bfs"){
			int s;
			cin >> s;
			cout << "BFS on " << s << endl;
			ag.bfs(s);
		}else if(command == "dfs"){
			cout << "DFS" << endl;
			ag.dfs();
		}else if(command == "distinctPaths"){
			int u, v;
			cin >> u >> v;
			cout << "Are there two distinct paths between nodes " << u << " and " << v << "?" << endl;
			bool res = ag.distinctPaths(u, v);
			if(res)
				cout << "There are two distinct paths between nodes " << u << " and " << v << "." << endl;
			else
				cout << "There are NO two distinct paths between nodes " << u << " and " << v << "." << endl;
		}else if(command == "printBridges"){
			cout << "Bridge edges of the graph are:" << endl;
			ag.printBridges();
		}else if(command == "printCC"){
			cout << "Connected components of the graph are:" << endl;
			ag.printCC();
		}else if(command == "twoColoring"){
			bool res = ag.twoColoring();
			if(res)
				cout << "Two-coloring is possible in this graph." << endl;
			else
				cout << "Two-coloring is NOT possible in this graph." << endl;
		}else if(command == "printGraph"){
			cout << "Adjacency lists of the graph are:" << endl;
			ag.printGraph();
		}else{
			cerr << "ERROR: the command " << command << " is not found." << endl;
		}
	}//while
  return 0;
}
