//TP 2021/2022: LV 4, Zadatak 5
#include <iostream>
#include <cmath>
#include <vector>

typedef std::vector<double> VektorDouble;
typedef std::vector<std::string> VektorStringova;

template<typename NekiTip>
std::vector<NekiTip> Presjek(const std::vector<NekiTip> &v1, const std::vector<NekiTip> &v2) {
    std::vector<NekiTip> presjek;
    for(int i=0; i<v1.size(); i++) {
        for(int j=0; j<v2.size(); j++) {
            if(v1[i]==v2[j]) {
                int vec_ubacen=0;
                for(int k=0; k<presjek.size(); k++) if(v1[i]==presjek[k]) vec_ubacen=1;
                if(vec_ubacen) break;
                presjek.push_back(v1[i]);
            }
        }
    }
    return presjek;
}
void UnesiVektor (VektorDouble &v, int n) {
    v.resize(n);
    for(int i=0; i<n; i++) std::cin>>v[i];
}
void UnesiVektor (VektorStringova &v, int n) {
    v.resize(n);
    std::cin.ignore(10000, '\n');
    for(int i=0; i<n; i++) std::getline(std::cin, v[i]);
}
void IspisiVektor (const VektorDouble &v) {
    for(int i=0; i<v.size(); i++) std::cout<<v[i]<<" ";
}
void IspisiVektor (const VektorStringova &v) {
    for(int i=0; i<v.size(); i++) std::cout<<v[i]<<std::endl;
}
int main ()
{
    std::cout<<"Test za realne brojeve..."<<std::endl;
    int n1;
    std::cout<<"Unesite broj elemenata prvog vektora: "<<std::endl;
    std::cin>>n1;
    std::cout<<"Unesite elemente prvog vektora: "<<std::endl;
    VektorDouble v1;
    UnesiVektor(v1, n1);
    int n2;
    std::cout<<"Unesite broj elemenata drugog vektora: "<<std::endl;
    std::cin>>n2;
    std::cout<<"Unesite elemente drugog vektora: "<<std::endl;
    VektorDouble v2;
    UnesiVektor(v2, n2);
    auto presjek=Presjek(v1, v2);
    std::cout<<"Zajednicki elementi su: ";
    IspisiVektor(presjek);
    std::cout<<std::endl<<"Test za stringove..."<<std::endl;
    int l1;
    std::cout<<"Unesite broj elemenata prvog vektora: "<<std::endl;
    std::cin>>l1;
    std::cout<<"Unesite elemente prvog vektora (ENTER nakon svakog unosa): "<<std::endl;
    VektorStringova s1;
    UnesiVektor(s1, l1);
    int l2;
    std::cout<<"Unesite broj elemenata drugog vektora: "<<std::endl;
    std::cin>>l2;
    std::cout<<"Unesite elemente drugog vektora (ENTER nakon svakog unosa): "<<std::endl;
    VektorStringova s2;
    UnesiVektor(s2, l2);
    auto s3=Presjek(s1, s2);
    std::cout<<"Zajednicki elementi su: "<<std::endl;
    IspisiVektor(s3);
	return 0;
}
