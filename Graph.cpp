

#include "Graph.h"
#include "UF.h"
#include "Heap.h"
#include <cfloat>
#include <stack>
using namespace std;

bool Edge::operator <(const Edge& e)
{
    return weight < e.weight;
}

bool Edge::operator >(const Edge& e)
{
    return weight > e.weight;
}

Graph::Graph(int size, bool dir)
{
    pq = new indexMinPQ<double>(size);
    adjList.resize(size + 1);
    fromVertex.resize(size + 1);
    edgList.resize(size + 1);
    distTo.reserve(size + 1);
    minWeight = 0;
    V = size;
    E = 0;
    marked.resize(size + 1);
    directed = dir;
}

Graph::~Graph()
{
    delete pq;
}

void Graph::addEdge(int from, int to, double weight)
{
    
    E ++;
    if (E == edges.capacity())
    {
        edges.reserve(2 * E);
    }
    Edge e;
    e.from = from;
    e.to = to;
    e.weight = weight;
    
    edges.push_back(e);
    adjList[from].push_back(to);
    edgList[from].push_back(e);    
    edgeSet.push_back(e);
    if (!directed)
    {
        adjList[to].push_back(from);
        edgList[to].push_back(e);
    }
}


vector<Edge> Graph::adjEdge(int vertex) {
    return edgList[vertex];
}


vector<int> Graph::adj(int vertex) {
    return adjList[vertex];
}

int Graph::edgeCount()
{
    return E;
}

void Graph::display()
{
    for (int i = 1; i <= V; i++)
    {
        cout << i << ": ";
        for (int j : adj(i))
        {
            cout << j << " ";
        }
        cout << endl;
    }
}


int Graph::vertexCount()
{
    return V;
}
bool Graph::hasEdge(int from, int to)
{
    return (find(adjList[from].begin(), adjList[from].end(), to) != adjList[from].end());
}

void Graph::dfs(int root)
{
    for (int i = 1; i <= V; i ++)
    {
        marked[i] = false;
    }
    dfsHelper(root);
}

void Graph::dfsHelper(int root)
{
    marked[root] = true;
    for (int i : adj(root))
    {
        if (!marked[i])
        {
            dfsHelper(i);
        }
        
    }
}

vector<int> Graph::reachable(int root)
{
    vector<int> temp;
    temp.reserve(V);
    dfs(root);
    for (int i = 1; i <= V; i++)
    {
        if (marked[i] && i != root)
        temp.push_back(i);
    }
    return temp;
}

void Graph::bfs(int root)
{
    for (int i = 1; i <= V; i ++)
    {
        marked[i] = false;
    }
    queue<int> q;
    marked[root] = true;
    q.push(root);
    while (!q.empty())
    {
        root = q.front();
        q.pop();
        cout << root << " ";
        for (int i : adj(root))
        {
            if (!marked[i])
            {
                q.push(i);
                marked[i] = true;
            }
        }
    }
}

void Graph::printAllPaths(int s, int d)
{
    for (int i = 1; i <= V; i ++)
    {
        marked[i] = false;
    }
    int * p = new int [V];
    printAllPathsUtil(s, d, p ,0);
    delete [] p;
}

void Graph::printAllPathsUtil(int u, int d, int path[], int index)
{
    marked[u] = true;
    path[index] = u;
    if ( u == d)
    {
        for (int i = 0; i <= index; i++)
        {
            cout << path[i] << " ";
        }
        cout << endl;
    }
    
    for (int j : adj(u))
    {
        if (!marked[j])
        {
            printAllPathsUtil(j, d, path, index + 1);
        }
    }
    
    marked[u] = false;
    
}
void Graph::displayCycle()
{
    stack<int> s;
    s.push(cyclePoint);
    int i = fromVertex[cyclePoint];
    while (i != cyclePoint)
    {
        s.push(i);
        i = fromVertex[i];
    }
    
    s.push(cyclePoint);
    while (!s.empty())
    {
        i = s.top();
        cout << i << " ";
        s.pop();
    }
}
bool Graph::hasCycle()
{
    
    for (int i = 1; i <= V; i ++)
    {
        for (int j = 1; j <= V; j ++)
        {
            marked[j] = false;
        }
        bool res = cycleUtil(i);
        if (res)
        {
            return true;
        }
    }
    return false;
}


bool Graph::cycleUtil(int root)
{
    marked[root] = true;
    bool res;
    for (int k : adj(root))
    {
        fromVertex[k] = root;
        if (!marked[k])
        {
            res =  cycleUtil(k);
            if (res)
            {
                return true;
            }
        }
        else
        {
            cyclePoint = k;
            return true;
        }
    }
    return false;
}


