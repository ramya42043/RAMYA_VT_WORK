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
class Derivedclass1:public Baseclass
{
	public:
	int val2;
	void childdisplay()
	{
		cout<<"enter value in child class1:";
		cin>>val2;
		cout<<"In child1 class value"<<val2<<endl;
	}
};
class Derivedclass2:public Derivedclass1
{
};
int main()
{
	Derivedclass1 DC1;
	/* Accesing Parent class member in child1*/
	DC1.display();
	Derivedclass2 DC2;
	/*Accessing parent and child class members in child2*/
	DC2.display();
	DC2.childdisplay();
}
