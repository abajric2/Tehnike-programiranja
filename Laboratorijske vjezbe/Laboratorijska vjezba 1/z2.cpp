//TP 2016/2017: Tutorijal 1, Zadatak 2
#include <iostream>
#include <cmath>
int main ()
{
    double a, b, c;
    std::cout<<"Unesite tri broja: ";
    std::cin>>a>>b>>c;
    if(!(a>0 && b>0 && c>0 && a+b>c && a+c>b && b+c>a)) {
        std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!"<<std::endl;
        return 0;
    }
    double obim=a+b+c;
    double s=(a+b+c)/2;
    double povrsina=std::sqrt(s*(s-a)*(s-b)*(s-c));
    std::cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<obim<<"."<<std::endl;
    std::cout<<"Njegova povrsina iznosi "<<povrsina<<"."<<std::endl;
    double alfa=std::acos((a*a+b*b-c*c)/(2*a*b));
    alfa*=180/(4*atan(1));
    double beta=std::acos((b*b+c*c-a*a)/(2*b*c));
    beta*=180/(4*atan(1));
    double gama=std::acos((a*a+c*c-b*b)/(2*a*c));
    gama*=180/(4*atan(1));
    double min;
    if(alfa<=beta && alfa<=gama) min=alfa;
    else if(beta<=alfa && beta<=gama) min=beta;
    else if(gama<=alfa && gama<=beta) min=gama;
    double stepeni=int(min);
    double minute=int((min-stepeni)*60);
    double sekunde=int((min-stepeni-minute/60)*3600);
    std::cout<<"Njegov najmanji ugao ima "<<stepeni<<" stepeni, "<<minute<<" minuta i "<<sekunde<<" sekundi."<<std::endl;
	return 0;
}