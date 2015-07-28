#include <iostream>
#include <vector>
using namespace std;


#ifndef __HEAP__
#define __HEAP__

template<class T>
class Heap
{
public:
	void sink(int i);
	void swim(int i);
	void enqueue(T);
	T dequeue();
	void display();
        bool isEmpty()
        {
            return elements.size() == 0;
        }
private:
	vector<T> elements;
};


template<class T>
void Heap<T>::sink(int i)
{
	while ( 2 * i + 1< elements.size())
	{
		int k = 2 * i + 1;
		if (k + 1 < elements.size() && elements[k] > elements[k + 1])
		{
			k = k + 1;
		}
		if (elements[k] > elements[i] )
		{
                        
			break;
		}
		swap(elements[k], elements[i]);
		i = k;
	}
}

template<class T>
void Heap<T>::swim(int i)
{
	int k;
	while (i/2 >= 0)
	{
            if (i == 0)
                break;
            k = i/2;
            if (elements[k] < elements[i] )
            {
                break;
            }
            swap(elements[k], elements[i]);
            i = k;
	}
}

template<class T>
void Heap<T>::enqueue(T value)
{
    elements.push_back(value);
    if ( elements.size() == elements.capacity())
    {
        elements.reserve(2 *  elements.size());
    }
    swim(elements.size() - 1);
}

template<class T>
T Heap<T>::dequeue()
{
    swap(elements[0], elements.back());
    T value = elements.back();
    elements.pop_back();
    sink(0);
    return value;
}

template<class T>
void Heap<T>::display()
{
    for (int i = 0; i < elements.size(); i++)
    {
        cout << elements[i] << " ";
    }
    cout << endl;
}

#endif

