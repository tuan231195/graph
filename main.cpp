/* 
 * File:   main.cpp
 * Author: tuannguyen
 *
 * Created on 6 July 2015, 11:31 AM
 */

#include <cstdlib>

#include "Graph.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Graph g(5, false);
    g.addEdge(1, 2, 4);
    g.addEdge(2, 3, 5);
    g.addEdge(4, 5, 2);
    g.addEdge(5, 2, 3);
    
    g.krusKal();
    cout << endl;
    g.prim();
    return 0;
}

