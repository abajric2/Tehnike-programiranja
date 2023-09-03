/* 
    TP 16/17 (LV 9, Zadatak 2)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cmath>

class Vektor3d {
    double koordinate[3];
    public:
    void Postavi (double x, double y, double z) {
        koordinate[0]=x; koordinate[1]=y; koordinate[2]=z;
    }
    Vektor3d &PostaviX (double x) {koordinate[0]=x; return *this;}
    Vektor3d &PostaviY (double y) {koordinate[1]=y; return *this;}
    Vektor3d &PostaviZ (double z) {koordinate[2]=z; return *this;}
    void Ocitaj (double &x, double &y, double &z) const {
        x=koordinate[0]; y=koordinate[1]; z=koordinate[2];
    }
    void Ispisi() const {
        std::cout<<"{"<<koordinate[0]<<","<<koordinate[1]<<","<<koordinate[2]<<"}";
    }
    double DajX() const {return koordinate[0];};
    double DajY() const {return koordinate[1];};
    double DajZ() const {return koordinate[2];};
    double DajDuzinu() const {return std::sqrt(koordinate[0]*koordinate[0]+koordinate[1]*koordinate[1]+koordinate[2]*koordinate[2]);}
    Vektor3d &PomnoziSaSkalarom (double s) {
        koordinate[0]*=s; koordinate[1]*=s; koordinate[2]*=s;
        return *this;
    }
    Vektor3d &SaberiSa (const Vektor3d &v) {
        koordinate[0]+=v.koordinate[0]; koordinate[1]+=v.koordinate[1]; koordinate[2]+=v.koordinate[2];
        return *this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d ZbirVektora (const Vektor3d &v1, const Vektor3d &v2) {
    Vektor3d v3;
    v3.koordinate[0]=v1.koordinate[0]+v2.koordinate[0]; v3.koordinate[1]=v1.koordinate[1]+v2.koordinate[1]; v3.koordinate[2]=v1.koordinate[2]+v2.koordinate[2];
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