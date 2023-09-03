/* 
    TP 16/17 (LV 9, Zadatak 5)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <stdexcept>
#include <iomanip>

class Sat {
    int sekunde;
    public:
    int DajSate() const;
    int DajMinute() const;
    int DajSekunde() const;
    static bool DaLiJeIspravno (int sati, int minute, int sekunde) {
        return sati>=0 && sati<=23 && minute>=0 && minute<=59 && sekunde>=0 && sekunde<=59;
    }
    Sat &Postavi (int sati, int minute, int sekunde) {
        if(!DaLiJeIspravno(sati, minute, sekunde)) throw std::domain_error("Neispravno vrijeme");
        Sat::sekunde=sekunde+minute*60+sati*60*60;
        return *this;
    }
    Sat &PostaviNormalizirano (int sati, int minute, int sekunde);
    void Ispisi() const {
        std::cout<<std::setfill('0')<<std::setw(2)<<DajSate()<<":"<<std::setw(2)<<DajMinute()<<":"<<std::setw(2)<<DajSekunde();
    }
    Sat &Sljedeci() {PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde()+1); return *this;}
    Sat &Prethodni() {PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde()-1); return *this;}
    Sat &PomjeriZa(int sekunde) {PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde()+sekunde); return *this;}
    friend int BrojSekundiIzmedju (const Sat &v1, const Sat &v2);
    static int Razmak (const Sat &v1, const Sat &v2);
};
int Sat::DajSekunde() const {
    return sekunde%60;
}
int Sat::DajMinute() const {
    return ((sekunde-DajSekunde())/60)%60;
}
int Sat::DajSate() const {
    return (((sekunde-DajSekunde())/60-DajMinute())/60)%24;
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
int BrojSekundiIzmedju (const Sat &v1, const Sat &v2) {
    return v1.sekunde-v2.sekunde;
}
int Sat::Razmak (const Sat &v1, const Sat &v2) {
    return v1.sekunde-v2.sekunde;
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
    vrijeme.Ispisi();
    }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what()<<std::endl;
        std::cout<<"Normalizirano vrijeme je: ";
        vrijeme.PostaviNormalizirano(h, m, s);
        std::cout<<vrijeme.DajSate()<<":"<<vrijeme.DajMinute()<<":"<<vrijeme.DajSekunde()<<std::endl;
    }
    std::cout<<std::endl<<"Vrijeme vece za sekundu od unesenog je ";
    vrijeme.Sljedeci().Ispisi();
    int pomjeri_za;
    std::cout<<std::endl<<"Unesite za koliko sekundi zelite pomjeriti vrijeme koje ste unijeli: ";
    std::cin>>pomjeri_za;
    std::cout<<"Pomjereno vrijeme je: ";
    vrijeme.Prethodni().PomjeriZa(pomjeri_za).Ispisi();
    int h2, m2, s2;
    std::cout<<std::endl<<"Unesite novo vrijeme: ";
    std::cin>>h2>>m2>>s2;
    Sat vrijeme2;
    if(vrijeme2.DaLiJeIspravno(h2, m2, s2)) vrijeme2.Postavi(h2, m2, s2);
    else vrijeme2.PostaviNormalizirano(h2, m2, s2);
    std::cout<<"Unijeli ste vrijeme: ";
    vrijeme2.Ispisi();
    std::cout<<std::endl<<"Pomjereno prvo vrijeme je vece od drugog za "<<BrojSekundiIzmedju(vrijeme, vrijeme2)
    <<" sekundi, odnosno drugo od pomjerenog prvog za "<<Sat::Razmak(vrijeme2, vrijeme)<<" sekundi";
	return 0;
}