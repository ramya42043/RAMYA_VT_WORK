#include<iostream>
using namespace std;
class Sample
{
int val;
public:
	int setval(void);
		/*{
			cout<<"set the value:";
			cin>>val;
		}*/
	int getval(void);
		/*{
			cout<<"value is:"<<val<<endl;
		}*/
};
inline int Sample::setval(void)
		{
			cout<<"set the value:";
			cin>>val;
		}
inline int Sample::getval(void)
		{
			cout<<"value is:"<<val<<endl;
		}
int main()
{
	Sample obj;
	obj.setval();
	obj.getval();
}
