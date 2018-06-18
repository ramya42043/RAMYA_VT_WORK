#include<iostream>
using namespace std;

class shallowcopy
{
	int a,b;
	public:

	void setdata(int x, int y)
	{
		a=x;
		b=y;
	}

	void showdata()
	{
		cout << "data1="<<a<<"\ndata2="<<b<<"\n";
	}
	
};
int main()
{
	shallowcopy obj;
	obj.setdata(10,20);
	obj.showdata();
	shallowcopy obj1; 
	obj1=obj;	
	obj1.showdata();
	
return 0;
}
