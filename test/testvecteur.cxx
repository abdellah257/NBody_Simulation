
#include "vecteur.hxx"

using namespace std;

int main() {
    Vecteur v1 = Vecteur();
    Vecteur v2(2,2,2);
    Vecteur v3(v2);
    Vecteur v4 = v3;
    cout << "elements of the vector v1: " << v1 << endl;
    cout << "elements of the vector v2: " << v2 << endl;
    cout << "elements of the vector v3: " << v3 << endl;
    cout << "elements of the vector v4: " << v4 << endl;
    v4 *= 3;
    cout << "elements of the vector v4: " << v4 << endl;
    v4 = v4 * 3;
    cout << "elements of the vector v4: " << v4 << endl;
    v4 = v4 + v2;
    cout << "elements of the vector v4: " << v4 << endl;
    Vecteur scalaire = v4 + 2;
    cout << "v4 + 2 =  " << scalaire << std::endl;
    Vecteur div = v4/0;
    cout << "v4 / 0 =  " << div << endl;
    return EXIT_SUCCESS;
}