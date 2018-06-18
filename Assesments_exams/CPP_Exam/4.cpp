#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

template <class T>
inline void print (const T& a, const char* x="")
{
    typename T::const_iterator pos;

    std::cout << x;
    for (pos=a.begin(); pos!=a.end(); ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << std::endl;
}


template <class T>
inline void insert (T& a, int first, int last)
{
    for (int i=first; i<=last; ++i) {
        a.insert(a.end(),i);
    }
}

using namespace std;

int main()
{
    vector<int> a;

    insert(a,1,9);
    
    print(a,"elements:");

   	
}
