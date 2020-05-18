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

class Locuinta{
    static int numarLocuinte;
    string numeClient;
    double suprafataUtila;
    double discount; // 0-10%
    public:
    Locuinta(string nume,double supr,double discount){
        this->numeClient = nume;
        this->discount = discount;
        this-> suprafataUtila = supr;
    }
    Locuinta(string nume,double supr){
        this->numeClient = nume;
        this->suprafataUtila = supr;
        this->discount = 0;
    }
    string getNumeClienti(){
        return this->numeClient;
    }
    static void increaseLocuinte(){
        Locuinta::numarLocuinte++;
    }
    friend bool operator <(const Locuinta obj1, const Locuinta obj2){
        if(obj1.suprafataUtila<obj2.suprafataUtila)
            return 1;
        return 2;
    }
    static int getLocuinte(){
        return Locuinta::numarLocuinte;
    }

    double getSuprafataUtila(){
        return this->suprafataUtila;
    }
    double getDiscount(){
        return this->discount;
    }
    friend istream& operator >>(istream& in,Locuinta& obj){
        cout<<"Enter nume client: ";
        in>>obj.numeClient;
        cout<<"Enter suprafataUtila: ";
        in>>obj.suprafataUtila;
        cout<<"enter discount(0-10%): ";
        in>>obj.discount;
        return in;
    }
    friend ostream& operator<<(ostream& out,Locuinta& obj){
        out<<"Nume Client: "<<obj.numeClient<<'\n';
        out<<"Suprafata utila: "<<obj.suprafataUtila<<"\nDiscount: "<<obj.discount<<'\n';
        return out;
    }
};

class Apartament: public Locuinta{
    static int numarLocuinte;
    int etaj;
    double pretMP;
    public:
    Apartament(string nume, double supr, double discount, int etaj, double pretMP): Locuinta(nume,supr,discount){
        this->etaj = etaj;
        this->pretMP = pretMP;
    }
    Apartament(string nume, double supr, int etaj, double pretMP): Locuinta(nume,supr){
        this->etaj = etaj;
        this->pretMP = pretMP;
    }
    friend bool operator <(Apartament obj1,Apartament obj2){
        if(obj1.getSuprafataUtila()<obj2.getSuprafataUtila())
            return 1;
        return 0;
    }
    static void increaseLocuinte(){
        Apartament::numarLocuinte++;
    }
    static int getLocuinte(){
        return Apartament::numarLocuinte;
    }
    double obtineChirie(){
        double pret = pretMP * this->getSuprafataUtila();
        return static_cast<double>(pret - (pret * this->getDiscount())/100.0);
    }
    friend istream& operator>>(istream& in, Apartament& obj){
        in>> static_cast<Locuinta&>(obj);
        cout<<"Enter etaj: ";
        in>>obj.etaj;
        cout<<"Enter pret mp supr utila: ";
        in>>obj.pretMP;
        return in;
    }
    friend ostream& operator<<(ostream& out,Apartament& obj){
        out<< static_cast<Locuinta&>(obj);
        out<<"Etaj: "<<obj.etaj<<"\npretMP supr utila: "<<obj.pretMP<<'\n';
        return out;
    }
};

class Casa : public Locuinta{
    static int numarLocuinte;
    int etaje;
    vector<double> supUtilaEtaje;
    vector<double> pretEtaj;
    double curteMP;
    double pretCurteMP;
    public:
    Casa(string nume, double supr, double discount, int etaje, vector<double> utilEtaj, vector<double> pretEtj, double curteMP, double pretCurteMP): Locuinta(nume,supr,discount){
        this->etaje = etaje;
        this->supUtilaEtaje = utilEtaj;
        this->pretEtaj = pretEtj;
        this->curteMP = curteMP;
        this->pretCurteMP = pretCurteMP;
    }
    Casa(string nume, double supr, int etaje, vector<double> utilEtaj, vector<double> pretEtj, double curteMP, double pretCurteMP): Locuinta(nume,supr){
        this->etaje = etaje;
        this->supUtilaEtaje = utilEtaj;
        this->pretEtaj = pretEtj;
        this->curteMP = curteMP;
        this->pretCurteMP = pretCurteMP;
    }
    static void increaseLocuinte(){
        Casa::numarLocuinte++;
    }
    static int getLocuinte(){
        return Casa::numarLocuinte;
    }
    friend bool operator <(const Casa obj1,const Casa obj2){
        double ans1,ans2;
        for (auto it : obj1.supUtilaEtaje)
            ans1 += it;
        for (auto it: obj2.supUtilaEtaje)
            ans2 += it;
        if(ans1<ans2)
            return 1;
        return 0;
    }

