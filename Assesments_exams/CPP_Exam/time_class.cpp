#include<iostream>
using namespace std;
class Time
{
	int a,b,c;
	public:
		Time(int x,int y,int z)
		{
			a = x;
			b = y;
			c = z;
		}
		void sethour(int x)
		{
			a = x;
		}
		void setminute(int x)
		{
			b = x;
		}
		void setsecod(int x)
		{
			c = x;
		}
		void settime(int x,int y,int z)
		{
			a = x;
			b = y;
			c = z;
		}

		void print()
		{	
			cout<<"values:"<<a<<" "<<b<<" "<<c<<endl;
		}
};
int main()
{
	Time t(1,2,3);
	t.print();
	t.sethour(12);
	t.setminute(30);
	t.setsecod(15);
	t.print();
	t.settime(1,2,3);
	t.print
}
	
