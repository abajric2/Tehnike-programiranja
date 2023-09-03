/* 
    TP 16/17 (LV 10, Zadatak 5)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <iomanip>

const double PI=4*std::atan(1);

class Ugao {
    int stepeni, minute, sekunde;
    public:
    Ugao(double radijani=0) {Postavi(radijani);};
    Ugao (int stepeni, int minute, int sekunde) {Postavi(stepeni, minute, sekunde);}
    void Postavi(double radijani) {
        radijani=std::fmod(radijani, 2*PI);
        while(radijani<0) radijani+=2*PI;
        Ugao::stepeni=radijani*(180/PI);
        Ugao::minute=60.001*(radijani*(180/PI)-stepeni);
        Ugao::sekunde=60.001*(60.001*(radijani*(180/PI)-stepeni)-minute);
    }
    void Postavi(int stepeni, int minute, int sekunde) {
        double s=stepeni;
        s+=double(sekunde)/3600+double(minute)/60;
        s=std::fmod(s, 360.);
        while(s<0) s+=360;
        Ugao::stepeni=s;
        double min=60.001*(s-Ugao::stepeni);
        Ugao::minute=min;
        Ugao::sekunde=60.001*(min-Ugao::minute);
    };
    double DajRadijane() const {double st=stepeni; st+=double(sekunde)/3600+double(minute)/60; return st*(PI/180);};
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde) {stepeni=DajStepene(); minute=DajMinute(); sekunde=DajSekunde();}
    int DajStepene() const {return stepeni;}
    int DajMinute() const {return minute;}
    int DajSekunde() const {return sekunde;}
    void Ispisi() const {std::cout<<std::fixed<<std::setprecision(5)<<DajRadijane()<<std::endl;}
    void IspisiKlasicno() const {std::cout<<std::fixed<<std::setprecision(5)<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec"<<std::endl;}
    Ugao &SaberiSa (const Ugao &u) {Postavi(stepeni+u.stepeni, minute+u.minute, sekunde+u.sekunde); return *this;};
    Ugao &PomnoziSa (double x) {Postavi(stepeni*=x, minute*=x, sekunde*=x); return *this;};
    friend Ugao ZbirUglova (const Ugao &u1, const Ugao &u2);
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};
Ugao ZbirUglova (const Ugao &u1, const Ugao &u2) {
    return u1.DajRadijane()+u2.DajRadijane();
}
Ugao ProduktUglaSaBrojem (const Ugao &u, double x) {
    return u.DajRadijane()*x;
}
int main ()
{
    Ugao u;
    u.Postavi(2.8);
    std::cout<<"Prvi ugao: "<<std::endl<<"radijani: "<<u.DajRadijane()<<std::endl;
    int stepeni, minute, sekunde;
    u.OcitajKlasicneJedinice(stepeni, minute, sekunde);
    std::cout<<"stepeni: "<<stepeni<<", minute: "<<minute<<", sekunde: "<<sekunde<<std::endl;
    std::cout<<"radijani: ";
    u.Ispisi();
    Ugao u2(2,3,4);
    std::cout<<"Drugi ugao: ";
    u2.IspisiKlasicno();
    u2.Postavi(4,5,6);
    std::cout<<"Drugi ugao nakon postavljanja: "<<std::endl;
    std::cout<<"stepeni: "<<u2.DajStepene()<<", minute: "<<u2.DajMinute()<<", sekunde: "<<u2.DajSekunde()<<std::endl;
    std::cout<<"Prvi ugao sabran s realnim brojem: ";
    u.SaberiSa(2.2).Ispisi();
    std::cout<<"Prvi ugao pomonozen s realnim brojem: ";
    u.PomnoziSa(5).Ispisi();
    Ugao u3(ZbirUglova(u, u2));
    std::cout<<"Zbir prvog i drugog ugla: (klasicno i radijani) "<<std::endl;
    u3.IspisiKlasicno();
    std::cout<<ZbirUglova(u, u2).DajRadijane()<<std::endl;
    std::cout<<"Produkt zbira prvog i drugog ugla s realnim brojem: ";
    std::cout<<ProduktUglaSaBrojem(u3, 1.5).DajRadijane()<<std::endl;

	return 0;
}