#include "univers.hxx"
#include "particule.hxx"
#include "vecteur.hxx"
#include "cellule.hxx"
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <assert.h>

/**
 * @brief Constructeur par default de l'Univers avec dimensionde 3 et une cellule
 * 
 */
Univers::Univers(){
    initCellules();
    setNeighbours();
}
/**
 * @brief Constructeur de la classe Univers avec une Cellule
 * 
 * @param d             dimension
 * 
 */
Univers::Univers(int d){
    dim = d;
    initCellules();
    setNeighbours();
}

/**
 * @brief Constructeur de la classe Univers avec initialisation des Cellules
 * 
 * @param d             dimension
 * @param rayon         le rayon de courbure
 * @param longueur      le Vecteur de longueur caracteristique dans chaque direction.
 * 
 */
Univers::Univers(int d, double rayon, const Vecteur & longueur){
    dim = d;
    rc = rayon;
    Lc  = longueur;
    initCellules();
    setNeighbours();
}
/**
 * @brief Retourne la position de la cellule correspondante a une particule
 * 
 * @param p            une particule
 */
Vecteur Univers::index_position(const Particle &p){
    Vecteur nd = getDimension();
    Vecteur relative_position = Vecteur();
    for(int i = 0; i < dim; i++){
        relative_position(i) = p.position(i)/Lc(i);
    }
    Vecteur cellule_index = floor(scalaire(relative_position, nd));
    return cellule_index;
}
/**
 * @brief Retourne le nombre de cellules dans notre univers
 * 
 */
int Univers::size(){
    Vecteur nd = getDimension();
    int TAILLE = 1;
    for(int i = 0; i < dim; i++){
        TAILLE *= nd(i);
    }
    return TAILLE;
}
/**
 * @brief Ajoute une particule a l'univers
 * 
 * @param p            particule a ajouter
 */
void Univers::addParticle(Particle &p){
    Vecteur cellule_index = index_position(p);
    int TAILLE = size();
    for(int i = 0; i < TAILLE; i++){
        // std::cout << cellules[i]->id << " --- " << cellule_index << std::endl;
        if(cellule_index.equal(cellules[i]->id)){
            cellules[i]->addParticle(p);
        }
    }  
}
/**
 * @brief Creation des cellules dans notre univers
 * 
 */
void Univers::initCellules(){
    Vecteur nd = getDimension();
    for (int i = 0; i< int(nd(0)); i++){
        if(dim == 1){
            Vecteur id = Vecteur(i, 0, 0);
            Vecteur centre = scalaire( id+0.5, Vecteur(Lc(0)/nd(0), 0, 0));
            Cellule* c = new Cellule(dim, id, centre);
            cellules.push_back(c);
        }else{
            for (int j = 0; j< int(nd(1)); j++){
                if(dim == 2){
                    Vecteur id = Vecteur(i, j, 0);
                    Vecteur centre = scalaire( id+0.5, Vecteur(Lc(0)/nd(0), Lc(1)/nd(1), 0));
                    Cellule* c = new Cellule(dim, id, centre);
                    cellules.push_back(c);
                }
                else{
                    for (int k = 0; k< int(nd(2)); k++){
                        Vecteur id = Vecteur(i, j, k);
                        Vecteur centre = scalaire( id+0.5, Vecteur(Lc(0)/nd(0), Lc(1)/nd(1), Lc(2)/nd(2)));
                        Cellule* c = new Cellule(dim, id, centre);
                        cellules.push_back(c);
                    }
                }
            }
        }
    }
}
/**
 * @brief Initialise les voisins de chaque cellule
 * 
 */
void Univers::setNeighbours(){
    for(auto &c: cellules){
        c->setNeighbours(cellules);
    }
}
/**
 * @brief Retourne la dimansion de la grille dans chaque direction
 * 

 */
Vecteur Univers::getDimension(){
    Vecteur Nd = Lc / rc;
    return Vecteur(floor(Nd(0)), floor(Nd(1)), floor(Nd(2)));
}
/**
 * @brief La Methode de Calcul de forces de toute les particules de l'univers
 * 
 */
void Univers::compute_forces(){
    for( auto &it: cellules){
        it->computeForces(rc);
    }
}
/**
 * @brief fonction d'affichage des positions de toutes les particules de l'univers
 * 
 */
void Univers::print_univers_positions(){
    for( auto &it : cellules){
        for(auto it1 : it->particles){
            std::cout << it1.id << " ";
            it1.affiche_position();
            std::cout << std::endl;
        }
    }
}

/**
 * @brief La Mise a jour des particules dans la grille de cellules
 * 
 */
void Univers::update_cells(){
    for(auto &c : cellules){
        std::deque<Particle> p = c->particles;
        int n = c->particles.size();
        int j = 0;
        for(int i = 0; i<n; i++){
            Particle p = Particle();
            p = c->particles[i-j];
            Vecteur pos = index_position(p);
            if(!pos.equal(c->id)){
                addParticle(p);
                c->particles.erase(c->particles.begin()+i-j);
                j++;
            }
        }
    }
}
/**
 * @brief La Methode de Stromer avec un affichage des positions a chaque iteration
 * 
 * @param dt            le pas de temps
 * @param t_end         le temps final
 */
