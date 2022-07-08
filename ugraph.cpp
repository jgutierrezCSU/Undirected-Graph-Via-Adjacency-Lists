//jesus gutierrez
//CSCI 311
//PROJECT 3
//SPRING 2019
//UGRAPH.CPP
#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
using namespace std;

#include "ugraph.h"

Ugraph::Ugraph(int N){

	size = N;
	
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);

}//default

void Ugraph::addEdge(int u, int v)
{
    Adj[u].push_back(edge(v, 0));
    Adj[v].push_back(edge(u, 0));
}

void Ugraph::addEdge(int u, int v, int weight){
	Adj[u].push_back(edge(v, weight));
    Adj[v].push_back(edge(u, weight));

}

bool Ugraph::sameCycle(int s, int r)
{
    bfs(s);

    if (distance[r] != INT_MAX) {
        int cur = r;
        bool stop = false;
        while(!stop) {
            for(int i = 0; i < (int)Adj[parents[cur]].size(); i++){
                if (Adj[parents[cur]][i].neighbor == cur) {
                    Adj[parents[cur]][i].w = -1;
                    cur = parents[cur];
                    break;
                }
            }
            if (cur == s)
                stop = true;
        }
    }

    bfs(r);

    if(distance[s] != INT_MAX)
        return true;

    return false;
}



void Ugraph::longestDfs(int u, int& max, int sourceV)
{
    for(int i = 0; i < (int)Adj[u].size(); i++){
        int v = Adj[u][i].neighbor;
        if(colors[v] == 'W'){
            parents[v] = u;
            colors[v] = 'G';
            distance[v] = distance[u] + 1;
            longestDfs(v, max, sourceV);
            //aq.push(v);
        } else if(colors[v] == 'G' && v == sourceV){
            //distance[u] += 1;
            if (distance[u] + 1 > max)
                max = distance[u] + 1;
        }
    }//for

    colors[u] = 'B';
}

bool Ugraph::twoPaths(int s, int r)
{
    bfs(s);

    if (distance[r] != INT_MAX) {
        int cur = r;
        bool stop = false;
        while(!stop) {
            int indexP = parents[cur];
            for(int i = 0; i < (int)Adj[indexP].size(); i++){
                if (Adj[indexP][i].neighbor == cur) {
                    Adj[indexP][i].w = -1;
                    cur = indexP;
                    break;
                }
            }
            if (cur == s)
                stop = true;
        }
    }

    bfs(s);

    for(int i = 0; i < Adj.size(); ++i) {
        for(int j = 0; j < (int)Adj[i].size(); j++){
            Adj[i][j].w = 0;
        }
    }

    if(distance[r] != INT_MAX)
        return true;

    return false;
}

bool Ugraph::isOnPath(int s, int r, int q)
{
    int min = INT_MAX;
    int minContainQ = INT_MAX;

    do {
        bfs(s);
        bool isContainQ = false;
        if (distance[r] != INT_MAX) {
            int cur = r;
            bool stop = false;
            while(!stop) {
                int indexP = parents[cur];
                for(int i = 0; i < (int)Adj[indexP].size(); i++){
                    if (Adj[indexP][i].neighbor == cur) {
                        if (indexP == q ||cur  == q)
                            isContainQ = true;
                        Adj[indexP][i].w = -1;
                        cur = indexP;
                        break;
                    }
                }
                if (cur == s)
                    stop = true;
            }
            if (isContainQ) {
                if (minContainQ > distance[r])
                    minContainQ = distance[r];
            } else {
                if (min > distance[r])
                    min = distance[r];
            }
        }
    } while(distance[r] != INT_MAX);

    for(int i = 0; i < Adj.size(); ++i) {
        for(int j = 0; j < (int)Adj[i].size(); j++){
            Adj[i][j].w = 0;
        }
    }

    if (minContainQ != INT_MAX || min != INT_MAX)
        return minContainQ < min;

    return false;
}

