/* 
 * File:   Graph.h
 * Author: tuannguyen
 *
 * Created on 5 July 2015, 9:13 AM
 */

#ifndef GRAPH_H
#define	GRAPH_H

#include <iostream>
#include <map>
#include <queue>
#include <vector>

#include "indexMinPQ.h"
using namespace std;



class Edge
{
public:
    int from;
    int to;
    double weight;
    bool operator >(const Edge &);
    bool operator < (const Edge &);
};

class Graph
{
private:
    bool directed;
    indexMinPQ<double> *pq;
    vector<vector<int> > adjList;
    vector<vector<Edge> > edgList;
    vector <int> fromVertex;
    double minWeight;
    int V;
    int E;
    int cyclePoint;
    vector<Edge> edgeSet;
    vector<bool> marked;
    queue<Edge> mst;
    vector<double> distTo;
    void dfsHelper(int);
    void printAllPathsUtil(int u, int d, int path[], int index);
    bool cycleUtil(int);
    void scan(int v);
    void prim(int s);
public:
    Graph(int, bool);
    ~Graph();
    vector<Edge> edges;
    void display();
    void dfs(int);
    bool hasCycle();
    void displayCycle();
    void printAllPaths(int s, int d);
    void bfs(int);
    vector<int> reachable(int);
    double dijkstraDistance(int s, int d);
    vector<Edge> adjEdge(int);
    vector<int> adj(int);
    void addEdge(int from, int to, double weight);
    int vertexCount();
    int edgeCount();
    bool hasEdge(int from, int to);
    double bellmanDistance(int s, int d);
    void allPairsShortest();
    void krusKal();
    void prim();
};


#endif	/* GRAPH_H */