void Univers::evolution_perm(double dt, double t_end){
    double t = 0.;
    std::deque<Vecteur> f_old;
    compute_forces();
    while( t < t_end){
        t += dt;
        for(auto &it: cellules){
            for( auto &p : it->particles){
                p.advance_position(dt);
                p.old_force = p.force;
            }
        }
        update_cells();
        compute_forces();
        for(auto &it: cellules){
            for(auto &p : it->particles)
                p.advance_vitesse(dt);
        }
        // std::cout << "t = "<< t << std::endl;
        // if(t >= t_end){
        print_univers_positions();
        // }
    }
}

/**
 * @brief La Methode de Stromer avec un affichage des positions a la derniere iteration
 * 
 * @param dt            le pas de temps
 * @param t_end         le temps final
 */
void Univers::evolution(double dt, double t_end){
    double t = 0.;
    std::deque<Vecteur> f_old;
    compute_forces();
    while( t < t_end){
        t += dt;
        for(auto &it: cellules){
            for( auto &p : it->particles){
                p.advance_position(dt);
                p.old_force = p.force;
            }
        }
        update_cells();
        compute_forces();
        for(auto &it: cellules){
            for(auto &p : it->particles)
                p.advance_vitesse(dt);
        }
        // std::cout << "t = "<< t << std::endl;
        if(t >= t_end){
            print_univers_positions();
        }
    }
}

/**
 * @brief Mise en place des conditions aux limites par la methode de reflexion
 * 
 * @param p             particule
 * @param paroi_inf     paroi inferieure
 * @param paroi_sup     paroi superieure
 */
void Univers::reflexion(Particle p, double paroi_inf, double paroi_sup) {
    assert(paroi_inf < paroi_sup);

    if (p.position.vect[0] >= paroi_sup) {
        p.position = p.position - Vecteur(2 * (p.position.vect[0] - paroi_sup), 0, 0);
        p.vitesse = Vecteur(-p.vitesse.vect[0], p.vitesse.vect[1], p.vitesse.vect[2]);
    } else if (p.position.vect[0] <= paroi_inf) {
        p.position = p.position - Vecteur(2 * (p.position.vect[0] - paroi_inf), 0, 0);
        p.vitesse = Vecteur(-p.vitesse.vect[0], p.vitesse.vect[1], p.vitesse.vect[2]);
    }
    
    if (p.position.vect[1] >= paroi_sup) {
        p.position = p.position - Vecteur(0, 2 * (p.position.vect[1]- paroi_sup), 0);
        p.vitesse = Vecteur(p.vitesse.vect[0], -p.vitesse.vect[1], p.vitesse.vect[2]);
    } else if (p.position.vect[1] <= paroi_inf) {
        p.position = p.position - Vecteur(0, 2 * (p.position.vect[1] - paroi_inf), 0);
        p.vitesse = Vecteur(p.vitesse.vect[0], -p.vitesse.vect[1], p.vitesse.vect[2]);
    }

    if (p.position.vect[2] >= paroi_sup) {
        p.position = p.position - Vecteur(0, 0, 2 * (p.position.vect[2] - paroi_sup));
        p.vitesse = Vecteur(p.vitesse.vect[0], p.vitesse.vect[2], -p.vitesse.vect[2]);
    } else if (p.position.vect[2] <= paroi_inf) {
        p.position = p.position - Vecteur(0, 0, 2 * (p.position.vect[2] - paroi_inf));
        p.vitesse = Vecteur(p.vitesse.vect[0], p.vitesse.vect[2], -p.vitesse.vect[2]);
    }
}

/**
 * @brief Mise en place des conditions aux limites par la methode d'absorption
 * 
 * @param p             particule
 * @param index         indice de la particule
 * @param paroi_inf     paroi inferieure
 * @param paroi_sup     paroi superieure
 * @param cell          cellule contenant la particule
 */
void Univers::absorption(Particle p, int index, double paroi_inf, double paroi_sup, Cellule cell) {
    assert(paroi_sup >= paroi_inf);

    if ((p.position.vect[0] >= paroi_sup) || (p.position.vect[0] <= paroi_inf) ||
        (p.position.vect[1] >= paroi_sup) || (p.position.vect[1] <= paroi_inf) ||
        (p.position.vect[2] >= paroi_sup) || (p.position.vect[2] <= paroi_inf)) {
        cell.particles.erase(cell.particles.begin() + index);
        nb_particles--;
    }
}

/**
 * @brief Mise en place des conditions aux limites par la methode de periodicite
 * 
 * @param p             particule
 * @param paroi_inf     paroi inferieure
 * @param paroi_sup     paroi superieure
 */
