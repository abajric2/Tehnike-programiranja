//TP 2021/2022: LV 3, Zadatak 6
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>

typedef std::vector<std::vector<int>> Matrica;

Matrica KreirajMatricu(int broj_redova, int broj_kolona) {
    return Matrica(broj_redova, std::vector<int>(broj_kolona));
}
Matrica KroneckerovProizvod (std::vector<int> a, std::vector<int> b) {
    Matrica c=KreirajMatricu(a.size(), b.size());
    for(int i=0; i<a.size(); i++) 
        for(int j=0; j<b.size(); j++) c[i][j]=a[i]*b[j];
    return c;
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
void IspisiMatricu(Matrica m) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++) std::cout<<std::setw(NajvecaSirina(m)+1)<<m[i][j];
        std::cout<<std::endl;
    }
}
int main ()
{
    int m;
    std::cout<<"Unesite broj elemenata prvog vektora: "<<std::endl;
    std::cin>>m;
    std::vector<int> v1(m);
    std::cout<<"Unesite elemente prvog vektora: "<<std::endl;
    for(int i=0; i<m; i++) std::cin>>v1[i];
    int n;
    std::cout<<"Unesite broj elemenata drugog vektora: "<<std::endl;
    std::cin>>n;
    std::cout<<"Unesite elemente drugog vektora: "<<std::endl;
    std::vector<int> v2(n);
    for(int i=0; i<n; i++) std::cin>>v2[i];
    Matrica M=KroneckerovProizvod(v1, v2);
    IspisiMatricu(M);
	return 0;
}
