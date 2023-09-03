//TP 2021/2022: LV 8, Zadatak 1
#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

struct Vrijeme {
    int sati, minute, sekunde;
};

void TestirajVrijeme (const Vrijeme &v) {
    if(v.sekunde<0 || v.sekunde>59 || v.minute<0 || v.minute>59 || v.sati<0 || v.sati>23) throw std::domain_error("Neispravno vrijeme");
}

void IspisiVrijeme (const Vrijeme &v) {
    try {
        TestirajVrijeme(v);
    }
    catch(std::domain_error) {
        throw;
    }
    std::cout<<std::setfill('0')<<std::setw(2)<<v.sati<<":"<<std::setw(2)<<v.minute<<":"<<std::setw(2)<<v.sekunde;
}

Vrijeme SaberiVrijeme (const Vrijeme &v1, const Vrijeme &v2) {
    try {
        TestirajVrijeme(v1); TestirajVrijeme(v2);
    }
    catch(std::domain_error) {
        throw;
    }
    Vrijeme v3;
    int sekunde=v1.sekunde+v2.sekunde, minute=v1.minute+v2.minute;
    if(sekunde<=59) v3.sekunde=sekunde;
    else {
        v3.sekunde=sekunde-60;
        minute++;
    }
    int sati=v1.sati+v2.sati;
    if(minute<=59) v3.minute=minute;
    else {
        v3.minute=minute-60;
        sati++;
    }
    if(sati<=23) v3.sati=sati;
    else v3.sati=sati-24;
    return v3;
}
Vrijeme UnesiVrijeme() {
    Vrijeme v;
    std::cin>>v.sati>>v.minute>>v.sekunde;
    return v;
}
int main ()
{ 
    try {
    std::cout<<"Unesite prvo vrijeme (h m s): "<<std::endl;
    auto v1=UnesiVrijeme();
    TestirajVrijeme(v1);
    std::cout<<"Unesite drugo vrijeme (h m s): "<<std::endl;
    auto v2=UnesiVrijeme();
    TestirajVrijeme(v2);
    std::cout<<"Prvo vrijeme: ";
    IspisiVrijeme(v1);
    std::cout<<std::endl<<"Drugo vrijeme: ";
    IspisiVrijeme(v2);
    std::cout<<std::endl<<"Zbir vremena: ";
    IspisiVrijeme(SaberiVrijeme(v1, v2));
    }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what();
    }
	return 0;
}