double Graph::dijkstraDistance(int s, int d)
{
    indexMinPQ<double> q(V);
    if (s == d)
    {
        return 0;
    }
    double *dist = new double[V + 1];
    for (int i = 1; i <= V; i++)
    {
        if (i != s)
        {
            dist[i] = DBL_MAX;
        }
    }
    dist[s] = 0;
    q.insert(s, 0);
    int u;
    while (!q.isEmpty())
    {
        u = q.delMin();
        for (Edge e : adjEdge(u))
        {
            
            int v = e.to;

            if (dist[v] > dist[u] + e.weight)
            {
                dist[v] = dist[u] + e.weight;
                if (!q.contains(v))
                    q.insert(v, dist[v]);
                else
                    q.change(v, dist[v]);
            }
        }
    }
    double rem = dist[d];
    delete [] dist;
    return rem;
}

double Graph::bellmanDistance(int s, int d)
{
    double *dist = new double[V + 1];
    dist[s] = 0;
    for (int i = 1; i <= V; i++)
    {
        if (i != s)
        {
            dist[i] = DBL_MAX;
        }
    }
    
    for (int i = 1; i <= V - 1; i++)
    {
        for (Edge e : edgeSet)
        {
            int v = e.to;
            int u = e.from;
            if (dist[v] > dist[u] + e.weight)
            {
                dist[v] = dist[u] + e.weight;
            }
        }
    }
    
    for (Edge e : edgeSet)
    {
        int v = e.to;
        int u = e.from;
        if (dist[v] > dist[u] + e.weight)
        {
            throw runtime_error("There exists a negative cycle in the graph!");
        }
    }
    
    double rem = dist[d];
    delete [] dist;
    return rem;
}


void Graph::allPairsShortest()
{
    double **c;
    c= new double*[V + 1];
    for (int i = 1; i <= V; i++)
    {
        c[i] = new double[V + 1];
        for (int j = 1; j <= V; j++)
        {
            if (j == i)
                c[i][j] = 0;
            else
                c[i][j] = DBL_MAX;
        }
    }
    for (int u = 1; u <= V; u++)
    {
        for (Edge e : adjEdge(u))
        {
            int v = e.to;
            c[u][v] = e.weight;
        }
    }
    for (int k = 1; k <= V; k++)
    {
        for (int i = 1; i <= V; i++)
        {
            for (int j = 1; j <= V; j++)
            {
                if (c[i][j] > c[i][k] + c[k][j])
                {
                    c[i][j] = c[i][k] + c[k][j];
                }
            }
        }
    }
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            cout << i << " -> " << j << ": ";
            if (c[i][j] != DBL_MAX)
            {
                cout << c[i][j];
            }
            else
            {
                cout << "They are not connected";
            }
            cout << endl;
        }
    }
    
    for (int i = 1; i <= V; i++)
    {
        delete [] c[i];
    }
    delete []c;
}

void Graph::krusKal()
{
    Heap<Edge> pq;
    for (Edge e: edgeSet)
        pq.enqueue(e);
    UF uf(V);
    while (!pq.isEmpty() && mst.size() < V)
    {
        Edge e = pq.dequeue();
        int u = e.from;
        int v = e.to;
        if (!uf.connected(u, v))
        {
            uf.join(v, u);
            mst.push(e);
            minWeight += e.weight;
        }
    }
    
    while (!mst.empty())
    {
        Edge e = mst.front();
        cout << e.from << " " << e.to << endl;
        mst.pop();
    }
    cout  << endl;
         
}

void Graph::prim()
{
    for (int i = 1; i <= V; i++)
    {
        marked[i] = false;
        distTo[i] = DBL_MAX;
    }
    
    for (int i = 1; i <= V; i++)
    {
        if (!marked[i])
            prim(i);
    }
    
    for (int v = 1; v < fromVertex.size(); v ++)
    {
        int to = v;
        int from = fromVertex[v];
        if (from != 0)
            cout << from << " " << to << endl;
    }
}
void Graph::prim(int s)
{
    distTo[s] = 0;
    pq->insert(s, distTo[s]);
    while (!pq->isEmpty())
    {
        int v = pq->delMin();
        scan(v);
    }
}

    
void Graph::scan(int v)
{
    marked[v] = true;
    for (Edge e: adjEdge(v))
    {
        int w;
        if (e.to == v)
        {
            w = e.from;
        }
        else
            w = e.to;
        if (marked[w])
            continue;
        if (e.weight < distTo[w])
        {
            distTo[w] = e.weight;
            fromVertex[w] = v;
            if (pq->contains(w))
            {
                pq->change(w, distTo[w]);
            }
            else
            {
                pq->insert(w, distTo[w]);
               
            }
        }
    }
}