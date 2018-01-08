#include <iostream>
#include<vector>
#include<fstream>
using namespace std;

ifstream f("date.in");
ofstream g("date.out");

void citire(vector<pair<int,int>> &piese, int &n)
{
    f>>n;
    pair<int,int> a;
    for(int i=0;i<n;i++)
    {
        f>>a.first>>a.second;
        piese.push_back(a);
    }
}
int main()
{

    vector<pair<int,int>> piese; //vector de piese
    int n;
    citire(piese, n);
    vector<int> L,Linversat; //L[i] = lg maxima a unui subsir cresc ce are piese[i] ca ultim element (din principiile progr. dinam.)
     //Linversat[i] = lg maxima a unui subsir cresc ce are piese[i] ROTIT ca ultim element (din principiile progr. dinam.)

     L.assign(n,1); //n inturi cu valoare 1
     Linversat.assign(n,1); //n inturi cu valoare 1
     //STIM:     L[0]=Linversat[0]=1;


     vector<int> succesor;
     succesor.assign(n,0);
     vector<int> succesorI;
     succesorI.assign(n,0);
     int i,j;//mereu j porneste de la i-1
     int x;
     int vmax = 0; //ca sa stiu care e valoarea sirului maxim
     int poz_max;//ultimul element din sirul maxim
     int poz_maxI;//ultimul element din sirul maxim cu el inversat
     for(i=1;i<n;i++)
     {
         j = i-1;
         while(j>=0)
            {
                //calculez L[i]
                if(piese[j].second == piese[i].first)
                {
                    x=max(L[i],L[j]+1);//daca a luat la alt j o valoare mai mare
                    if(x > L[i])
                    {
                        succesor[i] = j;
                    }
                    L[i] = x;
                    if(x > vmax)
                    {
                        vmax = x;
                        poz_max = i;
                    }
                }

                //de aici vine cazul cu rotirea
               /* if(piese[j].first == piese[i].first)
                {
                    x =  max(L[i],Linversat[j]+1);//in caz de s-a intrat pe primul if, sau a luat la alt j o valoare mai mare
                    if(x > L[i])
                    {
                        succesor[i] = j;
                    }
                    L[i] = x;
                    if(x > vmax)
                    {
                        vmax = x;
                        poz_max = i;
                    }
                }

                //calculez Linversat[i]
                if(piese[j].second == piese[i].second)
                {
                    x = max(Linversat[i],L[j] + 1);
                    if(x > Linversat[i])
                    {
                        succesorI[i]=j;
                    }
                    Linversat[i] = x;
                    if(x > vmax)
                    {
                        vmax = x;
                        poz_maxI = i;
                    }
                }
                if(piese[j].first == piese[i].second)
                {
                    x = max(Linversat[i],Linversat[j] + 1);
                    if(x > Linversat[i])
                    {
                        succesorI[i]=j;
                    }
                    Linversat[i] = x;
                    if(x > vmax)
                    {
                        vmax = x;
                        poz_maxI = i;
                    }
                }*/
                j--;
            }
     }



    for(int o = 0;o<n;o++)
        cout<<L[o]<<" ";
    cout<<endl;
        for(int o = 0;o<n;o++)
        cout<<Linversat[o]<<" ";

    //caut cate siruri maxime sunt
    int nr=0;
    for(i=0;i<n;i++)
    {
        if(L[i] == vmax)
            nr++;
        if(Linversat[i]==vmax)
            nr++;
    }
    cout<<endl;
    int vmax2 = vmax;
    vector<pair<int,int>> Solutie;// ca sa afisez in ordine
    if(L[poz_max] == vmax)
    {
        j = poz_max;
        while(vmax)
        {
            Solutie.push_back(piese[j]);
            j = succesor[j];
            vmax--;
        }
    }

    for(i=vmax2-1; i>=0;i--)
    {
        cout<<Solutie[i].first<<" "<<Solutie[i].second<<endl;
    }
    cout<<"\nSunt "<<nr<<" siruri de lungime maxima.";
    return 0;
}