    double obtineChirie(){
        double pret;
        for(int et = 0; et<etaje; et++)
            pret += static_cast<double>(supUtilaEtaje[et] * pretEtaj[et]);
        pret = static_cast<double> (pret - (pret * this->getDiscount())/100.0);
        pret+= static_cast<double>(curteMP * pretCurteMP);
        return pret;
    }
    friend istream& operator>>(istream& in,Casa& obj){
        double x;
        in>> static_cast<Locuinta&>(obj);
        cout<<"Enter etaje: ";
        in>>obj.etaje;
        cout<<"Enter suprafata utile pe fiecare etaj: ";
        obj.supUtilaEtaje.resize(obj.etaje);
        for(int i=0;i<obj.etaje;i++)
            in>>obj.supUtilaEtaje[i];
        cout<<"Enter pretMP pe fiecare etaj: ";
        obj.pretEtaj.resize(obj.etaje);
        for(int i=0;i<obj.etaje;i++)
            in>>obj.pretEtaj[i];
        cout<<"Enter suprafata curte: ";
        in>>obj.curteMP;
        cout<<"Enter pretMP curte: ";
        in>>obj.pretCurteMP;
        return in;
    }
    friend ostream& operator<<(ostream& out,Casa& obj){
        out<< static_cast<Locuinta&>(obj);
        out<<"Etaje: "<<obj.etaje<<"\nSuprafata Utile/Etaj: ";
        for(int i=0;i<obj.etaje;i++)
            out<<obj.supUtilaEtaje[i]<<' ';
        out<<"\nPret pe fiecare etaj: ";
        for(int i=0;i<obj.etaje;i++)
            out<<obj.pretEtaj[i]<<' ';
        out<<"\nCurte MP: "<<obj.curteMP<<"\nPret curte/MP: "<<obj.pretCurteMP<<'\n';
        return out;

    }
};
int Locuinta::numarLocuinte = 0;
int Apartament::numarLocuinte = 0;
int Casa::numarLocuinte = 0;

template<class Tip>
class Gestiune{
    set<pair<Locuinta,Tip>> multimeLocuinte; //NOT EVEN AN IDEA LMAO
    vector<Tip> listaLocuinte;

    public:
    Gestiune(Tip &a){
        listaLocuinte.push_back(a);
        Tip::increaseLocuinte();
        Locuinta::increaseLocuinte();
        Locuinta* conv = dynamic_cast<Locuinta*>(&a);
        //cout<<'\n';
        //cout<<typeid(*conv).name();
        pair<Locuinta,Tip> aux = make_pair(*conv,a);
        //cout<<'\n';
        //cout<<typeid(aux.first).name();
        this->multimeLocuinte.insert(aux); //just doesn't work...
    }
    Gestiune(){
    }

    void operator += (Tip &ob){
        listaLocuinte.push_back(ob);
        //if(typeid(ob)==typeid(Apartament))
        //    Apartament::numarApartamente++;
        //else
        //    Case::numarCase++;
        Tip::increaseLocuinte();
        Locuinta::increaseLocuinte();
        Locuinta* conv = dynamic_cast<Locuinta*>(&ob);
        pair<Locuinta,Tip> aux = make_pair(*conv,ob);
        this->multimeLocuinte.insert(aux); //just doesn't work... ACTUALLY SOLVED IT, sleep is the best

        //No idea what else I could do here, or WHAT IT WANTS FROM ME
        //the most ambiguous task ever.
        //Locuinta* conv = dynamic_cast<Locuinta*>(ob);
        //multimeLocuinte.insert(make_pair(*conv,ob));
    }
    
    void afis(){
        cout<< Tip::getLocuinte()<<'\n';
        cout<< Locuinta::getLocuinte()<<'\n';
        for(auto it: multimeLocuinte)
            cout<<it.second;
    }

};


int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    Apartament x("Andrei", 200.5F,5.5F,3,12.3F);
    Apartament y("Buzau", 220.5F,3.5F,2,14.3F);
    cout<<x.getNumeClienti()<<'\n';
    cout<<x.obtineChirie();

    Gestiune<Apartament> gest(x);
    gest+=y;
    gest.afis();

}
