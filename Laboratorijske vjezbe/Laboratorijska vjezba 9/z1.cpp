/* 
    TP 16/17 (LV 9, Zadatak 1)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cmath>

class Vektor3d {
    double x, y, z;
    public:
    void Postavi (double x, double y, double z) {
        Vektor3d::x=x; Vektor3d::y=y; Vektor3d::z=z;
    }
    Vektor3d &PostaviX (double x) {Vektor3d::x=x; return *this;}
    Vektor3d &PostaviY (double y) {Vektor3d::y=y; return *this;}
    Vektor3d &PostaviZ (double z) {Vektor3d::z=z; return *this;}
    void Ocitaj (double &x, double &y, double &z) const {
        x=Vektor3d::x; y=Vektor3d::y; z=Vektor3d::z;
    }
    void Ispisi() const {
        std::cout<<"{"<<x<<","<<y<<","<<z<<"}";
    }
    double DajX() const {return x;};
    double DajY() const {return y;};
    double DajZ() const {return z;};
    double DajDuzinu() const {return std::sqrt(x*x+y*y+z*z);}
    Vektor3d &PomnoziSaSkalarom (double s) {
        x*=s; y*=s; z*=s;
        return *this;
    }
    Vektor3d &SaberiSa (const Vektor3d &v) {
        x+=v.x; y+=v.y; z+=v.z;
        return *this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d ZbirVektora (const Vektor3d &v1, const Vektor3d &v2) {
    Vektor3d v3;
    v3.x=v1.x+v2.x; v3.y=v1.y+v2.y; v3.z=v1.z+v2.z;
    return v3;
}

int main ()
{
    double x, y, z;
    std::cout<<"Unesite koordinate vektora: "<<std::endl;
    std::cin>>x>>y>>z;
    Vektor3d v1;
    v1.Postavi(x, y, z);
    std::cout<<"Unijeli ste: ";
    v1.Ocitaj(x, y, z);
    std::cout<<"X="<<x<<", Y="<<y<<", Z="<<z<<std::endl;
    std::cout<<"Duzina unesenog vektora iznosi "<<v1.DajDuzinu()<<std::endl;
    double skalar;
    std::cout<<"Unesite skalar: "<<std::endl;
    std::cin>>skalar;
    std::cout<<"Vektor pomnozen sa unesenim skalarom,a zatim sabran sam sa sobom je: ";
    v1.PomnoziSaSkalarom(skalar).SaberiSa(v1).Ispisi();
    std::cout<<std::endl;
    double x2, y2, z2;
    std::cout<<"Unesite koordinate drugog vektora: "<<std::endl;
    std::cin>>x2>>y2>>z2;
    Vektor3d v2;
    v2.PostaviX(x2).PostaviY(y2).PostaviZ(z2);
    std::cout<<"Unijeli ste: ";
    std::cout<<"X="<<v2.DajX()<<", Y="<<v2.DajY()<<", Z="<<v2.DajZ()<<std::endl;
    Vektor3d v3=ZbirVektora(v1, v2);
    std::cout<<"Zbir unesena dva vektora je: ";
    v3.Ispisi();

	return 0;
}