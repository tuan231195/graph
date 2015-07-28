/* 
 * File:   UF.cpp
 * Author: tuannguyen
 * 
 * Created on 5 July 2015, 8:47 PM
 */

#include "UF.h"


UF::UF(int N) {
    id = new int[N + 1];
    sz = new int[N + 1];
    for (int i = 0; i <= N; i++)
    {
        id[i] = i;
        sz[i] = 1;
    }
}

int UF::find(int p)
{
    while ( p != id[p])
    {
        p = id[p];
    }
    return p;
}

int UF::count()
{
    return cnt;
}

bool UF::connected(int p, int q)
{
    return find(p) == find(q);
}

void UF::join(int p, int q)
{
    int i = find(p);
    int j = find(q);
    if (i == j)
        return;
    if (sz[i] < sz[j])
    {
        id[i] = j;
        sz[j] += sz[i];
    }   
    else
    {
        id[j] = i;
        sz[i] += sz[j];
    }
    cnt --;
}