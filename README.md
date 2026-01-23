# MiniRT, un projet 42 de raytracer 
MiniRT est un mini moteur de raytracing écrit en C.
Le programme génère une image 3D à partir d’une description de scène (.rt) en utilisant les principes fondamentaux du ray tracing : rayons, intersections, éclairage et ombres.

# Fonctionnalites

Objets supportés :
Sphère
Plan
Cylindre
Cône (bonus)
Lumière ponctuelle
Ombres portées
Gestion des normales
Textures (bonus)
Transparence / verre (bonus)
Degrade de couleurs (bonus)
Effet checkerboard (bonus)
Affichage en temps réel via MiniLibX

# UI
en mode "CAMERA" :
- rotation camera = click gauche + deplacement souris;
- translation camera :
              avant/arriere = scroll avant/arriere (axe z);
              haut/bas = w_key/s_key (axe y);
              camera gauche/droite = a_key/d_key (axe x);
en mode "EDIT":
- selection objet = click gauche souris;
- resize objet = scroll avant/arriere souris;
- translation objets:
                haut/bas = w_key/s_key (axe y);
                gauche/droite = a_key/d_key (axe x);
                avant/arriere = z_key enfoncee + scroll avant/arriere souris
- rotation objets: maintenir click gauche souris +
                axe x = q_KEY / e_KEY;
                axe y = a_KEY / d_KEY;
                axe z = z_KEY / c_KEY;
  
bascule mode "camera" <--> "edit" = m_key;
retour camera position initiale = r_key.

# concepts cles
Calcul des intersections rayon / objet
Calcul des normales
Éclairage de Phong (diffuse / spéculaire)
Rayons d’ombre
Anti auto-intersection via un offset (EPS)
Quaternions pour les rotations

# Sources:
Principes du ratracing:
 - https://euler.ac-versailles.fr/IMG/pdf/raytracing.pdf (francais);
 - https://raytracing.github.io/books/RayTracingInOneWeekend.html (english);
 - https://www.youtube.com/playlist?list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl
 - https://www.youtube.com/watch?v=gsZiJeaMO48

Bases mathematiques:
- rappels trigonometriques : https://perso.liris.cnrs.fr/gilles.gesquiere/Teaching/Imagina/Cours05.pdf, https://perso.univ-rennes1.fr/sean.mcnamara/AppMath2/2.4_cylindriques_spheriques.pdf;
- calcul vectoriel (https://www.youtube.com/watch?v=4uuQh-J0D2c) (francais);
- produit vectoriel, produit mixte et interpretation geometrique (https://www.youtube.com/watch?v=Qi1stedji44) (francais);
- https://docs.gl/sl4/refract
- https://docs.gl/sl4/reflect
- https://fr.wikipedia.org/wiki/Ombrage_de_Phong

Texture:
- https://anirudh-s-kumar.github.io/CG-Notes/texture_mapping/
- https://dogukannn.github.io/2024/12/12/ray-tracing-four.html
