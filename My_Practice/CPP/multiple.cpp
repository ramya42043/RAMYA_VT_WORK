#include<iostream>
using namespace std;
class Baseclass1
{
public:
	int val;
	void display()
	{
		cout<<"enter value in Base class1:";
		cin>>val;
		cout<<"In Base class1 "<<val<<endl;
	}
};
class Baseclass2
{
	public:
	int val2;
	void childdisplay()
	{
		cout<<"enter value in Base class2:";
		cin>>val2;
		cout<<"In Base class2 value"<<val2<<endl;
	}
};
class Derivedclass:public Baseclass1,public Baseclass2
{
};
int main()
{
	Derivedclass DC;
	/*Accessing parent and child class members in child2*/
	DC.display();
	DC.childdisplay();
}
