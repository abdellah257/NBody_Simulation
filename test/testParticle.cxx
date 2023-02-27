#include "univers.hxx"
#include "particule.hxx"
#include "vecteur.hxx"
#include <deque>

int main(){
    Particle p = Particle();
    p.affiche();
    std::cout << std::endl;
    p.masse = 10;
    p.vitesse = Vecteur(0.2, 0.2, 0.2);
    p.old_force = Vecteur(0.1, 0.1, 0.1);
    p.affiche();
    std::cout << std::endl;
    p.advance_position(2);
    p.advance_vitesse(0.3);
    p.affiche();
    std::cout << std::endl;
    Particle q = Particle();
    q.masse = 5;
    q.position = Vecteur(10, 10, 10);
    p.updateForce(q);
    p.affiche();
}