void Ugraph::bfsAvoidPrint(int s)
{
    for(int i = 0; i < size; i++){
        distance[i] = INT_MAX;
        parents[i] = i;
    }//for
    distance[s] = 0;
    queue<int> aq;
    aq.push(s);
    while(!aq.empty()){
        int u = aq.front();
        aq.pop();

        for(int i = 0; i < (int)Adj[u].size(); i++){
            int v = Adj[u][i].neighbor;
            if(Adj[u][i].w == -1)
                continue;
            if(distance[v] == INT_MAX){
                distance[v] = distance[u] + 1;
                parents[v] = u;
                aq.push(v);

            }
        }//for
    }//while
}

void Ugraph::dfsPrintBridges(int v, int &timer, int p)
{
    colors[v] = 'G';
    stamps[v].d = stamps[v].f = timer++;
    for (int i = 0; i < Adj[v].size(); ++i)
    {
        int to = Adj[v][i].neighbor;
        if (to == p)
            continue;
        if (colors[to] == 'G')
            stamps[v].f = std::min(stamps[v].f, stamps[to].d);
        else
        {
            dfsPrintBridges(to, timer, v);
            stamps[v].f = std::min (stamps[v].f, stamps[to].f);
            if (stamps[to].f > stamps[v].d)
                cout << v << " " << to << endl;
        }
    }
}

void Ugraph::printGraph(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)Adj[i].size(); j++){
			int v = Adj[i][j].neighbor;
			cout << v << " " ;
		}//for j
		cout << endl;
	}

}//printGraph

void Ugraph::bfs(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        aq.pop();
        cout << u << " ";

		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
            if(Adj[u][i].w == -1)
                continue;
            if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);

			}
		}//for
	}//while
    cout << endl;
}//bfs

void Ugraph::dfs(){
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			dfsVisit(i, t);
		}//if
	}//for
    cout << endl;
}//dfs

void Ugraph::dfsVisit(int u, int &t){
	colors[u] = 'G';
    cout << u << " ";
	stamps[u].d = t;
	t++;

	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = u;
                colors[v] = 'G';
				dfsVisit(v, t);
            }
	}//for
    colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit	

int Ugraph::longestCycle(int s)
{
    for(int i = 0; i < size; i++){
        parents[i] = i;
        colors[i] = 'W';
    }

    int maxLenght = 0;

    for(int i = 0; i < size; i++){
        distance[i] = INT_MAX;
        parents[i] = i;
    }//for

    distance[s] = 0;
    colors[s] = 'G';

    longestDfs(s, maxLenght, s);

    return  maxLenght;
}

void Ugraph::removeEdge(int u, int v)
{
    for (int i = 0; i < Adj[u].size(); ++i) {
        if (Adj[u][i].neighbor == v) {
            Adj[u][i] = Adj[u][Adj[u].size() - 1];
            Adj[u].resize(Adj[u].size() - 1);
        }
    }

    for (int i = 0; i < Adj[v].size(); ++i) {
        if (Adj[v][i].neighbor == u) {
            Adj[v][i] = Adj[v][Adj[v].size() - 1];
            Adj[v].resize(Adj[v].size() - 1);
        }
    }
}
bool Ugraph::distinctPaths(int u,int v)
{
    vector<int> firstPath;
    vector<int> secondPath;

    bfsAvoidPrint(u);

    if (distance[v] != INT_MAX) {
        int cur = v;
        firstPath.push_back(v);
        bool stop = false;
        while(!stop) {
            for(int i = 0; i < (int)Adj[cur].size(); i++) {
                if (Adj[cur][i].neighbor == parents[cur]) {
                    Adj[cur][i].w = -1;
                    break;
                }
            }

            for(int i = 0; i < (int)Adj[parents[cur]].size(); i++){
                if (Adj[parents[cur]][i].neighbor == cur) {
                    firstPath.push_back(parents[cur]);
                    Adj[parents[cur]][i].w = -1;
                    cur = parents[cur];
                    break;
                }
            }
            if (cur == u)
                stop = true;
        }
    } else
        return false;

    bfsAvoidPrint(v);

    if(distance[u] != INT_MAX) {
        int cur = u;
        secondPath.push_back(u);
        bool stop = false;
        while(!stop) {
            for(int i = 0; i < (int)Adj[parents[cur]].size(); i++){
                if (Adj[parents[cur]][i].neighbor == cur) {
                    secondPath.push_back(parents[cur]);
                    Adj[parents[cur]][i].w = -1;
                    cur = parents[cur];
                    break;
                }
            }
            if (cur == v) {
                stop = true;
            }
        }
    } else
        return false;

    for(int i = firstPath.size() - 1; i >= 0; --i)
        cout << firstPath[i] << " ";
    cout << endl;

    for(int i = 0; i < secondPath.size(); ++i)
        cout << secondPath[i] << " ";
    cout << endl;

    for(int i = 0; i < Adj.size(); ++i) {
        for(int j = 0; j < (int)Adj[i].size(); j++){
            Adj[i][j].w = 0;
        }
    }

    return true;
}

