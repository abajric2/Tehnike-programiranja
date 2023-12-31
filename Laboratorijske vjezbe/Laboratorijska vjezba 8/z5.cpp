//TP 2021/2022: LV 8, Zadatak 5
#include <iostream>
#include <tuple>

typedef std::tuple<double, double, double> Vektor3d;

void UnesiVektor(Vektor3d &v) {
    double x, y, z;
 std::cout << "X = "; std::cin >> x;
 std::cout << "Y = "; std::cin >> y;
 std::cout << "Z = "; std::cin >> z;
 v=std::make_tuple(x,y,z);
}
Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
 return {std::get<0>(v1) + std::get<0>(v2), std::get<1>(v1) + std::get<1>(v2), std::get<2>(v1) + std::get<2>(v2)};
}
Vektor3d VektorskiProizvod(const Vektor3d &v1, const Vektor3d &v2) {
    double v1x, v1y, v1z;
    std::tie(v1x, v1y, v1z)=v1;
    double v2x, v2y, v2z;
    std::tie(v2x, v2y, v2z)=v2;
    return {v1y * v2z - v1z * v2y, v1z * v2x - v1x * v2z, v1x * v2y - v1y * v2x};
}
void IspisiVektor(const Vektor3d &v) {
 std::cout << "{" << std::get<0>(v) << "," << std::get<1>(v) << "," << std::get<2>(v) << "}";
}
int main() {
 Vektor3d a, b;
 std::cout << "Unesi prvi vektor:\n";
 UnesiVektor(a);
 std::cout << "Unesi drugi vektor:\n";
 UnesiVektor(b);
 std::cout << "Suma ova dva vektora je: ";
 IspisiVektor(ZbirVektora(a, b));
 std::cout << std::endl << "Njihov vektorski prozivod je: ";
 IspisiVektor(VektorskiProizvod(a, b));
 return 0;
}

