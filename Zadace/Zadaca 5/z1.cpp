//TP 2021/2022: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>
#include <sstream>

long long int m=std::numeric_limits<long long int>::min();
long long int M=std::numeric_limits<long long int>::max();

class Razlomak {
    long long int brojnik, nazivnik;
    static void SkratiRazlomak(long long int &brojnik, long long int &nazivnik);
    static long long int NadjiNZD(long long int p, long long int q);
    static void ProvjeriPrekoracenjeMnozenja(long long int x, long long int y);
    static void ProvjeriPrekoracenjeSabiranja(long long int x, long long int y);
    static void ProvjeriPrekoracenjeOduzimanja(long long int x, long long int y);
    public:
    Razlomak(long long int brojnik=0, long long int nazivnik=1);
    long long int DajBrojnik() const {return brojnik;}
    long long int DajNazivnik() const {return nazivnik;}
    friend Razlomak operator +(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak operator -(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak operator *(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak operator /(const Razlomak &r1, const Razlomak &r2);
    Razlomak &operator +=(const Razlomak &r);
    Razlomak &operator -=(const Razlomak &r);
    Razlomak &operator *=(const Razlomak &r);
    Razlomak &operator /=(const Razlomak &r);
    Razlomak operator +() const{return *this;}
    Razlomak operator -() const {
        Razlomak::ProvjeriPrekoracenjeMnozenja(brojnik, -1);
        Razlomak pomocni=Razlomak(-brojnik, nazivnik);
        return pomocni;
    }
    Razlomak &operator ++();
    Razlomak operator ++(int);
    Razlomak &operator --();
    Razlomak operator --(int);
    friend bool operator <(const Razlomak &r1, const Razlomak &r2);
    friend bool operator >(const Razlomak &r1, const Razlomak &r2);
    friend bool operator <=(const Razlomak &r1, const Razlomak &r2);
    friend bool operator >=(const Razlomak &r1, const Razlomak &r2);
    friend bool operator ==(const Razlomak &r1, const Razlomak &r2);
    friend bool operator !=(const Razlomak &r1, const Razlomak &r2);
    friend std::ostream &operator <<(std::ostream &tok, const Razlomak &r);
    friend std::istream &operator >>(std::istream &tok, Razlomak &r);
    operator long double() const;
};
long long int Razlomak::NadjiNZD(long long int p, long long int q) {
    while(q!=0) {
        long long int temp=p;
        p=q;
        q=temp%q;
    }
    return p;
}
void Razlomak::SkratiRazlomak(long long int &brojnik, long long int &nazivnik) {
    long long int NZD=Razlomak::NadjiNZD(brojnik, nazivnik);
    brojnik/=NZD; nazivnik/=NZD;
}
Razlomak::Razlomak(long long int brojnik, long long int nazivnik) {
    if(nazivnik==1) {
        Razlomak::brojnik=brojnik; Razlomak::nazivnik=nazivnik;
        return;
    }
    if(nazivnik==0) throw std::logic_error("Nekorektan razlomak");
    Razlomak::SkratiRazlomak(brojnik, nazivnik);
    if(nazivnik<0) {
        brojnik=-brojnik; nazivnik=-nazivnik;
    }
    Razlomak::brojnik=brojnik; Razlomak::nazivnik=nazivnik;
}
void Razlomak::ProvjeriPrekoracenjeMnozenja(long long int x, long long int y) {
    if(y>0 && (x<m/y || x>M/y) || y<0 && (x==m || -x>M/(-y) || -x<m/(-y))) throw std::overflow_error("Nemoguce dobiti tacan rezultat");
}
void Razlomak::ProvjeriPrekoracenjeSabiranja(long long int x, long long int y) {
    if(y>0 && x>M-y || y<0 && x<m-y) throw std::overflow_error("Nemoguce dobiti tacan rezultat");
}
void Razlomak::ProvjeriPrekoracenjeOduzimanja(long long int x, long long int y) {
    if(y>0 && x<m-y || y<0 && x>M-y) throw std::overflow_error("Nemoguce dobiti tacan rezultat");
}
Razlomak &Razlomak::operator +=(const Razlomak &r) {
    long long int R=Razlomak::NadjiNZD(DajNazivnik(), r.DajNazivnik()), kol1=r.DajNazivnik()/R, kol2=DajNazivnik()/R,
    kol3=r.DajNazivnik()/R;
    Razlomak::ProvjeriPrekoracenjeMnozenja(DajBrojnik(), kol1);
    Razlomak::ProvjeriPrekoracenjeMnozenja(r.DajBrojnik(), kol2);
    Razlomak::ProvjeriPrekoracenjeMnozenja(DajNazivnik(), kol3);
    long long int pr1=DajBrojnik()*kol1, pr2=r.DajBrojnik()*kol2, nazivnik=DajNazivnik()*kol3;
    Razlomak::ProvjeriPrekoracenjeSabiranja(pr1, pr2);
    *this=Razlomak(pr1+pr2, nazivnik);
    return *this;
}
Razlomak operator +(const Razlomak &r1, const Razlomak &r2) {
    Razlomak pomocni=r1;
    pomocni+=r2;
    return pomocni;
}
Razlomak &Razlomak::operator -=(const Razlomak &r) {
    *this+=-r;
    *this=Razlomak(brojnik, nazivnik);
    return *this;
}
Razlomak operator -(const Razlomak &r1, const Razlomak &r2) {
    Razlomak pomocni=r1;
    pomocni-=r2;
    return pomocni;
}
Razlomak &Razlomak::operator *=(const Razlomak &r) {
    long long int s=Razlomak::NadjiNZD(DajBrojnik(), r.DajNazivnik()), t=Razlomak::NadjiNZD(r.DajBrojnik(), DajNazivnik()), kol1=DajBrojnik()/s,
    kol2=r.DajBrojnik()/t, kol3=DajNazivnik()/t, kol4=r.DajNazivnik()/s;
    Razlomak::ProvjeriPrekoracenjeMnozenja(kol1, kol2);
    Razlomak::ProvjeriPrekoracenjeMnozenja(kol3, kol4);
    *this=Razlomak(kol1*kol2, kol3*kol4);
    return *this;
}
Razlomak operator *(const Razlomak &r1, const Razlomak &r2) {
    Razlomak pomocni=r1;
    pomocni*=r2;
    return pomocni;
}
Razlomak &Razlomak::operator /=(const Razlomak &r) {
    long long int u=Razlomak::NadjiNZD(DajBrojnik(), r.DajBrojnik()), R=Razlomak::NadjiNZD(DajNazivnik(), r.DajNazivnik()), kol1=DajBrojnik()/u, 
    kol2=r.DajNazivnik()/R, kol3=DajNazivnik()/R, kol4=r.DajBrojnik()/u;
    Razlomak::ProvjeriPrekoracenjeMnozenja(kol1, kol2);
    Razlomak::ProvjeriPrekoracenjeMnozenja(kol3, kol4);
    *this=Razlomak(kol1*kol2, kol3*kol4);
    return *this;
}
Razlomak operator /(const Razlomak &r1, const Razlomak &r2) {
    Razlomak pomocni=r1;
    pomocni/=r2;
    return pomocni;
}
Razlomak &Razlomak::operator ++() {
    *this+=1;
    return *this;
}
Razlomak Razlomak::operator ++(int) {
    Razlomak pomocni=*this;
    ++*this;
    return pomocni;
}
Razlomak &Razlomak::operator --() {
    *this-=1;
    return *this;
}
Razlomak Razlomak::operator --(int) {
    Razlomak pomocni=*this;
    --*this;
    return pomocni;
}
bool operator <(const Razlomak &r1, const Razlomak &r2) {
    return static_cast<long double>(r1.DajBrojnik())/r1.DajNazivnik()<static_cast<long double>(r2.DajBrojnik())/r2.DajNazivnik();
}
bool operator >(const Razlomak &r1, const Razlomak &r2) {
    return static_cast<long double>(r1.DajBrojnik())/r1.DajNazivnik()>static_cast<long double>(r2.DajBrojnik())/r2.DajNazivnik();
}
bool operator ==(const Razlomak &r1, const Razlomak &r2) {
    return static_cast<long double>(r1.DajBrojnik())/r1.DajNazivnik()==static_cast<long double>(r2.DajBrojnik())/r2.DajNazivnik();
}
bool operator <=(const Razlomak &r1, const Razlomak &r2) {
    return r1<r2 || r1==r2;
}
bool operator >=(const Razlomak &r1, const Razlomak &r2) {
    return r1>r2 || r1==r2;
}
bool operator !=(const Razlomak &r1, const Razlomak &r2) {
    return !(r1==r2);
}
std::ostream &operator <<(std::ostream &tok, const Razlomak &r) {
    if(r.DajNazivnik()==1) return tok<<r.DajBrojnik();
    else return tok<<r.DajBrojnik()<<"/"<<r.DajNazivnik();
}
std::istream &operator >>(std::istream &tok, Razlomak &r) {
    decltype(r.brojnik) br;
    tok>>std::ws>>r.brojnik;
    if(tok.peek()=='\n' || tok.peek()=='\r' || tok.peek()=='\f' || tok.peek()=='\v' || tok.peek()=='\t' || tok.peek()==' ') {
        r.nazivnik=1; return tok;
    }
    else if(tok.peek()!='/'){
        tok.setstate(std::ios::failbit); r.nazivnik=1;
    }
    char znak;
    tok>>znak;
    if(tok.peek()=='\n' || tok.peek()=='\r' || tok.peek()=='\f' || tok.peek()=='\v' || tok.peek()=='\t' || tok.peek()==' ')
        tok.setstate(std::ios::failbit);
    tok>>r.nazivnik;
    if(tok.peek()!='\n' && tok.peek()!='\r' && tok.peek()!='\f' && tok.peek()!='\v' && tok.peek()!='\t' && tok.peek()!=' ') 
        tok.setstate(std::ios::failbit);
    r=Razlomak(r.brojnik, r.nazivnik);
    return tok;
}
Razlomak::operator long double() const {
    return static_cast<long double>(DajBrojnik())/DajNazivnik();
}
int main ()
{
    Razlomak r1(2022,1040);
    std::cout<<"r1 = "<<r1<<std::endl;
    std::cout<<r1.DajBrojnik()<<" "<<r1.DajNazivnik()<<std::endl;
    Razlomak r2(16,4);
    std::cout<<"r2 = "<<r2<<std::endl<<"r1 + r2 = "<<r1+r2<<std::endl<<"r1 - r2 = "<<r1-r2<<std::endl<<
    "r1 * r2 = "<<r1*r2<<std::endl<<"r1 / r2 ="<<r1/r2<<std::endl;
    r1+=r2; r1-=r2; std::cout<<r1<<std::endl;
    r1*=r2; r1/=r2; std::cout<<r1<<std::endl;
    std::cout<<-r1<<" "<<+r1<<std::endl;
    Razlomak r3=r1++, r4=r1--, r5=++r1, r6=--r1;
    std::cout<<r3<<" "<<r4<<" "<<r5<<" "<<r6<<std::endl;
    bool a=r1<r2, b=r1>r2, c=r1<=r2, d=r1>=r2, e=r1==r2, f=r1!=r2;
    std::cout<<std::boolalpha<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<std::endl;
    std::cout<<static_cast<long double>(r1)<<std::endl;
    Razlomak r;
    std::cout<<"Unesite razlomak: (p/q)"<<std::endl;
    std::cin>>r;
    std::cout<<"Unijeli ste: "<<r<<std::endl;
	return 0;
}
