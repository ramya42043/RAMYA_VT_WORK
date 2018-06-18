#include<bits/stdc++.h>
using namespace std;
  
int countFreq(string &pat, string &txt)
{
    int M = pat.length();
    cout<<"M:"<<M<<endl;
    int N = txt.length();
    cout<<"N:"<<N<<endl;
    int res = 0;
   
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    { 
        /* For current index i, check for 
           pattern match */
        int j;
        for (j = 0; j < M; j++)
            if (txt[i+j] != pat[j])
                break;
  
        // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        cout<<"j:"<<j<<endl;
        if (j == M)  
        {
           res++;
           j = 0;
        }
    }
    return res;
}
   
/* Driver program to test above function */
int main()
{
   string txt = "ramyamya";
   string pat = "mya";
   cout << countFreq(pat, txt)<<endl;
   return 0;
}
