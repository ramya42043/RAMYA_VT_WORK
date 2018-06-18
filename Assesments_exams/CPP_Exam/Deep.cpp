#include<iostream>
using namespace std;

class deep_copy
{
	int data1,data2,*ptr;
	public:

	deep_copy()
	{
		ptr=new int ;
	}
	void setdata(int value1, int value2,int value3)
	{
		data1=value1;
		data2=value2;
		*ptr=value3; 
	}
	void showdata()
	{
		cout << "data1="<<data1<<"\ndata2="<<data2<<"\nptr="<<*ptr<<"\n";
	}
	deep_copy(deep_copy &ref)
	{
		this->data1=ref.data1;
		this->data2=ref.data2; 
		this->ptr=new  int;
		*ptr=*(ref.ptr);
	}
	~deep_copy()
	{
		delete ptr;
	}	
};

int main()
{
	deep_copy obj1;
	obj1.setdata(10,20,30);
	deep_copy obj2=obj1; 
	obj1.showdata();
	obj2.setdata(1,2,3);
	cout<<"After setting Obj2 it will not effecting on obj1"<<endl;
	obj1.showdata();
	cout<<endl;
	obj2.showdata();
return 0;
}