void Ugraph::printBridges()
{
    int timer = 0;

    for(int i = 0; i < size; i++){
        parents[i] = i;
        colors[i] = 'W';
        stamps[i].d = 0;
        stamps[i].f = 0;
    }

    for(int i = 0; i < size; i++){
        if(colors[i] == 'W'){
            dfsPrintBridges(i, timer);
        }//if
    }//for
}
//// printCC
void Ugraph::printCC()
{
    int cur =0;
    int curID=0;
    vector<int>ID(size,0);
    dfsForPrintCC(curID,ID);
    while(cur != curID)
    {
        for(int i = 0; i < size; i++){
            if (ID[i] == cur)
                cout << i << " ";
        }
        cout << endl;
        cur++;
    }
}
// Check with tutor
void Ugraph::dfsForPrintCC(int &currentID,vector<int>&ID)
{
    for(int i = 0; i < size; i++){
        parents[i] = i;
        colors[i] = 'W';
    }//for   
    int t = 0;
    for(int i = 0; i < size; i++){
        if(colors[i] == 'W'){
            dfsForVisitCC(i, t,ID,currentID);
            currentID++;
        }//if
    }//for
}
void Ugraph::dfsForVisitCC(int u, int &t, vector<int>&ID, int &currentID){
    colors[u] = 'G';
    stamps[u].d = t;
    ID[u] = currentID;
    t++;
    for(int i = 0; i < (int)Adj[u].size(); i++){
            int v = Adj[u][i].neighbor;
            if(colors[v] == 'W')
            {
                parents[v] = u;
                colors[v] = 'G';
                ID[v] =currentID;
                dfsForVisitCC(v, t,ID,currentID);
            }
    }//for
    colors[u] = 'B';
    stamps[u].f = t;
    t++;
}//dfsVisit 
bool Ugraph::twoColoring()
{

    for(int i = 0; i < size; i++){
        parents[i] = i;
        colors[i] = 'W';
        distance[i] = INT_MAX;
    }

    for (int i = 0; i < size; i++)
        if (colors[i] == 'W')
            if (bfsForTwoColoring(i) == false) {
                return false;
            }

    return true;
}
bool Ugraph::bfsForTwoColoring(int src)
{
    colors[src] = 'G';
    queue <int> q;
    q.push(src);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int)Adj[u].size(); ++i) {
            if (Adj[u][i].neighbor == u)
                return false;
        }

        for (int v = 0; v < (int)Adj[u].size(); ++v)
        {
            int nv = Adj[u][v].neighbor;
            if (colors[nv] == 'W')
            {
                if(colors[u] == 'G')
                    colors[nv] = 'B';
                else if(colors[u] == 'B')
                    colors[nv] = 'G';
                q.push(nv);
            } else {
                for (int i = 0; i < (int)Adj[u].size(); ++i) {
                    if (Adj[u][i].neighbor == nv && colors[nv] == colors[u])
                        return false;
                }
            }
        }
    }

    return true;
}