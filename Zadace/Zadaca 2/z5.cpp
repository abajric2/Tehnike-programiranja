//TP 2021/2022: Zadaća 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <type_traits>
#include <new>
#include <vector>
#include <deque>

template <typename IterTip>
int BrojElemenata (IterTip pocetak, IterTip iza_kraja) {
    int br_el=0;
    while(pocetak!=iza_kraja) {
        br_el++;
        pocetak++;
    }
    return br_el;
}
template <typename Tip, typename IterTip1, typename IterTip2>
auto GeneraliziraniSpoljasnjiProizvod (IterTip1 p1, IterTip1 k1, IterTip2 p2, IterTip2 k2, Tip fun) {
    int br_redova=BrojElemenata(p1, k1), br_kolona=BrojElemenata(p2, k2);
    std::remove_reference_t<decltype(fun(*p1,*p2))> **mat{};
    try {
        mat=new std::remove_reference_t<decltype(fun(*p1,*p2))>*[br_redova]{};
        for(int i=0; i<br_redova; i++) *(mat+i)=new std::remove_reference_t<decltype(fun(*p1,*p2))>[br_kolona];
        auto pomocni=p2;
        for(int i=0; i<br_redova; i++) {
            for(int j=0; j<br_kolona; j++) {
                *(*(mat+i)+j)=fun(*p1, *pomocni++);
            }
            p1++; pomocni=p2;
        }
    }
    catch(std::bad_alloc) {
        if(mat) for(int i=0; i<br_redova; i++) delete[] *(mat+i);
        delete[] mat;
        throw std::range_error("Nema dovoljno memorije!");            
    }
    return mat;
}
double f(double x, double y) {
    return x+2*y;
}

int main ()
{
    int n1;
    std::cout<<"Duzina prve sekvence: "<<std::endl;
    std::cin>>n1;   
    std::vector<double> v(n1);
    std::cout<<"Elementi prve sekvence: "<<std::endl;
    for(int i=0; i<n1; i++) std::cin>>v.at(i);
    int n2;
    std::cout<<"Duzina druge sekvence: "<<std::endl;
    std::cin>>n2;
    std::deque<double> d(n2);
    std::cout<<"Elementi druge sekvence: "<<std::endl;
    for(int i=0; i<n2; i++) std::cin>>d.at(i);
    std::cout<<"Generalizirani spoljasnji proizvod uz f(x,y)=x+2y:"<<std::endl;
    try {
        double **mat{};
        mat=GeneraliziraniSpoljasnjiProizvod(v.begin(), v.end(), d.begin(), d.end(), f);
        for(int i=0; i<n1; i++) {
            for(int j=0; j<n2; j++) std::cout<<*(*(mat+i)+j)<<" ";
            std::cout<<std::endl;
        }
        if(mat) for(int i=0; i<n1; i++) delete[] *(mat+i);
        delete[] mat;
    }
    catch(std::range_error izuzetak) {
        std::cout<<izuzetak.what();
    }
	return 0;
}
