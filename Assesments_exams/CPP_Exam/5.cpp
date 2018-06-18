#include<iostream>
using namespace std;
class Time
{
	Time(int x,int y,int z)
	{
		cout<<x<<y<<z<<endl;
	}
};
int main()
{
Time T;
T(1,2,3);
}