void Univers::periodicite(Particle p, double paroi_inf, double paroi_sup) {
    assert(paroi_sup >= paroi_inf);

    if (p.position.vect[0] >= paroi_sup || p.position.vect[0] <= paroi_inf) {
        if (p.position.vect[0] < 0) {
            p.position = Vecteur(fmod(p.position.vect[0], paroi_sup - paroi_inf) + paroi_sup - paroi_inf, p.position.vect[1], p.position.vect[2]);
        } else {
            p.position = Vecteur(fmod(p.position.vect[0], paroi_sup - paroi_inf), p.position.vect[1], p.position.vect[2]);
        }
        
    }

    if (p.position.vect[1] >= paroi_sup || p.position.vect[1] <= paroi_inf) {
        if (p.position.vect[1] < 0) {
            p.position = Vecteur(p.position.vect[0], fmod(p.position.vect[1], paroi_sup - paroi_inf) + paroi_sup - paroi_inf, p.position.vect[2]);
        } else {
            p.position = Vecteur(p.position.vect[0], fmod(p.position.vect[1], paroi_sup - paroi_inf), p.position.vect[2]);
        }
    }

    if (p.position.vect[2] >= paroi_sup || p.position.vect[2] <= paroi_inf) {
        if (p.position.vect[2] < 0) {
            p.position = Vecteur(p.position.vect[0], p.position.vect[1], fmod(p.position.vect[2], paroi_sup - paroi_inf) + paroi_sup - paroi_inf);
        } else {
            p.position = Vecteur(p.position.vect[0], p.position.vect[1], fmod(p.position.vect[2], paroi_sup - paroi_inf));
        }
    }
}


/**
 * @brief modification de la vitesse en limitant l'énergie cinétique
 * 
 * @param energieD      Energie seuil
 */
void Univers::energieCinetique(double energieD) {
    double energiec = 0;
    for(auto &it: cellules){
        for(auto &p : it->particles){
            energiec += 0.5 * p.masse * (pow(p.getV()(0),2) + pow(p.getV()(1),2) + pow(p.getV()(2),2));
        }
    }
    for(auto &it: cellules){
        for(auto &p : it->particles){
            p.vitesse *= sqrt(energieD/energiec);
        }
    }
}

/**
 * @brief calcul des parametres des particules apres plusieurs iterations
 * 
 * @param dt            le pas des iterations
 * @param t_end         temps final
 */
void Univers::evolution_vis(double dt, double t_end){
    double t = 0.;
    int nb_iter = 0;
    std::deque<Vecteur> f_old;
    compute_forces();
    visualisation(cellules, std::to_string(t/100));

    while( t < t_end){
        t += dt;

        for(auto &it: cellules){
            for(auto &p : it->particles){
                p.advance_position(dt);
                p.old_force = p.force;
            }
        }

        update_cells();
        compute_forces();

        for(auto &it: cellules){
            for(auto &p : it->particles)
                p.advance_vitesse(dt);
        }

        nb_iter++;
        if (nb_iter % 1000 == 0) {
            energieCinetique(0.005);
        }
        
        // affichage des points
        visualisation(cellules, std::to_string(t/100));
    }

}



/**
 * @brief fonction de generation des fichiers pour la visualisation avec paraview
 * 
 * @param particles     liste des particules
 * @param txt           indice du fichier a creer
 */
void visualisation(std::deque<Cellule*> cells, std::string txt) {
    std::deque<Particle> particles;
    for(auto &it : cells){
        for( auto &p : it->particles){
            particles.push_back(p);
        }
    }
    std::ofstream file;
    file.open("../demo/data" + txt + ".vtu");
    if (file.fail()) {std::cout <<"erreur\n";}
    file << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\"> \n" <<
    "  <UnstructuredGrid>\n" <<
    "    <Piece NumberOfPoints=\"" << particles.size() << "\" NumberOfCells=\"0\">\n" <<
    "      <Points>\n" <<
    "        <DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n";

    for (long unsigned int i = 0; i < particles.size(); i++) {
        file << particles[i].position(0) << " " <<  particles[i].position(1) << " " << particles[i].position(2) << " ";
    }
    file << "\n";
    file << "        </DataArray>\n" <<
    "      </Points>\n" <<
    "      <PointData Vectors=\"vector\">\n" <<
    "        <DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\n";

    for (long unsigned int i = 0; i < particles.size(); i++) {
        file << particles[i].vitesse(0) << " " <<  particles[i].vitesse(1) << " " << particles[i].vitesse(2) << " ";
    }
    file << "\n";
    file << "        </DataArray>\n" <<
    "        <DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">\n";

    for (long unsigned int i = 0; i < particles.size(); i++) {
        file << particles[i].masse << " ";
    }
    file << "\n";
    file << "        </DataArray>\n" <<
    "      </PointData>\n" <<
    "      <Cells>\n" <<
    "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n" <<
    "        </DataArray>\n" <<
    "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n" <<
    "        </DataArray>\n" <<
    "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n" <<
    "        </DataArray>\n" <<
    "      </Cells>\n" <<
    "    </Piece>\n" <<
    "  </UnstructuredGrid>\n" <<
    "</VTKFile>\n";
}