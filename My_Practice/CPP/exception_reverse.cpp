#include<iostream>
using namespace std;

class Base 
{

};
class Derived: public Base 
{

};
int main()
{
        Base b;
        Derived d;
        try 
        {
                throw d;
        }
        catch(Base b)
        {
             cout<<"Caught Base Exception"<<endl;
        }       
        catch(Derived d) {
                cout<<"Caught Derived Exception"<<endl;
        }
        return 0;
}

