#include<iostream>
using namespace std;
class Baseclass
{
public:
	int val;
	void display()
	{
		cout<<"enter value in parent class:";
		cin>>val;
		cout<<"In parent class "<<val<<endl;
	}
};
class Derivedclass1:private Baseclass
{
public:
	int val2;
	Derivedclass1()
	{
	cout<<"Derived class constructor"<<endl;
	Baseclass::display();
	}
};
int main()
{
	Derivedclass1 b1;

}
