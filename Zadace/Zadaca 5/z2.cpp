//TP 2021/2022: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <iomanip>

class Berza {
    std::vector<int> cijene;
    int min, max;
    public:
    Berza(int min, int max) {
        if(min<0 || max<0) throw std::range_error("Ilegalne granice cijene");
        Berza::min=min; Berza::max=max;
    }
    explicit Berza(int max) {
        if(max<0) throw std::range_error("Ilegalne granice cijene");
        Berza::max=max; Berza::min=0;
    }
    void RegistrirajCijenu(int cijena) {
        if(cijena<min || cijena>max) throw std::range_error("Ilegalna cijena");
        cijene.push_back(cijena);
    }
    int DajBrojRegistriranihCijena() const {return cijene.size();}
    void BrisiSve() {cijene.resize(0);}
    int DajMinimalnuCijenu() const;
    int DajMaksimalnuCijenu() const;
    bool operator !() {return DajBrojRegistriranihCijena()==0;}
    int DajBrojCijenaVecihOd(int cijena) const;
    void Ispisi() const;
    int operator [](int indeks) const;
    Berza &operator ++();
    Berza operator ++(int);
    Berza &operator --();
    Berza operator --(int);
    Berza &operator -();
    friend Berza operator +(const Berza &b, int n);
    friend Berza operator +(int n, const Berza &b);
    Berza &operator +=(int n);
    friend Berza operator -(const Berza &b, int n);
    Berza &operator -=(int n);
    friend Berza operator -(int n, const Berza &b);
    Berza &operator -=(const Berza &b);
    friend Berza operator -(const Berza &b1, const Berza &b2);
    friend bool operator ==(const Berza &b1, const Berza &b2);
    friend bool operator !=(const Berza &b1, const Berza &b2);
};
int Berza::DajMinimalnuCijenu() const {
    if(!DajBrojRegistriranihCijena()) throw std::range_error("Nema registriranih cijena");
    return *std::min_element(cijene.begin(), cijene.end());
}
int Berza::DajMaksimalnuCijenu() const {
    if(!DajBrojRegistriranihCijena()) throw std::range_error("Nema registriranih cijena");
    return *std::max_element(cijene.begin(), cijene.end());
}
int Berza::DajBrojCijenaVecihOd(int cijena) const {
    if(!DajBrojRegistriranihCijena()) throw std::range_error("Nema registriranih cijena");
    return std::count_if(cijene.begin(), cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, cijena));
}
void Berza::Ispisi() const {
    std::vector<double> pomocni(DajBrojRegistriranihCijena());
    std::copy(cijene.begin(), cijene.end(), pomocni.begin());
    std::sort(pomocni.begin(), pomocni.end(), std::greater<double>());
    std::transform(pomocni.begin(), pomocni.end(), pomocni.begin(), std::bind(std::divides<double>(), std::placeholders::_1, 100));
    std::cout<<std::fixed<<std::setprecision(2);
    std::copy(pomocni.begin(), pomocni.end(), std::ostream_iterator<double>(std::cout, "\n"));
}
int Berza::operator [](int indeks) const {
    if(indeks<1 || indeks>DajBrojRegistriranihCijena()) throw std::range_error("Neispravan indeks");
    return cijene.at(indeks-1);
}
Berza &Berza::operator ++() {
    std::vector<int> pomocni(DajBrojRegistriranihCijena());
    std::transform(cijene.begin(), cijene.end(), pomocni.begin(), std::bind(std::plus<int>(), std::placeholders::_1, 100));
    if(std::any_of(pomocni.begin(), pomocni.end(), std::bind(std::greater<int>(), std::placeholders::_1, max)) ||
    std::any_of(pomocni.begin(), pomocni.end(), std::bind(std::less<int>(), std::placeholders::_1, min))) 
        throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    cijene=pomocni;
    return *this;
}
Berza Berza::operator ++(int) {
    Berza pomocni=*this;
    ++*this;
    return pomocni;
}
Berza &Berza::operator --() {
    std::vector<int> pomocni(DajBrojRegistriranihCijena());
    std::transform(cijene.begin(), cijene.end(), pomocni.begin(), std::bind(std::minus<int>(), std::placeholders::_1, 100));
    if(std::any_of(pomocni.begin(), pomocni.end(), std::bind(std::greater<int>(), std::placeholders::_1, max)) ||
    std::any_of(pomocni.begin(), pomocni.end(), std::bind(std::less<int>(), std::placeholders::_1, min)))
        throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    cijene=pomocni; 
    return *this;
}
Berza Berza::operator --(int) {
    Berza pomocni=*this;
    --*this;
    return pomocni;
}
Berza &Berza::operator -() {
    std::transform(cijene.begin(), cijene.end(), cijene.begin(), std::bind(std::minus<int>(), min+max, std::placeholders::_1));
    return *this;
}
Berza &Berza::operator +=(int n) {
    std::vector<int> pomocni(DajBrojRegistriranihCijena());
    std::transform(cijene.begin(), cijene.end(), pomocni.begin(), std::bind(std::plus<int>(), std::placeholders::_1, n));
    if(std::any_of(pomocni.begin(), pomocni.end(), std::bind(std::less<int>(), std::placeholders::_1, min)) ||
    std::any_of(pomocni.begin(), pomocni.end(), std::bind(std::greater<int>(), std::placeholders::_1, max)))
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    cijene=pomocni;
    return *this;
}
Berza operator +(const Berza &b, int n) {
    Berza pomocni=b;
    pomocni+=n;
    return pomocni;
}
Berza operator +(int n, const Berza &b) {
    Berza pomocni=b+n;
    return pomocni;
}
Berza &Berza::operator -=(int n) {
    std::vector<int> pomocni(DajBrojRegistriranihCijena());
    std::transform(cijene.begin(), cijene.end(), pomocni.begin(), std::bind(std::minus<int>(), std::placeholders::_1, n));
    if(std::any_of(pomocni.begin(), pomocni.end(), std::bind(std::less<int>(), std::placeholders::_1, min)) ||
    std::any_of(pomocni.begin(), pomocni.end(), std::bind(std::greater<int>(), std::placeholders::_1, max)))
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    cijene=pomocni;
    return *this;
}
Berza operator -(const Berza &b, int n) {
    Berza pomocni=b;
    pomocni-=n;
    return pomocni;
}
Berza operator -(int n, const Berza &b) {
    Berza pomocni=b;
    std::transform(b.cijene.begin(), b.cijene.end(), pomocni.cijene.begin(), std::bind(std::minus<int>(), n, std::placeholders::_1));
    if(std::any_of(pomocni.cijene.begin(), pomocni.cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, b.min)) ||
    std::any_of(pomocni.cijene.begin(), pomocni.cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, b.max)))
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return pomocni;
}
Berza &Berza::operator -=(const Berza &b) {
    if(!(DajBrojRegistriranihCijena()==b.DajBrojRegistriranihCijena() && min==b.min && max==b.max)) 
        throw std::domain_error("Nesaglasni operandi");
    std::vector<int> pomocni(DajBrojRegistriranihCijena());
    std::transform(cijene.begin(), cijene.end(), b.cijene.begin(), pomocni.begin(), std::minus<int>());
    if(std::any_of(pomocni.begin(), pomocni.end(), std::bind(std::less<int>(), std::placeholders::_1, min)) ||
    std::any_of(pomocni.begin(), pomocni.end(), std::bind(std::greater<int>(), std::placeholders::_1, max)))
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    cijene=pomocni;
    return *this;
}
Berza operator -(const Berza &b1, const Berza &b2) {
    Berza pomocni=b1;
    pomocni-=b2;
    return pomocni;
}
bool operator ==(const Berza &b1, const Berza &b2) {
    if(b1.DajBrojRegistriranihCijena()!=b2.DajBrojRegistriranihCijena()) return false;
    return std::equal(b1.cijene.begin(), b1.cijene.end(), b2.cijene.begin());
}
bool operator !=(const Berza &b1, const Berza &b2) {
    return !(b1==b2);
}
int main ()
{
    try {
        Berza b1(1000,500000);
        b1.RegistrirajCijenu(15000); b1.RegistrirajCijenu(25660); b1.RegistrirajCijenu(368547);
        if(!b1) std::cout<<"Nema registriranih cijena";
        else std::cout<<b1.DajBrojRegistriranihCijena()<<" "<<b1.DajMaksimalnuCijenu()<<" "<<b1.DajMaksimalnuCijenu()<<" "<<
        b1.DajBrojCijenaVecihOd(10000)<<std::endl;
        b1.Ispisi(); std::cout<<"------------"<<std::endl;
        b1.BrisiSve();
        b1.Ispisi(); std::cout<<"------------"<<std::endl;
        Berza b2(500000);
        b2.RegistrirajCijenu(150000); b2.RegistrirajCijenu(25660); b2.RegistrirajCijenu(368547);
        std::cout<<b2[1]<<" "<<b2[2]<<" "<<b2[3]<<std::endl;
        b1=++b2;
        b1.Ispisi(); std::cout<<"------------"<<std::endl;
        b2.Ispisi(); std::cout<<"------------"<<std::endl;
        b1++; b1--;
        Berza b3=b1--;
        Berza b4=--b2;
        b3.Ispisi(); std::cout<<"------------"<<std::endl;
        b4.Ispisi(); std::cout<<"------------"<<std::endl;
        -b3; std::cout<<b3[1]<<std::endl;
        b3=b4+100; 
        b3=100+b4;
        b3.Ispisi(); std::cout<<"------------"<<std::endl;
        b4+=200;
        b4=b1-100; 
        b4-=200;
        b4.Ispisi(); std::cout<<"------------"<<std::endl;
        Berza b5=b1-b2;
        b5.Ispisi(); std::cout<<"------------"<<std::endl;
        b4=1000-b5;
        b4.Ispisi(); std::cout<<"------------"<<std::endl;
        b1-=b2;
        b1.Ispisi(); std::cout<<"------------"<<std::endl;
        if(b1==b2 && b3!=b4) std::cout<<"DA"<<std::endl;
        else std::cout<<"NE"<<std::endl;
    }
    catch(std::range_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what();
    }
	return 0;
}
