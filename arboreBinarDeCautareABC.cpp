#include <bits/stdc++.h>
using namespace std;
//#define st          first
//#define nd          second
#define pb          push_back
#define mkp         make_pair
#define lwbnd		lower_bound
#define upbnd		upper_bound
#define FOR(i,a,b)  for(int i=(a);i<=(b);++i)
#define FORS(i,a,b) for(int i=(a);i<(b);++i)
#define PII         pair<int,int>
#define VI          vector<int>
#define VPII        vector<PII>
#define ALL(x)      x.begin(),x.end()
#define SZ(x)       ((int)(x).size())
#define ll          long long
#define MOD         1000000007 //998244353
#define maxn        200005
const int INF=0x3f3f3f3f;

int n;

class Nod{
public:
    int info;
    Nod* st;
    Nod* dr;
    Nod(int val){
        info=val;
        st=nullptr;
        dr=nullptr;
    }
    ~Nod(){
        st=nullptr;
        dr=nullptr;
    }
};

class ABC{
    Nod* root;
public:
    ABC(){
        this->root=nullptr;
    }
    ABC(Nod* node){
        this->root=node;
    }
    ABC(int info){
        Nod* adder=new Nod(info);
        this->root=adder;
    }
    void insert(int info){
        Nod* it=root;
        Nod* adder=new Nod(info);
        if(it==nullptr)
        {
            root=adder;
            return;
        }
        while((it->st!=nullptr&&info<it->info)||(it->dr!=nullptr&&info>it->info))
        {
            if(info<it->info)
                it=it->st;
            else
                it=it->dr;
        }
        if(info<it->info)
            it->st=adder;
        else
            it->dr=adder;
    }
    void operator + (const int info){
        Nod* it=root;
        Nod* adder=new Nod(info);
        if(it==nullptr)
        {
            root=adder;
            return;
        }
        while((it->st!=nullptr&&info<it->info)||(it->dr!=nullptr&&info>it->info))
        {
            if(info<it->info)
                it=it->st;
            else
                it=it->dr;
        }
        if(info<it->info)
            it->st=adder;
        else
            it->dr=adder;
    }
    friend istream & operator >>(istream &in,ABC &arb){
        int info;
        in>>info;
        Nod* it=arb.getRoot();
        Nod* adder=new Nod(info);
        if(it==nullptr)
        {
            arb.root=adder;
            return in;
        }
        while((it->st!=nullptr&&info<it->info)||(it->dr!=nullptr&&info>it->info))
        {
            if(info<it->info)
                it=it->st;
            else
                it=it->dr;
        }
        if(info<it->info)
            it->st=adder;
        else
            it->dr=adder;

        return in;
    }

    int height(Nod* node){
        if(node!=nullptr)
            return 1+max(height(node->st),height(node->dr));
        return 0;
    }
    void frunze(Nod* node){
        if(node->st==nullptr&&node->dr==nullptr)
            cout<<node->info<<" at adress "<<&node<<'\n';
        if(node->st!=nullptr)
            frunze(node->st);
        if(node->dr!=nullptr)
            frunze(node->dr);
    }
    Nod* getRoot(){
        return this->root;
    }
};

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    //ABC arbore(new Nod(15)); // Cu constructor initializator
    //ABC arbore;
    ABC arbore(10);
    arbore.insert(20);
    arbore+2;
    cin>>arbore>>arbore;
    cout<<arbore.height(arbore.getRoot())<<" levels\n";
    arbore.frunze(arbore.getRoot());
    //    arbore.frunze(arbore.getRoot());
}
