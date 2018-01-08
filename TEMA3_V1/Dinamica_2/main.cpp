#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream f("date.in");
ofstream g("date.out");

void citire(int &n, int &m, vector<int>* &M, vector<int>* &A)
{
    f>>n>>m;
    cout<<n<<endl<<m<<endl;
    A = new vector<int>[n];
    M = new vector<int>[n+2];
    for(int i=0;i<n;i++)
    {
        A[i].assign(m,0);
        M[i].assign(m+2,0);
        if(i==n-1)
        {
            M[n].assign(m+2,0);
            M[n+1].assign(m+2,0);
        }

    }

    //citesc in A
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            {
                f>>A[i][j];
                M[i+1][j+1] = A[i][j];
            }
}

int main()
{
    int n,m;
    vector<int>*M;
    vector<int>*A; //A e matricea citita, M matricea cu sol. optima
    citire(n,m,M,A);

    //traseu optim ajunge in [i][j] = M[i][j]
    int i=0, j=0;
    for(int i=1;i<n+1;i++)
    {
        cout<<i<<endl;
        for(int j=1;j<m+1;j++)
        {
            cout<<A[i-1][j-1]<<" ";
            M[i][j] = A[i-1][j-1] + max(M[i-1][j],M[i][j-1]);
        }
        cout<<endl;
    }
    cout<<"Matricea subproblemelor: \n";
        for(int i=0;i<n+2;i++)
    {
        for(int  j= 0;j<m+2;j++)
            cout<<M[i][j]<<" ";
        cout<<endl;
    }

    cout<<"Suma maxima: "<<M[n][m]<<endl;
    vector<pair<int,int>> Sol;
    int k=-1;
    pair<int,int> aux;//Ca sa le afisez in ordinea corecta
    int x=n, y=m;
    while(x!=0 && y!=0)
    {
        k++;
        aux.first = x;
        aux.second = y;
        Sol.push_back(aux);
        if(M[x-1][y] > M[x][y-1])
        {
            x = x-1;
        }
        else
            y = y-1;
    }
    for(int i=k; i>=0 ; i--)
        cout<<Sol[i].first<<" "<<Sol[i].second<<endl;
    return 0;
}
