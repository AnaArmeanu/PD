#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <cstdio>
using namespace std;
const int max1=100;
ifstream f("date.in");
ofstream g("date.out");

int eval(string a, string b, int i, int j)
{
    if(a[i]==b[j])
        return 0;
    return 1;
}

int DLev(string a, string b)
{
    int c1,c2,c3;
    f>>c1>>c2>>c3;


    int n,m; //nr de caractere pentru a si b
    n = a.size();
    m = b.size();
    vector<vector<int>>dp(n+1); //matrice in care [i][j] e min dintre...; +1 pt bordare
    for(int i=0; i<n+1; i++)
    {
        dp[i].resize(m+1);//+1 pentru bordare
    }
    //pas de initializare; nu e nevoie sa initializez totul cu 0, stl face deja asta
    for(int i=0; i<n+1; i++)
    {
        dp[i][0] = i;
    }
    for(int i=0; i<m+1; i++)
    {
        dp[0][i] = i;
    }

    for(int i=1; i<n+1; i++) //de la 1 pt ca poz 0 e deja completata
    {
        for(int j=1; j<m+1; j++)
        {
            dp[i][j] = min(dp[i-1][j]+c1, dp[i][j-1]+c2);
            dp[i][j] = min(dp[i][j], dp[i-1][j-1]+eval(a,b,i-1,j-1)*c3);//i-1 si j-1 ca sa vina literele i,j adica pe pozitiile i-1 si j-1
        }
    }
    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<m+1; j++)
            cout<<dp[i][j]<<" ";
        cout<<endl;
    }
    g<<dp[n][m]; // distanta
    //refac drumul
    //idee: creez o stiva de stringuri ca sa nu parcurg de 2 ori matricea

    stack<string> Solutie;
    string S;
    int i=n,j=m;
    while(i!=0 || j!=0)
    {
        if(dp[i][j] == dp[i-1][j]+c1) //stergere
        {
            S.erase(0,S.size());
            S+="stergere ";
            S+=a[i-1];
            S+=" de pe pozitia(din sirul initial) ";
            char poz[4];
            snprintf(poz, sizeof(poz),"%d",i-1);
            S += poz;

            Solutie.push(S);
            i--;
        }
        else
        {
            if(dp[i][j] == dp[i][j-1]+c2) //inserare
            {
                S.erase(0,S.size());
                S+="inserare ";
                S+=b[j-1];
                S+=" pe pozitia(din sirul initial) ";
                char poz[4];
                snprintf(poz, sizeof(poz),"%d",i);
                S += poz;

                Solutie.push(S);
                j--;
            }
            else
            {
                if(eval(a,b,i-1,j-1))//daca se produce vreo modificare
                {
                S.erase(0,S.size());
                S+="inlocuire ";
                S+=a[i-1];
                S+=" pe pozitia(din sirul initial) ";
                char poz[4];
                snprintf(poz, sizeof(poz),"%d",i-1);
                S += poz;
                S+=" cu ";
                S+= b[j-1];

                Solutie.push(S);
                i--;
                j--;
                }
                else{i--;j--;}
            }
        }
    }
    //afisez
    while(Solutie.size())
    {
        cout<<Solutie.top()<<endl;
        g<<Solutie.top()<<endl;
        Solutie.pop();
    }
}
int main()
{
    string a,b;
    f>>a>>b;
    cout<<a<<" "<<b<<endl;
    DLev(a,b);

    return 0;
}
