#include <bits/stdc++.h>
using namespace std;
#define ST          first
#define ND          second
#define PB          push_back
#define MKP         make_pair
#define LWBND		lower_bound
#define UPBND		upper_bound
#define FOR(i,a,b)  for(int i=(a);i<=(b);++i)
#define FORS(i,a,b) for(int i=(a);i<(b);++i)
#define ALL(x)      x.begin(),x.end()
#define SZ(x)       ((int)(x).size())
#define MOD         1000000007 //998244353
#define MAXN        200005
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<PII> VPII;
const int INF=0x3f3f3f3f;

class Matrice {
    int n;
    int **a;
    void alocate(int n){
        try{
            this->a=new int*[n+1];
            FOR(i,0,n)
                this->a[i]=new int[n+1];
        }
        catch(bad_alloc& err){
            cout<<"Allocation Failure"<<'\n';
            cout<<err.what()<<'\n';
            exit(EXIT_FAILURE);
        }
    }
public:
    Matrice(){
        alocate(MAXN);
        n=MAXN-1;
    }
    Matrice(int n){
        alocate(n);
        this->n=n;
    }
    Matrice(const Matrice& cpy){
        this->n=cpy.n;
        alocate(this->n);
        FOR(i,1,n)
            FOR(j,1,n)
                a[i][j]=cpy.a[i][j];
    }
    ~Matrice(){
        for(int i=0;i<=n;++i)
            delete[] a[i];
        delete[] a;
    }
    Matrice& operator=(const Matrice& cpy){
        if(this != &cpy){
            if(n<cpy.n){
                FOR(i,0,n)
                    delete[] a[i];
                delete[] a;
                alocate(cpy.n);
            }
            n=cpy.n;
        }
        return *this;
    }
    friend istream& operator>>(istream& in,Matrice& matr){
        int nrNodes,cnt;
        cout<<"Enter number of nodes/rows: ";
        in>>nrNodes;
        if(matr.n<nrNodes){
            matr=Matrice(nrNodes);
        }
        matr.a[0][0]=nrNodes;
        cout<<"Enter number of neighbors/elements and then neighbors/elements for node/row:\n";
        FOR(i,1,matr.a[0][0]){
            cout<<i<<": ";
            in>>matr.a[i][0];
            FOR(j,1,matr.a[i][0])
                in>>matr.a[i][j];
            cout<<'\n';
        }
        return in;
    }
    friend ostream& operator<<(ostream& out,const Matrice&matr){
        out<<"Matrix at "<<&matr<<":\n";
        FOR(i,1,matr.a[0][0])
        {
            out<<i<<": ";
            FOR(j,1,matr.a[i][0])
                out<<matr.a[i][j]<<' ';
            out<<'\n';
        }
        return out;
    }
};

class Graf{
    int nr_noduri;
public:
    Graf():nr_noduri(0){}
    Graf(int nr):nr_noduri(nr){}
    Graf(const Graf& cpy){
        nr_noduri=cpy.nr_noduri;
    }
    ~Graf(){
        nr_noduri=0;
    }

    virtual Graf& operator=(const Graf& cpy){
        if(this!=&cpy)
            nr_noduri=cpy.nr_noduri;
        return *this;
    }
    virtual ostream& grafOut(ostream& out)=0;
    virtual istream& grafIn(istream& in)=0;

    virtual istream& operator>>(istream& in){
        cout<<"Etner number of nodes: ";
        in>>this->nr_noduri;
        cout<<'\n';
        return in;
    }
    virtual ostream& operator<<(ostream& out){
        out<<"The graph has "<<this->nr_noduri<<" nodes\n";
        return out;
    }
};

class Graf_complet: public Graf{
    int nr_muchii;
public:
    Graf_complet(): Graf(0),nr_muchii(0){}
    Graf_complet(int x): Graf(x-1),nr_muchii(x){}
    Graf_complet(int x,int y): Graf(x),nr_muchii(y){}
    Graf_complet(const Graf_complet& cpy): Graf(cpy){
        this->nr_muchii=cpy.nr_muchii;
    }
    ~Graf_complet(){
        nr_muchii=0;
    }//apeleaza si ~Graf() but nothing to do
    istream& grafIn(istream& in){
        return this->Graf::operator>>(in);
    }
    ostream& grafOut(ostream& out){
        return this->Graf::operator<<(out);
    }

    Graf_complet& operator=(const Graf_complet& cpy)
    {
        if(this!=&cpy){
                Graf::operator=(cpy);
                nr_muchii=cpy.nr_muchii;
        }
        return *this;
    }

    friend istream& operator>>(istream& in,Graf_complet& cpy){
        cpy.grafIn(in);
        cout<<"Enter number of edges: ";
        in>>cpy.nr_muchii;
        cout<<'\n';
        return in;
    }
    friend ostream& operator<<(ostream& out,Graf_complet& cpy){
        cpy.grafOut(out);
        out<<"The graph has "<<cpy.nr_muchii<<" edges\n";
        return out;
    }
};

class Graf_antisimetric: public Graf{
    Matrice mat;
public:
    Graf_antisimetric():Graf(0),mat(0){}
    Graf_antisimetric(int x):Graf(x),mat(x){}
    Graf_antisimetric(int x,int y): Graf(x),mat(((x>y)?x:y)){}
    ~Graf_antisimetric(){}//literally nothing to do

    istream& grafIn(istream& in){
        return this->Graf::operator>>(in);
    }
    ostream& grafOut(ostream& out){
        return this->Graf::operator<<(out);
    }

    Graf_antisimetric& operator=(const Graf_antisimetric& cpy){
        if(this!=&cpy){
            Graf::operator=(cpy);
            this->mat=cpy.mat;
        }
        return *this;
    }
    friend istream& operator>>(istream& in,Graf_antisimetric& cpy){
        cpy.grafIn(in);
        in>>cpy.mat;
        return in;
    }
    friend ostream& operator<<(ostream& out,Graf_antisimetric& cpy){
        cpy.grafOut(out);
        out<<cpy.mat;
        return out;
    }
};

class Graf_turneu: public Graf_complet, public Graf_antisimetric
{
public:
    Graf_turneu():Graf_complet(),Graf_antisimetric(){}

};




int main()
{
    //cin.tie(0);
    //ios_base::sync_with_stdio(0);
    int pot;
    Graf_antisimetric x(5,6);
    cout<<x;
    cin>>x;
    cout<<x;

}