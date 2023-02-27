#include "univers.hxx"
#include "particule.hxx"
#include "vecteur.hxx"

int main(){
    double rayon = 100;
    Vecteur L = Vecteur(100, 100, 100);
    Univers* univ = new Univers(2, rayon, L);
    std::deque<Particle> particleList;
    Particle p1;
    p1.masse = 1; p1.id = 1;
    p1 .position = Vecteur(); p1.vitesse = Vecteur();
    univ->addParticle(p1);
    Particle p2;
    p2.masse = 3.0e-6; p2.id = 2;
    p2.position = Vecteur(0, 1, 0); p2.vitesse = Vecteur(-1, 0, 0);
    univ->addParticle(p2);
    Particle p3;
    p3.masse = 9.55e-4; p3.id = 3;
    p3.position = Vecteur(0, 5.36, 0); p3.vitesse = Vecteur(-0.425, 0, 0);
    univ->addParticle(p3);
    Particle p4;
    p4.masse = 1.e-14; p4.id = 4;
    p4.position = Vecteur(34.75, 0, 0); p4.vitesse = Vecteur(0, 0.0296, 0);
    univ->addParticle(p4);

    double dt = 0.015;
    double t_end = 468.5;
    univ->print_univers_positions();
    univ->evolution_perm(dt, t_end);
}