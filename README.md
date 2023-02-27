
Bonjour,

Le Rapport est dans le repertoire /doc

Pour exécuter le code, il faut tout d'abord accéder au répertoire /build, puis exécuter la commande suivante dans le terminal:
> cmake ..

Il faut ensuite exécuter la commande:
> make

Les fichiers tests sont générés dans le dossier /test de build.

Pour exécuter les résultats du tp des equations differentielles, veuillez entrer la commande:
./test/edo
./test/trace

Pour exécuter les résultats de la simulation de la collision entre deux objets, veuillez entrer la commande:
./test/testUnivers

Pour tester les classes Particle et Vecteur, veuillez entrer la commande:
./test/googletest

Pour tester la méthode de Störmer-Verlet, veuillez entrer la commande:
./test/testStromer
# N Body Simulation
