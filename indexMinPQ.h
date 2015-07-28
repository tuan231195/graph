/* 
 * File:   indexMinPQ.h
 * Author: tuannguyen
 *
 * Created on 5 July 2015, 1:10 PM
 */

#ifndef INDEXMINPQ_H
#define	INDEXMINPQ_H
#include <stdexcept>
using namespace std;

template<class T>
class indexMinPQ {
public:
    indexMinPQ(int);
    bool isEmpty()
    {
        return (N == 0);
    }
    bool contains(int k);
    int size();
    int min();
    T minKey();
    int delMin();
    void insert(int k, T key);
    void change(int k, T key);
    
    ~indexMinPQ();
private:
    bool greater(int i , int j);
    void swap(int i, int j);
    void swim(int k);
    void sink(int k);
    int N;
    int * pq;
    int * qp;
    T * keys;
};

template<class T>
bool indexMinPQ<T>::contains(int k)
{
    return (qp[k] != -1);
}

template<class T>
indexMinPQ<T>::indexMinPQ(int size) 
{
    N = 0;
    pq = new int[size + 1];
    qp = new int [size + 1];
    keys = new T[size + 1];
    for (int i = 0; i <= size; i ++)
    {
        qp[i] = -1;
    }
}

template<class T>
indexMinPQ<T>::~indexMinPQ()
{
    delete [] pq;
    delete [] qp;
    delete [] keys;
}

template<class T>
void indexMinPQ<T>::sink(int i)
{
	while ( 2 * i <= N)
	{
		int k = 2 * i;
		if (k + 1 <= N && greater(k, k + 1))
		{
			k = k + 1;
		}
		if (greater(k, i))
		{
			break;
		}
		swap(k, i);
		i = k;
	}
}

template<class T>
void indexMinPQ<T>::insert (int k, T key)
{
    if (contains(k)) 
        throw runtime_error("Item is in the queue");
    N++;
    qp[k] = N;
    pq[N] = k;
    keys[k] = key;
    swim(N);
}

template<class T>
void indexMinPQ<T>::change(int k, T key)
{
    if (!contains(k)) 
        throw runtime_error("Item is not in the queue");
    keys[k] = key;
    swim(qp[k]);
    sink(qp[k]);
}


template<class T>
void indexMinPQ<T>::swim(int i)
{
	int k;
	while (i > 1)
	{
            k = i/2;
            if (greater(i, k))
            {
                break;
            }
            swap(k, i);
            i = k;
	}
}

template<class T>
bool indexMinPQ<T>::greater(int i, int j)
{
    return keys[pq[i]] > keys[pq[j]];
}

template<class T>
void indexMinPQ<T>::swap(int i, int j)
{
    int temp = pq[i]; 
    pq[i] = pq[j];
    pq[j] = temp;
    qp[pq[i]] = i;
    qp[pq[j]] = j;
    
};


template<class T>
int indexMinPQ<T>::size()
{
    return N;
}

template<class T>
int indexMinPQ<T>::min()
{
    if (N == 0)
        throw runtime_error ("No item in the queue");
    return pq[1];
}

template <class T>
T indexMinPQ<T>::minKey()
{
     if (N == 0)
        throw runtime_error ("No item in the queue");
    return keys[pq[1]];
}

template<class T>
int indexMinPQ<T>::delMin()
{
      if (N == 0)
        throw runtime_error ("No item in the queue");
      int min = pq[1];
      swap(1, N--);
      sink(1);
      qp[min] = -1;
      pq[N + 1] = -1;
      return min;
}

#endif	/* INDEXMINPQ_H */

