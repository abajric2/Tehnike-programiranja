//TP 2021/2022: Zadaća 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>

int CiklickaPermutacija (std::vector<int> v1, std::vector<int> v2) {
    if(v1.size()!=v2.size()) return -1;
    if(v1.size()==0) return 0;
    int pomak=0;
    while(pomak<v1.size()) {
        int brojac=0;
        for(int i=0, j=i+pomak; brojac<v1.size(); i++, j++, brojac++) {
            if(j>=v1.size()) j=0;
            if(v1.at(j)!=v2.at(i)) break;            
        }
        if(brojac==v1.size()) return pomak;
        pomak++;
    }
    return -1;
}

int main ()
{
    std::vector<int> v1;
    int element;
    std::cout<<"Prva sekvenca: "<<std::endl;
    while(std::cin>>element) v1.push_back(element);
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::vector<int> v2;
    std::cout<<"Druga sekvenca: "<<std::endl;
    while(std::cin>>element) v2.push_back(element);
    if(CiklickaPermutacija(v1, v2)==-1) std::cout<<"Druga sekvenca nije ciklicka permutacija prve.";
    else std::cout<<"Druga sekvenca je ciklicka permutacija prve s pomakom "<<CiklickaPermutacija(v1, v2)<<".";

	return 0;
}
