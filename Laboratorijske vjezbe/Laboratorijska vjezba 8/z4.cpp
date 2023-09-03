//TP 2021/2022: LV 8, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <map>

std::string ZamijeniPremaRjecniku (std::string s, std::map<std::string, std::string> m) {
    std::string s2;
    for(auto i=s.begin(); i!=s.end(); i++) {
        if(*i==' ') s2.push_back(*i);
        else {
            std::string rijec;
            while(i!=s.end() && *i!=' ') rijec.push_back(*i++);
            i--;
            if(m.count(rijec)) s2.insert(s2.size(), m[rijec]);
            else s2.insert(s2.size(), rijec);
        }
    }
    return s2;
}
int main ()
{
    std::map<std::string, std::string> m{{"test", "proba"}, {"recenica", "rijec"}, {"da", "ne"}, {"dan", "noc"}};
    std::string s;
    std::cout<<"Unesite recenicu: "<<std::endl;
    std::getline(std::cin, s);
    s=ZamijeniPremaRjecniku(s, m);
    std::cout<<"Modifikovana recenica glasi: "<<s;
	return 0;
}
