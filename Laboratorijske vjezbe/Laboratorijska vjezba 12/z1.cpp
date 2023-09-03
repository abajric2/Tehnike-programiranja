/* 
    TP 16/17 (LV 12, Zadatak 1)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <iomanip>

class Sat {
    int sati, minute, sekunde;
    public:
    Sat () {sati=0; minute=0; sekunde=0;}
    Sat(int h, int m, int s) {PostaviNormalizirano(h, m, s);}
    int DajSate() const {return sati;}
    int DajMinute() const {return minute;}
    int DajSekunde() const {return sekunde;}
    static bool DaLiJeIspravno (int sati, int minute, int sekunde) {
        return sati>=0 && sati<=23 && minute>=0 && minute<=59 && sekunde>=0 && sekunde<=59;
    }
    Sat &Postavi (int sati, int minute, int sekunde) {
        if(!DaLiJeIspravno(sati, minute, sekunde)) throw std::domain_error("Neispravno vrijeme");
        Sat::sati=sati; Sat::minute=minute; Sat::sekunde=sekunde;
        return *this;
    }
    Sat &PostaviNormalizirano (int sati, int minute, int sekunde);
    friend std::ostream &operator <<(std::ostream &tok, const Sat &s);// {
    Sat &operator ++() {PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde()+1); return *this;}
    Sat operator ++(int) {Sat s=*this; PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde()+1); return s;}
    Sat &operator --() {PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde()-1); return *this;}
    Sat operator --(int) {Sat s=*this; PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde()-1); return s;}
    Sat &operator +=(int sekunde) {PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde()+sekunde); return *this;}
    Sat operator +(int n) {Sat s=*this; return s+=n;}
    //Sat operator -(const Sat &s) {return {-sati, -minute, -sekunde};}
    Sat &operator -=(int sekunde) {return *this+=-sekunde;}
    Sat operator -(int n) {Sat s=*this; return s-=n;}
    friend int operator - (const Sat &v1, const Sat &v2);
    //static int operator - (const Sat &v1, const Sat &v2);
};
std::ostream &operator <<(std::ostream &tok, const Sat &s) {
    return tok<<std::setfill('0')<<std::setw(2)<<s.sati<<":"<<std::setw(2)<<s.minute<<":"<<std::setw(2)<<s.sekunde;
}

Sat &Sat::PostaviNormalizirano (int sati, int minute, int sekunde) {
    int s=sekunde%60; 
    if(s<0) s+=60;
    minute=(sekunde-s)/60+minute;
    int m=minute%60;
    if(m<0) m+=60;
    sati=((minute-m)/60+sati)%24;
    if(sati<0) sati+=24;
    Postavi(sati, m, s);
    return *this;
}
int PretvoriUSekunde (const Sat &vrijeme) {
    int sekunde=vrijeme.DajSekunde()+60*vrijeme.DajMinute()+60*60*vrijeme.DajSate();
    return sekunde;
}
/*int BrojSekundiIzmedju (const Sat &v1, const Sat &v2) {
    return PretvoriUSekunde(v1)-PretvoriUSekunde(v2);
}*/
int operator -(const Sat &v1, const Sat &v2) {
    return PretvoriUSekunde(v1)-PretvoriUSekunde(v2);
}
int main ()
{
    int h, m, s;
    std::cout<<"Unesite vrijeme (h m s): "<<std::endl;
    std::cin>>h>>m>>s;
    Sat vrijeme;
    try {
    vrijeme.Postavi(h, m, s);
    std::cout<<"Unijeli ste vrijeme: ";
    std::cout<<vrijeme;
    }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what()<<std::endl;
        std::cout<<"Normalizirano vrijeme je: ";
        vrijeme.PostaviNormalizirano(h, m, s);
        std::cout<<vrijeme.DajSate()<<":"<<vrijeme.DajMinute()<<":"<<vrijeme.DajSekunde()<<std::endl;
    }
    std::cout<<std::endl<<"Vrijeme vece za sekundu od unesenog je ";
    std::cout<<++vrijeme<<std::endl;
    vrijeme--;
    int pomjeri_za;
    std::cout<<std::endl<<"Unesite za koliko sekundi zelite pomjeriti vrijeme koje ste unijeli: ";
    std::cin>>pomjeri_za;
    vrijeme+=pomjeri_za;
    std::cout<<"Pomjereno vrijeme je: ";
    std::cout<<vrijeme<<std::endl;
    Sat vrijeme2;
    vrijeme2+=162;
    std::cout<<vrijeme2;
    int h3, m3, s3;
    std::cout<<std::endl<<"Unesite novo vrijeme: ";
    std::cin>>h3>>m3>>s3;
    Sat vrijeme3;
    if(vrijeme3.DaLiJeIspravno(h3, m3, s3)) vrijeme3.Postavi(h3, m3, s3);
    else vrijeme3.PostaviNormalizirano(h3, m3, s3);
    std::cout<<"Unijeli ste vrijeme: ";
    std::cout<<vrijeme3;
    std::cout<<std::endl<<"Pomjereno prvo vrijeme je vece od drugog za "<<vrijeme-vrijeme3
    <<" sekundi, odnosno drugo od pomjerenog prvog za "<<vrijeme3-vrijeme<<" sekundi";
	return 0;
}