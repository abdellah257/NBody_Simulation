#include "univers.hxx"
#include "particule.hxx"
#include "vecteur.hxx"
#include <deque>
#include <chrono>
#include <cmath>


int main() {
    // int k = 1;
    // int TAILLE = pow(pow(2,k), 3);
    auto start = std::chrono::steady_clock::now();
    Vecteur L = Vecteur(250, 140, 0);
    double r = 2.5;
    double d = pow(2, 1/6);
    Univers* univ = new Univers(2, r, L);
    int N1 = 40;
    Vecteur v = Vecteur(90, 75, 0);
    for (int i=0; i< N1; i++) {
        for (int j=0; j< N1; j++) {
            Particle* p = new Particle();
            p->position = v + d*Vecteur(i, j, 0);
            p->vitesse = Vecteur(0, -10, 0);
            p->masse = 1;
            p->id = 1;
            p->categorie = 1;
            p->force = Vecteur();
            univ->addParticle(*p);
            univ->nb_particles += 1;
        }
    }
    int N2 = 160;
    Vecteur w = Vecteur(20, 0, 0);
    for (int i=0; i< N2; i++) {
        for (int j=0; j< N1; j++) {
            Particle *p = new Particle();
            p->position = w + d*Vecteur(i, j, 0);
            p->vitesse = Vecteur(0, 0, 0);
            p->masse = 1;
            p->id = 2;
            p->categorie = 2;
            p->force = Vecteur();
            univ->addParticle(*p);
            univ->nb_particles += 1;
        }
    }
    univ->evolution_vis(0.05, 5.5);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";


    // for (int i = 0; i< univ->nb_particles; i++){
    //     univ->particles[i].affiche();
    //     std::cout<< std::endl;
    // }
}