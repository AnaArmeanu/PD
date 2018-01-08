#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream f("date.in");
ofstream g("date.out");

struct activ
{
    int st, sf, p;
};

void citire(int &n, vector<activ> &V)
{
    f>>n;
    activ x;
    for(int i=0;i<n;i++)
        {
            f>>x.st>>x.sf>>x.p;
            V.push_back(x);
        }
}

int binS(int st,int dr, vector<activ> V, int caut )//caut = timpul de inceput a activitatii curente
{
    if(st > dr)
        return -1;
    int m = (st+dr)/2;
    if(V[m].sf < caut)
    {
        return m;
    }
    else
        return binS(st,m-1,V,caut);
}
int main()
{
    int n;
    vector<activ> V;
    citire(n, V);

    vector<int> PD(n); //PD[i] = prof obtinut din planif. activ. 1..i
    vector<int> predecesor; //predecesor[i] = ultimul interval ce nu se intersecteaza cu intervalul i
    predecesor.assign(n,-1);
    //STIM: pred[0]=-1
    PD[0]=V[0].p;
    int maxim=0,poz;
    for(int i=1;i<n;i++)
    {
        predecesor[i] = binS(0,i,V,V[i].st);
        if(predecesor[i]!=-1)
            PD[i]=max(PD[i-1], V[i].p+PD[predecesor[i]]);
        else
        PD[i] = max(PD[i-1],V[i].p);
        if(maxim<PD[i])
        {
            maxim = PD[i];
            poz = i;
        }
    }
    cout<<"maxim:"<<maxim<<endl;
    vector<activ> Sol;
    activ S;
    int k=0;
    while(poz!=-1)
    {
        S.st=V[poz].st;
        S.sf=V[poz].sf;
        Sol.push_back(S);
        poz = predecesor[poz];
        k++;
    }
    for(int i=k-1;i>=0;i--)
    {
        cout<<Sol[i].st<<" "<<Sol[i].sf<<endl;
    }
    return 0;
}
