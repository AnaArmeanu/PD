#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<stdlib.h>
using namespace std;

ifstream f("date.in");
ofstream g("date.out");

void dinam (int n, int k, vector<vector<int>> V)
{
    vector<vector<int>> D(n+1); //n+1 linii(bordare) si k coloane
    for(int i=1; i<=n; i++)
    {
        D[i].resize(k+1);

    }

    for(int j=0; j<V[1].size(); j++)
        if(V[1][j]<=k)
            D[1][V[1][j]]=j;//pozitia in vector

    for(int i=2; i<=n; i++) //----
    {
        for(int h=1; h<V[i].size(); h++) //----m ptc trece prin fiecare element al sirului
        {
            for(int j=0; j<=k; j++) //k
            {

                if(j-V[i][h]>0)
                    if(D[i-1][j-V[i][h]]>0)
                    {
                        D[i][j]=h;
                    }
            }

        }

    }//=> m*k

    for(int i=1; i<=n; i++)
    {
        for(int j=0; j<=k; j++)
        {
            cout<<D[i][j]<<" ";

        }
        cout<<endl;
    }
    if(D[n][k]==0)
    {
        cout<<"Nu se poate forma suma.";
        g<<"Nu se poate forma suma.";
    }
    else
    {
        int i=n;
        while(k!=0)
        {
            cout<<V[i][D[i][k]]<<" ";
            g<<V[i][D[i][k]]<<" ";
            k=k-V[i][D[i][k]];
             i--;
        }
    }
}

int main()
{
    int n,k;
    f>>n>>k;
    vector<vector<int>>V(n+1);
    string numere,nr;
    getline(f,numere); //citeste endl si trece pe linia cu primul sir
    for(int i=1; i<=n; i++)
    {
        V[i].push_back(0);//ca fiecare nr sa fie pe pozitia lui(sa nu am pozitia 0)
        getline(f,numere);
        cout<<numere<<endl;
        int k=0;
        int ultim=0;
        while(numere[k-1]!='\0')//ca sa iau si ultimul nr
        {
            if(numere[k]==' '||numere[k]=='\0')
            {
                nr.assign(numere,ultim,k-ultim);
                ultim = k+1;
                int x ;
                sscanf(nr.c_str(), "%d", &x);
                V[i].push_back(x);

            }
            k++;
        }
    }
    //gata citirea
    dinam(n,k,V);

    return 0;
}
