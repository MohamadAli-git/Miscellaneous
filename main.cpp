#include <iostream>
#include <thread>
#include <string>
#include <math.h>
using namespace std;
int Factorization(int num ,char tag, int i );
void Threads(int n,int Nums[],char Tags[]);
int Fac[200][10];
int Count=0;
int NumsLevel[200];
int NumsLevelind=0;
int main(int argc, char *argv[])
{
    int threadnumber;
    int Nums[200];
    char Tags[200];
    string p=argv[1],p1,p2;
    p1=p.erase(0,1);
    p2=argv[2];
    if(p1.compare("t")==0){
        threadnumber=stoi(p2);
    }

    //cout << "pleas input tag and numbers" << endl;
    Count=-1;
    do
    {
        Count+=1;
        cout<<"Tag "<<Count<<": ";
        cin >>Tags[Count];
        cout<<"Number "<<Count<<": ";
        cin>>Nums[Count];
    }while(Nums[Count] != -1);
    cout <<"----------------------"<<endl<< "Starting Threads" << endl;
    Threads(threadnumber,Nums,Tags);
    cin>>Count;
    return 0;
}

int  Factorization(int num ,char tag, int TH )
{

    int index=1, Or=num;
// Print the number of 2s that divide n
    //cout << tag<<": " ;
    while (num % 2 == 0)
        {
            Fac[TH][index]=2;
            Fac[TH][0]=index;
            index+=1;
            //cout << 2 << " ";
            num = num/2;
        }

    // n must be odd at this point. So we can skip
    // one element (Note i = i +2)
    for (int i = 3; i <= (Or/2); i = i + 2)
    {
        // While i divides n, print i and divide n
        while (num % i == 0)
        {
            //cout << i << " ";
            Fac[TH][index]=i;
            Fac[TH][0]=index;
            index+=1;
            num = num/i;
        }
    }
    // This condition is to handle the case when n
    // is a prime number greater than 2
    if (num > 2){
        Fac[TH][index]=num;
        Fac[TH][0]=index;
        index+=1;
    }
        NumsLevel[NumsLevelind]=TH;
        NumsLevelind+=1;
  return 0;
}


void Threads(int n,int Nums[],char Tags[])
{
    if(n>=Count)
        n=Count;
    thread threads[n];
    int C2=0;
    if(Count%n==0)
        C2=(Count/n)-1;
    else
        C2=Count/n;
    for(int C1=0; C1<=C2; C1++){
        for (int i = 0; i < n; i++)
        {
          //thread (Factorization(Nums[i],Tags[i]), i + 1);
            if((C1*n+i)<=Count)
                threads[i] = thread(Factorization,Nums[i+(C1*n)],Tags[i+(C1*n)],i+(C1*n));
        }

        for (auto& th : threads) {
            th.join();
        }
    }
        for (int i = 0; i < NumsLevelind; i++)
        {
            cout<<Tags[NumsLevel[i]]<<": ";
            for (int j = 1; j < Fac[NumsLevel[i]][0]+1; j++)
            {
               cout<<Fac[NumsLevel[i]][j]<<" ";
            }
            cout<<endl;
        }
}



