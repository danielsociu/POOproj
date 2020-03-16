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
class ABC;

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
    
    void deleter(int val){
        Nod* father=root;
        Nod* it=root;
        while(it->info!=val){
            father=it;
            if(val<it->info)
                it=it->st;
            else
                it=it->dr;
            if(it==nullptr)
                break;
        }
        if(it==nullptr){
            cout<<"Element not found\n";
            return;
        }
        /*
         * Deci daca exista nodul din dreapta, vom adauga toate
         * nodurile din stanga de la cel sters(it) la
         * extremitatea stanga a nodului din dreapta lui it
         * altfel, pur si simplu tatal va pointa la nodul din stanga
         */
        if(it->dr!=nullptr){
            Nod* nxt=it->dr;
            while(nxt->st!=nullptr)
                nxt=nxt->st;
            nxt->st=it->st;
            if(father!=it){
                if(father->st==it)
                    father->st=it->dr;
                else
                    father->dr=it->dr;
            }else{
                this->root=it->dr;
            }
        }
        else if(father!=it){
            if(father->st==it)
                father->st=it->st;
            else
                father->dr=it->st;
        }else{
            this->root=it->st;
        }
        delete it;
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
    void adaugaN(int n){
        int val;
        for(;n--;){
            cin>>val;
            this->insert(val);
        }
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
    void preordine(ostream &out,Nod *node){
        if(node!=nullptr){
            out<<node->info<<' ';
            preordine(out,node->st);
            preordine(out,node->dr);
        }
    }
    void inordine(ostream &out,Nod *node){
        if(node!=nullptr){
            inordine(out,node->st);
            out<<node->info<<' ';
            inordine(out,node->dr);
        }
    }
    void postordine(ostream &out,Nod *node){
        if(node!=nullptr){
            postordine(out,node->st);
            postordine(out,node->dr);
            out<<node->info<<' ';
        }
    }
    friend ostream & operator <<(ostream &out,ABC &arb){
        out<<"Preordine: ";
        arb.preordine(out,arb.root);
        out<<'\n';
        out<<"Inordine: ";
        arb.inordine(out,arb.root);
        out<<'\n';
        out<<"Postordine: ";
        arb.postordine(out,arb.root);
        out<<'\n';
        return out;
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
    ABC arbore(15);
    arbore.insert(20);
    arbore+2;
    cin>>arbore;
    arbore.adaugaN(3);
    cout<<arbore.height(arbore.getRoot())<<" levels\n";
    arbore.frunze(arbore.getRoot());
    cout<<arbore;
    arbore.deleter(15);
    cout<<arbore;
    //    arbore.frunze(arbore.getRoot());
}
