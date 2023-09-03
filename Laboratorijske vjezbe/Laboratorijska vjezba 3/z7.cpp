//TP 2021/2022: LV 3, Zadatak 7
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <stdexcept>

typedef std::vector<std::vector<int>> Matrica;

Matrica PascalovTrougao (int n) {
    if(n<0) throw std::domain_error("Broj redova ne smije biti negativan");
    Matrica m;
    if(n==0) return m;
    m.resize(n);
    for(int i=0; i<n; i++) m[i].resize(i+1);
    m[0][0]=1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(j<i && j>=0 && i>=1) m[i][j]+=m[i-1][j];
            if(j<=i && i>=1 && j>=1) m[i][j]+=m[i-1][j-1];
        }
    }
    return m;
}
int NajvecaSirina (Matrica m) {
    if(m.size()==0) return 0;
    int max_sirina=0;
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++) {
            if(m[i].size()==0) return 0;
            int br_cifara=0;
            if(m[i][j]<0) br_cifara++;
            do {
                br_cifara++;
                m[i][j]/=10;
            } while(m[i][j]!=0);
            if(br_cifara>max_sirina) max_sirina=br_cifara;
        }
    }
    return max_sirina;
}
int main ()
{
    int n;
    std::cout<<"Unesite broj redova: "<<std::endl;
    std::cin>>n;
    auto m=PascalovTrougao(n);
    int sirina=NajvecaSirina(m);
    for (auto red : m) {
        for (auto element : red) std::cout<<std::setw(sirina+1)<<element;
        std::cout<<std::endl;
    }
	return 0;
}
