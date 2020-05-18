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
    Locuinta(){
        numeClient="";
        suprafataUtila=0;
        discount=0;
    }
    string getNumeClienti(){
        return this->numeClient;
    }
    double getSuprafataUtila(){
        return this->suprafataUtila;
    }
    double getDiscount(){
        return this->discount;
    }
    static void increaseLocuinte(){
        Locuinta::numarLocuinte++;
    }
    static int getLocuinte(){
        return Locuinta::numarLocuinte;
    }
    friend bool operator <(const Locuinta obj1, const Locuinta obj2){
        if(obj1.suprafataUtila<obj2.suprafataUtila)
            return 1;
        return 2;
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
    Apartament(): Locuinta(){
        etaj=0;
        pretMP=0;
    }
    int getEtaj(){
        return this->etaj;
    }
    double getPretMP(){
        return this->pretMP;
    }
    double obtineChirie(){
        double pret = pretMP * this->getSuprafataUtila();
        return static_cast<double>(pret - (pret * this->getDiscount())/100.0);
    }
    static void increaseLocuinte(){
        Apartament::numarLocuinte++;
    }
    static int getLocuinte(){
        return Apartament::numarLocuinte;
    }
    friend bool operator <(Apartament obj1,Apartament obj2){
        if(obj1.getSuprafataUtila()<obj2.getSuprafataUtila())
            return 1;
        return 0;
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
    vector<double> pretEtaje;
    double curteMP;
    double pretCurteMP;
    public:
    Casa(string nume, double supr, double discount, int etaje, vector<double> utilEtaj, vector<double> pretEtj, double curteMP, double pretCurteMP): Locuinta(nume,supr,discount){
        this->etaje = etaje;
        this->supUtilaEtaje = utilEtaj;
        this->pretEtaje = pretEtj;
        this->curteMP = curteMP;
        this->pretCurteMP = pretCurteMP;
    }
    Casa(string nume, double supr, int etaje, vector<double> utilEtaj, vector<double> pretEtj, double curteMP, double pretCurteMP): Locuinta(nume,supr){
        this->etaje = etaje;
        this->supUtilaEtaje = utilEtaj;
        this->pretEtaje = pretEtj;
        this->curteMP = curteMP;
        this->pretCurteMP = pretCurteMP;
    }
    Casa():Locuinta(){
        etaje=0;
        supUtilaEtaje.clear();
        pretEtaje.clear();
        curteMP=0;
        pretCurteMP=0;
    }
    int getEtaje(){
        return this->etaje;
    }
    vector<double> getSupUtilaEtaje(){
        return this->supUtilaEtaje;
    }
    vector<double> getPretEtaje(){
        return this->pretEtaje;
    }
    double getCurteMP(){
        return this->curteMP;
    }
    double getPretCurteMP(){
        return this->pretCurteMP;
    }
    double obtineChirie(){
        double pret;
        for(int et = 0; et<etaje; et++)
            pret += static_cast<double>(supUtilaEtaje[et] * pretEtaje[et]);
        pret = static_cast<double> (pret - (pret * this->getDiscount())/100.0);
        pret+= static_cast<double>(curteMP * pretCurteMP);
        return pret;
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
        obj.pretEtaje.resize(obj.etaje);
        for(int i=0;i<obj.etaje;i++)
            in>>obj.pretEtaje[i];
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
            out<<obj.pretEtaje[i]<<' ';
        out<<"\nCurte MP: "<<obj.curteMP<<"\nPret curte/MP: "<<obj.pretCurteMP<<'\n';
        return out;
    }
};
int Locuinta::numarLocuinte = 0;
int Apartament::numarLocuinte = 0;
int Casa::numarLocuinte = 0;

template<class Tip> 
class Gestiune;

template<class Tip>
istream& operator>>(istream&,Gestiune<Tip>& obj);

template<class Tip>
ostream& operator>>(ostream&,Gestiune<Tip>& obj);

template<class Tip>
class Gestiune{
    set<pair<Locuinta,Tip>> multimeLocuinte; //NOT EVEN AN IDEA LMAO
    vector<Tip> listaLocuinte;
    int localNumarCase;
    int localNumarApartamente;
    vector<double> caseChirie;

    public:
    Gestiune(Tip &a){
        localNumarCase=0;
        localNumarApartamente=0;
        if(typeid(a)==typeid(Casa))
            localNumarCase++;
        else
            localNumarApartamente++;
        if(typeid(a)==typeid(Casa))
        {
            double chirie = a.obtineChirie();
            caseChirie.push_back(chirie);
        }
        listaLocuinte.push_back(a);
        Tip::increaseLocuinte();
        Locuinta::increaseLocuinte();
        Locuinta* conv = dynamic_cast<Locuinta*>(&a);
        pair<Locuinta,Tip> aux = make_pair(*conv,a);
        this->multimeLocuinte.insert(aux); //just doesn't work...
        //cout<<'\n';
        //cout<<typeid(*conv).name();
        //cout<<'\n';
        //cout<<typeid(aux.first).name();
    }
    Gestiune(){
        localNumarCase=0;
        localNumarApartamente=0;
    }
    int getLocalLocuinte(){
        if(typeid(Tip) == typeid(Casa))
            return this->localNumarCase;
        return this->localNumarApartamente;
    }
    int getLocuinte(){
        return Tip::getLocuinte();
    }
    int getTotalLocuinte(){
        return Tip::Locuinta::getLocuinte();
    }
    double getChirieCase(){
        cout<<"Only possible for Gestiune<Casa>!\n";
        return -1;
    }
    vector<Tip> getElemente(){
        return this->listaLocuinte;
    }

    void afis(){
        for(auto it: multimeLocuinte)
            cout<<it.second;
    }
    void operator += (Tip &ob){
        listaLocuinte.push_back(ob);
        if(typeid(ob)==typeid(Casa))
            localNumarCase++;
        else
            localNumarApartamente++;
        if(typeid(ob)==typeid(Casa))
        {
            double chirie = ob.obtineChirie();
            caseChirie.push_back(chirie);
        }
        Tip::increaseLocuinte();
        Locuinta::increaseLocuinte();
        Locuinta* conv = dynamic_cast<Locuinta*>(&ob);
        pair<Locuinta,Tip> aux = make_pair(*conv,ob);
        this->multimeLocuinte.insert(aux); //just doesn't work... ACTUALLY SOLVED IT, sleep is the best
        //Set needs operator < no matter wat, kappa
        //if(typeid(ob)==typeid(Apartament))
        //    Apartament::numarApartamente++;
        //else
        //    Case::numarCase++;
        //No idea what else I could do here, or WHAT IT WANTS FROM ME
        //the most ambiguous task ever.
        //Locuinta* conv = dynamic_cast<Locuinta*>(ob);
        //multimeLocuinte.insert(make_pair(*conv,ob));
    }
    friend istream& operator>> (istream& in, Gestiune& obj){
        Tip obj2;
        in>>obj2;
        obj+=obj2;
        return in;
    }
    friend ostream& operator<< (ostream& out, Gestiune& obj){
        obj.afis();
        return out;
    }
};

template<>
double Gestiune<Casa>::getChirieCase(){
    double sum;
    for(auto it : caseChirie)
        sum+=it;
    return sum;
}

int main()
{
    //cin.tie(0);
    //ios_base::sync_with_stdio(0); //I was wondering what was wrong, lmao
    // Declaring first instance of Gestiune<Apartament> ***************
    Apartament x("Andrei", 200.5F,5.5F,3,12.3F);
    Apartament y("Buzau", 220.5F,3.5F,2,14.3F);
    cout<<x.getNumeClienti()<<'\n';
    cout<<'\n';
    cout<<x.obtineChirie();
    cout<<'\n';
    //Apartament ecsdee;
    //cin>>ecsdee;
    Gestiune<Apartament> gest(x);
    gest+=y;
    //gest+=ecsdee;
    gest.afis();
    cout<<x.getLocuinte();
    cout<<'\n';
    cout<<x.getDiscount();
    cout<<'\n';
    cout<<gest.getLocalLocuinte();
    cout<<'\n';
    cout<<gest.getLocuinte();
    cout<<'\n';
    cout<<gest.getTotalLocuinte();
    cout<<'\n';

    // Declaring first instance of Gestiune<Casa> ***********************
    vector<double> whatever(2,1);
    Casa c1("Texting",300.2,10,2,whatever,whatever,300,2),c2("Specialization",55.2,3,2,whatever,whatever,22,4);
    Gestiune<Casa> gestCasa;
    gestCasa+=c1;
    gestCasa+=c2;
    cout<<gestCasa;
    cout<<gestCasa.getLocalLocuinte();
    cout<<'\n';
    cout<<gestCasa.getLocuinte();
    cout<<'\n';
    cout<<gestCasa.getTotalLocuinte();
    cout<<'\n';
    cout<<gestCasa.getChirieCase();
    cout<<'\n';
    vector<Casa> listeCase = gestCasa.getElemente();
    for(auto it:listeCase)
        cout<<it.obtineChirie()<<'\n';
    
    // Declaring second instance of Gestiune<Apartament> ***************
    Apartament z("Pupaza", 200.5F,5.5F,3,12.3F);
    Apartament w("cartof", 220.5F,3.5F,2,14.3F);
    Gestiune<Apartament> gest2;
    gest2+=z;
    gest2+=w;
    //cin>>gest2;
    //gest2.afis();
    cout<<gest2;
    cout<<gest2.getLocalLocuinte();
    cout<<'\n';
    cout<<gest2.getLocuinte();
    cout<<'\n';
    cout<<gest2.getTotalLocuinte();
    cout<<'\n';
    cout<<gest2.getChirieCase();

}
