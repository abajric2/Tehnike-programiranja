//TP 2021/2022: LV 14, Zadatak 1
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

class Datum {
    int dan, mjesec, godina;
    public:
    Datum(int d, int m, int g) : dan(d), mjesec(m), godina(g) {}
    int DajDan() const {return dan;}
    int DajMjesec() const {return mjesec;}
    int DajGodinu() const {return godina;}
};
class Temperature {
    Datum d;
    std::string komentar;
    std::vector<double> mjerenja;
    public:
    Temperature(int d, int m, int g, std::string s, std::vector<double> v) : d(d, m, g), komentar(s), mjerenja(v) {}
    const Datum &DajDatum() const {return d;}
    std::string DajKomentar() const {return komentar;}
    double DajMinimalnuTemperaturu() const;
    double DajMaksimalnuTemperaturu() const;
    double DajProsjecnuTemperaturu() const;
    int DajDuzinuTeksta() const {return komentar.length();}
};
double Temperature::DajMinimalnuTemperaturu() const {return *std::min_element(mjerenja.begin(), mjerenja.end());}
double Temperature::DajMaksimalnuTemperaturu() const {return *std::max_element(mjerenja.begin(), mjerenja.end());}
double Temperature::DajProsjecnuTemperaturu() const {
    double suma=0; 
    std::for_each(mjerenja.begin(), mjerenja.end(), [&suma](double el){suma+=el;});
    return suma/mjerenja.size();
}
int main ()
{
    std::ifstream dat("TEMPERATURE.TXT");
    if(!dat) {
        std::cout<<"Datoteka TEMPERATURE.TXT ne postoji!"<<std::endl; return 1;
    }
    std::vector<Temperature> v;
    for(;;) {
        int dan, mjesec, godina;
        char znak;
        dat>>dan>>znak>>mjesec>>znak>>godina;
        dat.ignore(10000, '\n');
        if(!dat) {
            if(dat.eof()) break;
            else {
                std::cout<<"Problemi pri citanju datoteke TEMPERATURE.TXT"<<std::endl; return 2;
            }
        }
        std::string red;
        std::getline(dat, red);
        if(!dat) {
            std::cout<<"Problemi pri citanju datoteke TEMPERATURE>.TXT"<<std::endl; return 3;
        }
        double el;
        char z;
        std::vector<double> t;
        while(dat>>el) {
            t.push_back(el);
            if(!(dat>>z) || z!=',') break;
        }
        if(dat.eof()) {
            v.push_back(Temperature(dan, mjesec, godina, red, t));
            break;
        }

        dat.seekg(-int(sizeof(z)), std::ios::cur);
        v.push_back(Temperature(dan, mjesec, godina, red, t));
    }
    std::sort(v.begin(), v.end(), [](Temperature el1, Temperature el2) {
        if(el1.DajDatum().DajGodinu()<el2.DajDatum().DajGodinu()) return true;
        else if(el1.DajDatum().DajGodinu()>el2.DajDatum().DajGodinu()) return false;
        else if(el1.DajDatum().DajMjesec()<el2.DajDatum().DajMjesec()) return true;
        else if(el1.DajDatum().DajMjesec()>el2.DajDatum().DajMjesec()) return false;
        else if(el1.DajDatum().DajDan()<el2.DajDatum().DajDan()) return true;
        else if(el1.DajDatum().DajDan()>el2.DajDatum().DajDan()) return false;
        else return el1.DajProsjecnuTemperaturu()<el2.DajProsjecnuTemperaturu();
    });
    std::ofstream izlaz("IZVJESTAJ.TXT");
    for(int i=0; i<v.size(); i++) {
        izlaz<<v[i].DajKomentar()<<std::endl;
        std::string pomocni(v[i].DajDuzinuTeksta(), '-');
        auto temp=izlaz.precision();
        izlaz<<pomocni<<std::endl<<"Datum mjerenja: "<<v[i].DajDatum().DajDan()<<"/"<<v[i].DajDatum().DajMjesec()<<"/"<<v[i].DajDatum().DajGodinu()<<
        std::endl<<"Minimalna temperatura: "<<v[i].DajMinimalnuTemperaturu()<<std::endl<<"Maksimalna temperatura: "<<v[i].DajMaksimalnuTemperaturu()<<
        std::endl<<"Prosjecna temperatura: "<<std::fixed<<std::setprecision(2)<<v[i].DajProsjecnuTemperaturu()<<std::endl<<std::endl;
        izlaz.unsetf(std::ios::floatfield); izlaz.precision(temp);
    }
	return 0;
}
